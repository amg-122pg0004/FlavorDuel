#include "RegisterUI.h"
#include <map>
#include "ModeTitle.h"
#include "RegisterThread.h"
#include "UserDataStruct.h"
using namespace Flavor;
using Anchor = AppFrame::UIObjectBase::Anchor;
namespace {
	constexpr AppFrame::VECTOR2<int> CanvasSize = { 1280,720 };
	const std::map<RegisterError, std::string> ErrorMessage = {
		{RegisterError::None,""},
		{RegisterError::TooShortID,"ユーザーIDは5文字以上で設定してください"},
		{RegisterError::TooShortPassword,"パスワードは8文字以上で設定してください"},
		{RegisterError::ForbiddenCharacterID,"ユーザーIDに使用できない文字が含まれています"},
		{RegisterError::ForbiddenCharacterPassword,"パスワードに使用できない文字が含まれています"},
		{RegisterError::DuplicateID,"このユーザーIDは既に使われています"},
		{RegisterError::PasswordNotMach,"入力されたパスワードが一致していません"}
	};
	constexpr auto ForbiddenCharacter = "$\\\"'`;()[]{}|";
	constexpr auto BackGroundImagePath = "res/background.png";
}

RegisterUI::RegisterUI(ModeTitle& mode)
	:AppFrame::UICanvas(CanvasSize)
	, _registerThread{ nullptr }
	, _error{ RegisterError::None }
	, _name{ nullptr }
	, _password{ nullptr }
	, _passwordReenter{ nullptr }
	, _errorText{ nullptr }
	, _titleMode{ mode }
{
	this->SetName("Register");

	auto app = AppFrame::ApplicationBase::GetInstance();
	int windowWidth = app->DispSizeW();
	int windowHeight = app->DispSizeH();
	int centerX = static_cast<int>(windowWidth * 0.5f);
	int centerY = static_cast<int>(windowHeight * 0.5f);

	auto backgroundImage = std::make_unique<AppFrame::UI::Image>(BackGroundImagePath);
	this->AddUIObject(std::move(backgroundImage));

	//ID入力テキストボックス
	auto userNameBox = std::make_unique<AppFrame::UI::EditableTextBox>("", 200, true, true, false);
	userNameBox->SetAnchor(Anchor::Center);
	userNameBox->SetPosition({ centerX,centerY });
	userNameBox->SetSize({ 200,20 });
	userNameBox->SetDrawBox(true);
	userNameBox->SetDefaultText("ユーザーID");
	_name = userNameBox.get();
	this->AddUIObject(std::move(userNameBox));

	auto passwordBox = std::make_unique<AppFrame::UI::EditableTextBox>("", 200, true, true, false);
	passwordBox->SetPosition({ centerX,centerY + 22 });
	passwordBox->SetSize({ 200,20 });
	passwordBox->SetAnchor(Anchor::Center);
	passwordBox->SetDrawBox(true);
	passwordBox->SetSecret(true);
	passwordBox->SetDefaultText("パスワード");
	_password = passwordBox.get();
	this->AddUIObject(std::move(passwordBox));

	auto passwordBoxReenter = std::make_unique<AppFrame::UI::EditableTextBox>("");
	passwordBoxReenter->SetPosition({ centerX,centerY + 44 });
	passwordBoxReenter->SetSize({ 200,20 });
	passwordBoxReenter->SetAnchor(Anchor::Center);
	passwordBoxReenter->SetDrawBox(true);
	passwordBoxReenter->SetSecret(true);
	passwordBoxReenter->SetDefaultText("パスワード再入力");
	_passwordReenter = passwordBoxReenter.get();
	this->AddUIObject(std::move(passwordBoxReenter));

	auto registerButton = std::make_unique<AppFrame::UI::Button>();
	registerButton->SetAnchor(Anchor::Center);
	registerButton->SetPosition({ centerX,centerY + 160 });
	registerButton->SetTextBox({ std::make_unique<AppFrame::UI::TextBox>("登録") });
	auto registerFunction = [&]() {
		CheckIDAndPassword();
		if (_error != RegisterError::None) {
			return;
		}
		_registerThread.reset(new RegisterThread(_name->GetText(), _password->GetText()));
		_registerThread->ThreadStart();
	};
	registerButton->SetFunction(registerFunction);
	this->AddUIObject(std::move(registerButton));

	auto loginButton = std::make_unique<AppFrame::UI::Button>();
	loginButton->SetAnchor(Anchor::Center);
	loginButton->SetPosition({ centerX + 200,centerY + 160 });
	loginButton->SetSize({ 100,20 });
	auto loginText = std::make_unique<AppFrame::UI::TextBox>("ログイン画面");
	loginText->SetTextColor(AppFrame::Color::Black);
	loginButton->SetTextBox(std::move(loginText));
	auto changeUIFunction = [&]() {
		_titleMode.SetNextUI(TitleUI::Login);
	};
	loginButton->SetFunction(changeUIFunction);
	this->AddUIObject(std::move(loginButton));

	auto errorMessage = std::make_unique<AppFrame::UI::TextBox>("");
	errorMessage->SetAnchor(Anchor::Center);
	errorMessage->SetPosition({ centerX,centerY-20 });
	_errorText = errorMessage.get();
	this->AddUIObject(std::move(errorMessage));
}

void RegisterUI::Init()
{
	AppFrame::UICanvas::Init();
}

void RegisterUI::Terminate()
{
	AppFrame::UICanvas::Terminate();
}

void RegisterUI::Update(InputManager& input, float deltaSeconds)
{
	auto preError = _error;
	AppFrame::UICanvas::Update(input, deltaSeconds);
	if (_registerThread) {
		if (!_registerThread->IsThreadExec()) {
			if (_registerThread->GetSuccess()) {
				auto app = AppFrame::ApplicationBase::GetInstance();
				app->GetAppData()->SetData(_registerThread->GetUserData());
				_error = RegisterError::None;
				_titleMode.ChangeModeHome();
			}
			else {
				_error = RegisterError::DuplicateID;
			}
			_registerThread.release();
		}
	}
	if (preError != _error) {
		_errorText->SetText(ErrorMessage.at(_error));
		this->RefreshScreen();
	}
}

void RegisterUI::Render()
{
	AppFrame::UICanvas::Render();
}

void Flavor::RegisterUI::CheckIDAndPassword()
{
	_error = RegisterError::None;
	//IDが短すぎないか
	if (static_cast<int>(_name->GetText().size()) < 5) {
		_error = RegisterError::TooShortID;
		return;
	}
	//IDに使用禁止文字が含まれないか
	std::string forbiddenString(ForbiddenCharacter);
	for (auto& chara : _name->GetText()) {
		for (auto& checkChara : forbiddenString) {
			if (checkChara == chara) {
				_error = RegisterError::ForbiddenCharacterID;
				return;
			}
		}
	}

	//パスワードが一致しているか
	if (_password->GetText() != _passwordReenter->GetText()) {
		_error = RegisterError::PasswordNotMach;
		return;
	}
	//パスワードが短すぎないか
	if (static_cast<int>(_password->GetText().size()) < 8) {
		_error = RegisterError::TooShortPassword;
	}
	//パスワードに使用禁止文字が含まれないか
	for (auto& chara : _password->GetText()) {
		for (auto& checkChara : forbiddenString) {
			if (checkChara == chara) {
				_error = RegisterError::ForbiddenCharacterPassword;
				return;
			}
		}
	}
}
