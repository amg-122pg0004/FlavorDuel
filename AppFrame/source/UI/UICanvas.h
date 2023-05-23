/*****************************************************************//**
 * \file   UICanvas.h
 * \brief  UIを描画する画面クラス
 *         更新が不用な場合はあらかじめ_scrennに描き込んでおく
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "DxLib.h"
#include "Math/VECTOR2.h"

namespace AppFrame {
	class UIObjectBase;
	class InputManager;
	class UICanvas
	{
	public:
		UICanvas(VECTOR2<int> size);
		virtual ~UICanvas();
		virtual void Init();
		virtual void Terminate();
		virtual void Update(InputManager& input, float deltaSeconds);
		virtual void Render();
		void RefreshScreen();

		VECTOR2<int> GetScreenSize() { return _size; }

		void AddChildCanvas(std::unique_ptr<UICanvas> uiCanvas);
		void AddUIObject(std::unique_ptr<UIObjectBase> uiObject);

		std::vector<std::unique_ptr<UICanvas>>& GetChildCanvas() { return _childCanvas; }

		void SetPosition(VECTOR2<int> position) { _rootPosition = position; }

		bool GetNeedUpdate() { return _needUpdate; }
		void SetNeedUpdate(bool flag) { _needUpdate = flag; }

		std::string GetName() { return _name; }
		void SetName(std::string name) { _name = name; }

		bool getActivate() { return _activate; }
		void SetActivate(bool flag) { _activate = flag; }
	private:
		bool _activate;
		std::string _name;
		int _screen;//スクリーンハンドル
		VECTOR2<int> _size;//スクリーンサイズ
		VECTOR2<int> _rootPosition;//スクリーン基点位置
		std::vector<std::unique_ptr<UICanvas>> _childCanvas;//子キャンバス
		std::vector<std::unique_ptr<UIObjectBase>> _uiObjects;//UIオブジェクト
		bool _needUpdate;//更新が必要なオブジェクトが配列に含まれているか
	};
}