/*****************************************************************//**
 * \file   StringFitting.h
 * \brief  文字列の操作を行うクラス
 *
 * \author 土居将太郎
 * \date   June 2023
 *********************************************************************/
#pragma once
#include <string>

namespace Flavor {
	class StringFitting
	{
		public:
		/**
		 * \brief 文字列を特定の文字数ごとに改行する
		 * \param text 改行前文字列
		 * \param characterNumber 改行する文字数(byte数)
		 * \return 
		 */
		static std::string InsertLineBreak(std::string text, int characterNumber);
	};
}