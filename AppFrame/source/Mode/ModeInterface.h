#pragma once
#include <sstream>
#include <functional>
#include <fstream>
#include <math.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include <time.h>
#include <windows.h>
#include "DxLib.h"
#include "AppFrameMath.h"
namespace AppFrame {
	class ModeInterface
	{
	public:
		virtual float GetLevelSize() { return 0.0f; }

		virtual bool SetLevelMinMax(std::pair<VECTOR, VECTOR> minmax) { return false; }
		virtual VECTOR GetLevelMax() { return Math::VZero(); }
		virtual VECTOR GetLevelMin() { return Math::VZero(); }

		virtual VECTOR GetVector() { return Math::VZero(); }
		virtual bool SetVecString(std::vector<std::string> p) { return false; }
		virtual std::vector<std::string> GetVecString() { std::vector<std::string> p; return p; }
	};

}