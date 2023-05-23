/*****************************************************************//**
 * \file   UICanvas.cpp
 * \brief  UIを描画する画面クラス
 *         更新が不用なUIオブジェクトはあらかじめ_scrennに描き込んでおく
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#include "UICanvas.h"
#include "UIObjectBase.h"
#include "ChangeScreen.h"
namespace AppFrame {

	UICanvas::UICanvas(VECTOR2<int> size)
		:_activate{ true }
		, _screen{ -1 }
		, _size{ size }
		, _rootPosition{ 0,0 }
		, _needUpdate{ false }
		, _name{ "" }
	{
	}

	UICanvas::~UICanvas()
	{
	}

	void UICanvas::Init()
	{
		_screen = MakeScreen(_size.x, _size.y, true);

		int currentScrenn = GetDrawScreen();
		ChangeScreen::ChangeScreenAndSaveCamera(_screen);
		for (auto&& ui : _uiObjects) {
			if (ui->GetNeedUpdate()) {
				_needUpdate = true;
			}
			else {
				ui->Render();
			}
		}
		for (auto&& canvas : _childCanvas) {
			canvas->Init();
			if (canvas->GetNeedUpdate()) {
				_needUpdate = true;
			}
		}
		ChangeScreen::ChangeScreenAndSaveCamera(currentScrenn);
	}

	void UICanvas::Terminate()
	{
		for (auto&& canvas : _childCanvas) {
			canvas->Terminate();
		}
		DeleteGraph(_screen);
	}

	void UICanvas::Update(InputManager& input, float deltaSeconds)
	{
		if (!_activate) {
			return;
		}
		if (!_needUpdate) {
			return;
		}
		for (auto&& ui : _uiObjects) {
			if (ui->GetNeedUpdate()) {
				ui->Update(input, deltaSeconds);
			}
		}
		for (auto&& canvas : _childCanvas) {
			canvas->Update(input, deltaSeconds);
		}
	}

	void UICanvas::Render()
	{
		if (!_activate) {
			return;
		}
		DrawGraph(_rootPosition.x, _rootPosition.y, _screen, true);
		if (!_needUpdate) {
			return;
		}
		for (auto&& ui : _uiObjects) {
			if (ui->GetNeedUpdate()) {
				ui->Render();
			}
		}
		for (auto&& canvas : _childCanvas) {
			canvas->Render();
		}
	}
	void UICanvas::RefreshScreen()
	{
		DeleteGraph(_screen);
		_screen = MakeScreen(_size.x, _size.y, true);
		int currentScrenn = GetDrawScreen();
		ChangeScreen::ChangeScreenAndSaveCamera(_screen);
		for (auto&& ui : _uiObjects) {
			if (ui->GetNeedUpdate()) {
				_needUpdate = true;
			}
			else {
				ui->Render();
			}
		}
		for (auto&& canvas : _childCanvas) {
			canvas->Init();
			if (canvas->GetNeedUpdate()) {
				_needUpdate = true;
			}
		}
		ChangeScreen::ChangeScreenAndSaveCamera(currentScrenn);
	}
	void UICanvas::AddChildCanvas(std::unique_ptr<UICanvas> uiCanvas)
	{
		uiCanvas->Init();
		_childCanvas.emplace_back(std::move(uiCanvas));
	}

	void UICanvas::AddUIObject(std::unique_ptr<UIObjectBase> uiObject)
	{
		_uiObjects.emplace_back(std::move(uiObject));
	}
}