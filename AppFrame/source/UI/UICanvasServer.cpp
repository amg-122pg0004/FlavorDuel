/*****************************************************************//**
 * \file   UICanvasServer.cpp
 * \brief  UICanvasの配列を管理するクラス
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#include "UICanvasServer.h"
#include <algorithm>
#include "UICanvas.h"
#include "ModeBase.h"
namespace AppFrame {
	UICanvasServer::UICanvasServer(ModeBase& parent)
		:_mode{ parent }
	{
		_uiCanvas.clear();
		_pendingUICanvas.clear();
	}

	UICanvasServer::~UICanvasServer()
	{
	}

	void UICanvasServer::UICanvasServer::Clear()
	{
		_uiCanvas.clear();
		_pendingUICanvas.clear();
	}

	void UICanvasServer::UICanvasServer::Add(std::unique_ptr<UICanvas> canvas)
	{
		canvas->Init();

		if (_updating) {
			_pendingUICanvas.push_back(std::move(canvas));
		}
		else {
			_uiCanvas.push_back(std::move(canvas));
		}
	}

	void UICanvasServer::UICanvasServer::Update(InputManager& input)
	{
		_updating = true;
		AddPendingObject();
		float deltaSeconds = _mode.GetStepTime() * 0.001f;
		for (auto&& canvas : _uiCanvas) {
			canvas->Update(input, deltaSeconds);
		}
		_updating = false;
	}

	void UICanvasServer::UICanvasServer::Render()
	{
		for (auto&& canvas : _uiCanvas) {
			canvas->Render();
		}
	}

	UICanvas* UICanvasServer::Get(std::string name)
	{
		auto findResult = std::find_if(_uiCanvas.begin(), _uiCanvas.end(), [&name](std::unique_ptr<UICanvas>& canvas) {return canvas->GetName() == name; });
		if (findResult != _uiCanvas.end()) {
			return (*findResult).get();
		}
		return nullptr;
	}

	void UICanvasServer::UICanvasServer::AddPendingObject()
	{
		if (_pendingUICanvas.size() > 0) {
			auto ite = _pendingUICanvas.begin();

			for (; ite != _pendingUICanvas.end(); ++ite) {
				_uiCanvas.push_back(std::move((*ite)));
			}

			_pendingUICanvas.clear();
		}
	}
}