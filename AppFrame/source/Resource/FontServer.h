/*****************************************************************//**
 * \file   FontServer.h
 * \brief  フォントの読み込みを行うクラス
 *
 * \author 土居将太郎
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <string>
#include <unordered_map>
namespace AppFrame {
	class FontServer
	{
	public:
		static void Init();//<_fontGraphの初期化
		static void Release();//<ClearFont呼び出し

		static void ClearFont();//<_fontGraphデータの全削除

		/**
		 * \brief _fontGraphのキー検索
		 *
		 * \param filename 検索するキー名
		 * \return キーに対応した値を返す
		 */
		static int Find(std::string fontname);
		static int Erase(std::string fontname);
		/**
		 * \brief 読み込み済のファイル出なければmapに登録
		 *
		 * \param fontName 呼び出すための名前
		 * \param filename 読み込むファイル名
		 * \return 読み込んだ値、読み込み済みなら-1を返す
		 */
		static int LoadFont(std::string fontName, std::string filename);

	private:
		static std::unordered_map<std::string, int> _fontGraph;
	};
}