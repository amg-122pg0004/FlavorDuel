/*****************************************************************//**
 * \file   UICanvasServer.h
 * \brief  UICanvasฬz๑๐วท้NX
 *
 * \author yซพY
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <memory>
#include <vector>
#include <string>
namespace AppFrame {
	class UICanvas;
	class InputManager;
	class ModeBase;

	class UICanvasServer {

	public:
		UICanvasServer(ModeBase& parent);
		~UICanvasServer();

		std::vector<std::unique_ptr<UICanvas>>& GetObjects() { return _uiCanvas; }
		void Clear();

		void Add(std::unique_ptr<UICanvas> canvas);
		void Update(InputManager& input);
		void Render();

		UICanvas* Get(std::string name);
	private:
		std::vector<std::unique_ptr<UICanvas>> _uiCanvas;
		std::vector<std::unique_ptr<UICanvas>> _pendingUICanvas;

		bool _updating;
		void AddPendingObject();

		ModeBase& _mode;
	};
}