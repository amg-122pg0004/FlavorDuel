/*****************************************************************//**
 * \file   StringFitting.h
 * \brief  ������̑�����s���N���X
 *
 * \author �y�������Y
 * \date   June 2023
 *********************************************************************/
#pragma once
#include <string>

namespace Flavor {
	class StringFitting
	{
		public:
		/**
		 * \brief ����������̕��������Ƃɉ��s����
		 * \param text ���s�O������
		 * \param characterNumber ���s���镶����(byte��)
		 * \return 
		 */
		static std::string InsertLineBreak(std::string text, int characterNumber);
	};
}