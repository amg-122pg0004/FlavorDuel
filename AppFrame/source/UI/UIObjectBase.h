/*****************************************************************//**
 * \file   UIObjectBase.h
 * \brief  UICanvasに配置可能なオブジェクトの基底クラス
 *         _needUpdatePerFrameがTrueの時のみ毎フレーム更新・描画を行う
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
#include "Math/AABB2D.h"
namespace AppFrame {
	class InputManager;
	class UIObjectBase
	{
	public:
		UIObjectBase();
		virtual ~UIObjectBase();
		virtual void Update(InputManager& input, float deltaSecond) = 0;
		virtual void Render() = 0;

		void SetNeedUpdate(bool flag) { _needUpdatePerFrame = flag; }
		const bool GetNeedUpdate() { return _needUpdatePerFrame; }

		void SetPosition(VECTOR2<int> position) { _position = position; }
		const VECTOR2<int> GetPosition() { return _position; }

		void SetSize(VECTOR2<int> size) { _size = size; }
		const VECTOR2<int> GetSize() { return _size; }
		const VECTOR2<int> GetHalfSize();

		enum class Anchor { UpperLeft, Center };
		void SetAnchor(Anchor position) { _anchor = position; }
		const Anchor GetAnchor() { return _anchor; }

		const AABB2D<int> GetAABB();

		const bool GetVisible() { return _visible; }
		void SetVisible(bool flag) { _visible = flag; }
	private:
		bool _needUpdatePerFrame;
		VECTOR2<int> _position;
		VECTOR2<int> _size;
		Anchor _anchor;
		bool _visible;
	};
}