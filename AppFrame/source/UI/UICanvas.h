/*****************************************************************//**
 * \file   UICanvas.h
 * \brief  UI��`�悷���ʃN���X
 *         �X�V���s�p�ȏꍇ�͂��炩����_screnn�ɕ`������ł���
 *
 * \author �y�������Y
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
		int _screen;//�X�N���[���n���h��
		VECTOR2<int> _size;//�X�N���[���T�C�Y
		VECTOR2<int> _rootPosition;//�X�N���[����_�ʒu
		std::vector<std::unique_ptr<UICanvas>> _childCanvas;//�q�L�����o�X
		std::vector<std::unique_ptr<UIObjectBase>> _uiObjects;//UI�I�u�W�F�N�g
		bool _needUpdate;//�X�V���K�v�ȃI�u�W�F�N�g���z��Ɋ܂܂�Ă��邩
	};
}