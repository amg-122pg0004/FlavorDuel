#include "TitleUI.h"
#include "ModeTitle.h"
#include "PostData.h"
using namespace Flavor;
using Anchor = AppFrame::UIObjectBase::Anchor;
namespace {
	AppFrame::VECTOR2<int> CanvasSize = { 1280,780 };
}

TitleUI::TitleUI(ModeTitle& mode)
	:AppFrame::UICanvas(CanvasSize)
	, _loginThread{ nullptr }
	, _loginState{ LoginState::Idle }
	, _name{ nullptr }
	, _password{ nullptr }
{
	auto app = AppFrame::ApplicationBase::GetInstance();
	int windowWidth = app->DispSizeW();
	int windowHeight = app->DispSizeH();
	int centerX = static_cast<int>(windowWidth * 0.5f);
	int centerY = static_cast<int>(windowHeight * 0.5f);

	std::make_unique<AppFrame::UI::TextBox>("Login");
	auto userNameBox = std::make_unique<AppFrame::UI::EditableTextBox>("");
	userNameBox->SetAnchor(Anchor::Center);
	userNameBox->SetPosition({ centerX,centerY });
	userNameBox->SetSize({ 200,20 });
	userNameBox->SetDrawBox(true);
	userNameBox->SetDefaultText("ユーザーID");
	_name = userNameBox.get();

	auto passwordBox = std::make_unique<AppFrame::UI::EditableTextBox>("");
	passwordBox->SetPosition({ centerX,centerY + 80 });
	passwordBox->SetSize({ 200,20 });
	passwordBox->SetAnchor(Anchor::Center);
	passwordBox->SetDrawBox(true);
	passwordBox->SetSecret(true);
	passwordBox->SetDefaultText("パスワード");
	_password = passwordBox.get();

	auto loginButton = std::make_unique<AppFrame::UI::Button>();
	loginButton->SetAnchor(Anchor::Center);
	loginButton->SetPosition({ centerX,centerY + 160 });
	loginButton->SetTextBox({ std::make_unique<AppFrame::UI::TextBox>("Login") });

	auto loginFunction = [&]() {
		_loginThread.reset(new LoginThread(_name->GetText(), _password->GetText()));
		_loginThread->ThreadStart();
	};
	loginButton->SetFunction(loginFunction);

	//auto registerButton = std::make_unique<AppFrame::UI::Button>();
	//registerButton->SetAnchor(Anchor::Center);

	this->AddUIObject(std::move(userNameBox));
	this->AddUIObject(std::move(passwordBox));
	this->AddUIObject(std::move(loginButton));
	//this->AddUIObject(std::move(registerButton));
}

TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
	AppFrame::UICanvas::Init();
}

void TitleUI::Terminate()
{
	AppFrame::UICanvas::Terminate();
}

void TitleUI::Update(InputManager& input, float deltaSeconds)
{
	AppFrame::UICanvas::Update(input, deltaSeconds);
	if (_loginThread) {
		if (!_loginThread->IsThreadExec()) {
			if (_loginThread->GetSuccess()) {
				_loginState = LoginState::Success;
				_data = _loginThread->GetUserData();
			}
			else {
				_loginState = LoginState::Fail;
			}
			_loginThread.release();
		}
	}
}

void TitleUI::Render()
{
	AppFrame::UICanvas::Render();
	if (_loginState != LoginState::Idle) {
		std::string message{"LoginSuccess!"};
		if (_loginState == LoginState::Fail) {
			message = "LoginFail";
		}
		DrawString(0, 0, message.c_str(), AppFrame::Color::Red);
	}
	if (_loginState == LoginState::Success) {
		DrawString(0, 20, ("ID:" + _data.id).c_str(), AppFrame::Color::Red);
		DrawString(0, 40, ("レベル:" + std::to_string(_data.level)).c_str(), AppFrame::Color::Red);
		DrawString(0, 60, ("所持金:" + std::to_string(_data.money)).c_str(), AppFrame::Color::Red);
		DrawString(0, 80, ("ランク:" + std::to_string(_data.rank)).c_str(), AppFrame::Color::Red);
	}

}