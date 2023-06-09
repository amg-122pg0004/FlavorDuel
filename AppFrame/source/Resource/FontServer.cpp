/*****************************************************************//**
 * \file   FontServer.cpp
 * \brief  フォントの読み込みを行うクラス
 *
 * \author 土居将太郎
 * \date   January 2023
 *********************************************************************/
#include "DxLib.h"
#include "FontServer.h"
namespace AppFrame {
	std::unordered_map<std::string, int> FontServer::_fontGraph;

	void FontServer::Init()
	{
		_fontGraph.clear();
	}

	void FontServer::Release()
	{
		ClearFont();
	}

	void FontServer::ClearFont()
	{
		for (auto&& graph : _fontGraph) {
			DeleteFontToHandle(graph.second);
		}

		_fontGraph.clear();
	}

	int FontServer::Find(std::string fontname)
	{
		auto itr = _fontGraph.find(fontname);

		if (itr != _fontGraph.end()) {
			return itr->second;
		}

		return -1;
	}

	int FontServer::Erase(std::string fontname)
	{
		auto itr = _fontGraph.find(fontname);

		if (itr != _fontGraph.end()) {
			_fontGraph.erase(itr);
			return 1;
		}

		return -1;
	}

	int FontServer::LoadFont(std::string fontName, std::string filename)
	{
		int font = Find(filename);

		if (font == -1) {
			font = ::LoadFontDataToHandle(filename.c_str());
			_fontGraph[fontName] = font;
		}

		return font;
	}

}