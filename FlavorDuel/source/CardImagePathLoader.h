/*****************************************************************//**
 * \file   CardImagePathLoader.h
 * \brief  カード画像のIDからファイルパスを呼び出せるように読み込んでおくクラス
 *         カード画像IDは画像ごとに連番で設定したものがデータベース上にある
 * 
 * \author 土居将太郎
 * \date   June 2023
 *********************************************************************/
#pragma once
#include <map>
#include <string>
namespace Flavor {
	class CardImagePathLoader
	{
	public:
		CardImagePathLoader();
		std::string GetPath(int id);
	private:
		std::map<int, std::string> _cardImageMap;
	};
}
