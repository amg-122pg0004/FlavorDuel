/*****************************************************************//**
 * \file   TimelineComponent.h
 * \brief  キーフレームと補間方法を設定して、タイムラインを作成・セットします。GetValueで値を返します。
 * \brief　_visbleをtrueにするとデバッグモードでグラフの曲線を確認できます
 *
 * \author 土居将太郎
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <vector>
#include "ComponentBase.h"
#include "Utility/Easing.h"
namespace AppFrame {
	class TimelineComponent : public ComponentBase
	{
	public:
		struct KeyFrame
		{
			float time;
			float value;
			EasingType type;
		};

		enum class PlayType {
			OnceNormal,//正順1回再生
			OnceReverse,//逆順1回再生
			OnceNormalAndReverce,//正順→逆順を1回再生
			LoopNormal,//正順ループ再生
			LoopReverse,//逆順ループ再生
			LoopNormalAndReverce,//正順→逆順をループ再生
		};

		using TimeLine = std::vector<KeyFrame>;

		TimelineComponent();
		bool Init()override;
		void Update(InputManager& input)override;
		void Debug()override;
		//値を取得(コンポーネント内にあるタイマー時間を使用)
		std::vector<float> GetValue();
		//指定した時間の値を取得
		std::vector<float> GetValueParticularTime(float time);
		//タイムラインを設定
		void SetTimeLine(TimeLine timeline);
		void SetTimeLine(std::vector<TimeLine> timeline);
		PlayType GetPlayType() { return _playType; }
		//再生タイプを設定
		void SetPlayType(PlayType type);
		//再生停止、再開を設定
		void SetStop(bool flag) { _stop = flag; }
		bool GetStop() { return _stop; }
		//タイマーを最初に戻す
		void ResetTime();

		void SetDebugVisible(bool flag) { _debugVisible = flag; }
	private:
		std::vector<TimeLine> _timeLines;//キーは時間、値はfirst設定値,second補間方法
		float GetMax();//最大の設定値
		float GetMin();//最小の設定値
		void DrawDebugImage();//デバッグ用のグラフの曲線を設定

		PlayType _playType;
		bool _reverse;
		bool _loop;
		bool _bothWays;
		bool _stop;//更新を行うか
		float _time;//現在の時間
		float _timeMax;//全体の時間

		int _debugImage;
		bool _debugVisible;
	};
}
