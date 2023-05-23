#include "LoginUI.h"
#include "ModeTitle.h"
#include "PostData.h"
#include "UserDataStruct.h"
using namespace Flavor;
using Anchor = AppFrame::UIObjectBase::Anchor;
namespace {
	AppFrame::VECTOR2<int> CanvasSize = { 1280,780 };
}

LoginUI::LoginUI(ModeTitle& mode)
	:AppFrame::UICanvas(CanvasSize)
	, _titleMode{ mode }
	, _loginThread{ nullptr }
	, _loginState{ LoginState::Idle }
	, _name{ nullptr }
	, _password{ nullptr }
{
	this->SetName("Login");

	auto app = AppFrame::ApplicationBase::GetInstance();
	int windowWidth = app->DispSizeW();
	int windowHeight = app->DispSizeH();
	int centerX = static_cast<int>(windowWidth * 0.5f);
	int centerY = static_cast<int>(windowHeight * 0.5f);

	auto userNameBox = std::make_unique<AppFrame::UI::EditableTextBox>("");
	userNameBox->SetAnchor(Anchor::Center);
	userNameBox->SetPosition({ centerX,centerY });
	userNameBox->SetSize({ 200,20 });
	userNameBox->SetDrawBox(true);
	userNameBox->SetDefaultText("ユーザーID");
	_name = userNameBox.get();
	this->AddUIObject(std::move(userNameBox));

	auto passwordBox = std::make_unique<AppFrame::UI::EditableTextBox>("");
	passwordBox->SetPosition({ centerX,centerY + 80 });
	passwordBox->SetSize({ 200,20 });
	passwordBox->SetAnchor(Anchor::Center);
	passwordBox->SetDrawBox(true);
	passwordBox->SetSecret(true);
	passwordBox->SetDefaultText("パスワード");
	_password = passwordBox.get();
	this->AddUIObject(std::move(passwordBox));

	auto loginButton = std::make_unique<AppFrame::UI::Button>();
	loginButton->SetAnchor(Anchor::Center);
	loginButton->SetPosition({ centerX,centerY + 160 });
	loginButton->SetTextBox({ std::make_unique<AppFrame::UI::TextBox>("ログイン") });
	auto loginFunction = [&]() {
		_loginThread.reset(new LoginThread(_name->GetText(), _password->GetText()));
		_loginThread->ThreadStart();
	};
	loginButton->SetFunction(loginFunction);
	this->AddUIObject(std::move(loginButton));

	auto registerButton = std::make_unique<AppFrame::UI::Button>();
	registerButton->SetAnchor(Anchor::Center);
	registerButton->SetPosition({ centerX + 200,centerY + 160 });
	registerButton->SetSize({ 100,20 });
	auto registerText = std::make_unique<AppFrame::UI::TextBox>("新規登録");
	registerText->SetTextColor(AppFrame::Color::Black);
	registerButton->SetTextBox(std::move(registerText));
	auto changeUIFunction = [&]() {
		_titleMode.SetNextUI(TitleUI::Register);
	};
	registerButton->SetFunction(changeUIFunction);
	this->AddUIObject(std::move(registerButton));
}

LoginUI::~LoginUI()
{
}

void LoginUI::Init()
{
	AppFrame::UICanvas::Init();
}

void LoginUI::Terminate()
{
	AppFrame::UICanvas::Terminate();
}

void LoginUI::Update(InputManager& input, float deltaSeconds)
{
	AppFrame::UICanvas::Update(input, deltaSeconds);
	if (_loginThread) {
		if (!_loginThread->IsThreadExec()) {
			if (_loginThread->GetSuccess()) {
				_loginState = LoginState::Success;
				auto app = AppFrame::ApplicationBase::GetInstance();
				app->GetAppData()->SetData(_loginThread->GetUserData());
				_titleMode.ChangeModeHome();
			}
			else {
				_loginState = LoginState::Fail;
			}
			_loginThread.release();
		}
	}
}

void LoginUI::Render()
{
	AppFrame::UICanvas::Render();
	if (_loginState != LoginState::Idle) {
		std::string message{"LoginSuccess!"};
		if (_loginState == LoginState::Fail) {
			message = "LoginFail";
		}
		DrawString(0, 0, message.c_str(), AppFrame::Color::Red);
	}

}