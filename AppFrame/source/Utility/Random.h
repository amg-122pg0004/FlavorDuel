/*****************************************************************//**
 * \file   Random.h
 * \brief  ランダムな値を取得するクラス
 * 
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <random>
namespace AppFrame {
    class Random
    {
    public:
        /**
         * \brief 指定された2つの整数の間からランダムな整数を取得する
         * \param min 最小値
         * \param max 最大値
         * \return ランダムな値
         */
        static int GetBtetweenNumbers(int min, int max) {
            std::default_random_engine engine(seedGenerator());
            std::uniform_int_distribution<> dist(min, max);
            return dist(engine);
        }
        /**
         * \brief 0から1の間でランダムなfloat値を取得する
         * \return ランダムなfloat値
         */
        static float GetBetween0to1() { return static_cast<float>(GetBtetweenNumbers(1, 1000) * 0.001f); }

        static std::mt19937 GetSeed() { return  std::mt19937(seedGenerator()); }
    private:
        static std::random_device seedGenerator;
    };
}