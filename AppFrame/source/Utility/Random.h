/*****************************************************************//**
 * \file   Random.h
 * \brief  �����_���Ȓl���擾����N���X
 * 
 * \author �y�������Y
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <random>
namespace AppFrame {
    class Random
    {
    public:
        /**
         * \brief �w�肳�ꂽ2�̐����̊Ԃ��烉���_���Ȑ������擾����
         * \param min �ŏ��l
         * \param max �ő�l
         * \return �����_���Ȓl
         */
        static int GetBtetweenNumbers(int min, int max) {
            std::default_random_engine engine(seedGenerator());
            std::uniform_int_distribution<> dist(min, max);
            return dist(engine);
        }
        /**
         * \brief 0����1�̊ԂŃ����_����float�l���擾����
         * \return �����_����float�l
         */
        static float GetBetween0to1() { return static_cast<float>(GetBtetweenNumbers(1, 1000) * 0.001f); }

        static std::mt19937 GetSeed() { return  std::mt19937(seedGenerator()); }
    private:
        static std::random_device seedGenerator;
    };
}