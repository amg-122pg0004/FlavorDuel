/*****************************************************************//**
 * \file   TimelineComponent.h
 * \brief  キーフレームと補間方法を設定して、タイムラインを作成・セットします。GetValueで値を返します。
 * \brief　_visbleをtrueにするとデバッグモードでグラフの曲線を確認できます
 *
 * \author 土居将太郎
 * \date   February 2023
 *********************************************************************/
#include "TimelineComponent.h"
#include "ObjectBase.h"
#include "../Mode/ModeBase.h"
#include "Color.h"
#include <sstream>
namespace AppFrame {
    TimelineComponent::TimelineComponent()
        :_stop{ false }
        , _playType{ PlayType::LoopNormal }
        , _reverse{ false }
        , _loop{ true }
        , _bothWays{ false }
        , _time{ 0 }
        , _timeMax{ 0 }
        , _debugImage{ -1 }
        , _debugVisible{ false }
    {
        _timeLines.resize(1);
    }

    bool TimelineComponent::Init()
    {
        _time = 0;

        return true;
    }

    void TimelineComponent::Update(InputManager& input)
    {
        if (_stop) {
            return;
        }

        float deltaTime = _parent->GetMode()->GetStepTime() * 0.001f;

        if (_reverse) {
            deltaTime *= -1.0f;
        }

        _time += deltaTime;

        if (_time > _timeMax) {
            if (_bothWays) {
                _time = _timeMax - std::fmod(_time, _timeMax);
                _reverse = true;
            }
            else if (_loop) {
                _time = std::fmod(_time, _timeMax);
            }
            else {
                _time = _timeMax;
                _stop = true;
            }
        }
        else if (_time < 0) {
            if (_bothWays && _loop) {
                _time = _time * -1.0f;
                _reverse = false;
            }
            else if (_loop) {
                _time = _timeMax - std::fmod(_time, _timeMax);
            }
            else {
                _time = 0;
                _stop = true;
            }
        }
    }

    void TimelineComponent::Debug()
    {
        if (!_debugVisible) {
            return;
        }

        DrawGraph(0, 0, _debugImage, false);
        int x = static_cast<int>(_time / _timeMax * 500.0f);
        DrawLine(x, 0, x, 200, Color::Blue);

        std::stringstream ss;
        ss << "タイムライン" << "name:" << _parent->GetName() << "　ID:" << _parent->GetID() << "\n";
        DrawString(0, 0, ss.str().c_str(), Color::Red );
        std::stringstream ss2;
        ss2 << "最大値:" << GetMax() << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n";
        ss2 << "最小値:" << GetMin();
        DrawString(420, 0, ss2.str().c_str(), Color::Red);
        std::stringstream ss3;
        ss3 << "開始秒:0" << "　　　　　　　　　　　　　　　　　　　　　　終了秒" << _timeMax;
        DrawString(0, 180, ss3.str().c_str(), Color::Red);
    }

    std::vector<float> TimelineComponent::GetValue()
    {
        return GetValueParticularTime(_time);
    }

    std::vector<float> TimelineComponent::GetValueParticularTime(float time)
    {
        std::vector<float> result;

        if (_timeLines.size() == 0) {
            result.push_back({ 0.0f });
            return result;
        }

        for (auto&& timeline : _timeLines) {
            for (auto itr = timeline.rbegin(); itr != timeline.rend(); ++itr) {
                if (time >= itr->time) {
                    //最後のキーフレーム以降なら最後のキーフレームの値を返す
                    if (itr == timeline.rbegin()) {
                        result.push_back(itr->value);
                        break;
                    }

                    auto next = std::prev(itr);
                    auto easing = Easing::GetMode(itr->type);

                    result.push_back(static_cast<float>(easing(time - itr->time, itr->value, next->value, next->time - itr->time)));
                    break;
                }
            }
        }

        return result;
    }

    namespace {
        static bool keyFrameSort(TimelineComponent::KeyFrame& x, TimelineComponent::KeyFrame& y) {
            return x.time < y.time;
        }
    }
    void TimelineComponent::SetTimeLine(TimeLine timeline)
    {
        _timeLines.resize(1);
        _timeLines[0] = timeline;
        std::sort(_timeLines[0].begin(), _timeLines[0].end(), keyFrameSort);
        _timeMax = _timeLines[0].back().time;
        DrawDebugImage();
    }

    void TimelineComponent::SetTimeLine(std::vector<TimeLine> timeline)
    {
        _timeLines.resize(timeline.size());
        _timeLines = timeline;

        for (auto&& timeline : _timeLines) {
            std::sort(timeline.begin(), timeline.end(), keyFrameSort);
        }

        _timeMax = _timeLines[0].back().time;
        DrawDebugImage();
    }

    void TimelineComponent::SetPlayType(PlayType type)
    {
        switch (type) {
        case TimelineComponent::PlayType::OnceNormal:
            _loop = false;
            _reverse = false;
            _bothWays = false;
            break;

        case TimelineComponent::PlayType::OnceReverse:
            _loop = false;
            _reverse = true;
            _bothWays = false;
            break;

        case TimelineComponent::PlayType::OnceNormalAndReverce:
            _loop = false;
            _reverse = false;
            _bothWays = true;
            break;

        case TimelineComponent::PlayType::LoopNormal:
            _loop = true;
            _reverse = false;
            _bothWays = false;
            break;

        case TimelineComponent::PlayType::LoopReverse:
            _loop = true;
            _reverse = true;
            _bothWays = false;
            break;

        case TimelineComponent::PlayType::LoopNormalAndReverce:
            _loop = true;
            _reverse = false;
            _bothWays = true;
            break;
        }

        ResetTime();
    }

    void TimelineComponent::ResetTime()
    {
        if (_reverse) {
            _time = _timeMax;
        }
        else {
            _time = 0;
        }
    }

    void TimelineComponent::DrawDebugImage()
    {
#ifdef _DEBUG
        int debugSolfImage = MakePAL8ColorSoftImage(500, 200);
        FillSoftImage(debugSolfImage, 255, 255, 255, 0);
        SetPaletteSoftImage(debugSolfImage, 0, 255, 0, 0, 0);
        SetPaletteSoftImage(debugSolfImage, 1, 0, 255, 0, 0);
        SetPaletteSoftImage(debugSolfImage, 2, 0, 0, 255, 0);
        SetPaletteSoftImage(debugSolfImage, 3, 0, 0, 0, 0);

        auto max = GetMax();
        auto min = GetMin();
        auto rangeY = max - min;

        for (int xPx = 0; xPx < 500; ++xPx) {

            std::vector<float> values = GetValueParticularTime(xPx * _timeMax / 500);

            for (int i = 0; i < values.size(); ++i) {
                auto y = 200.0f - ((values[i] - min) * 200.0f / rangeY);
                int color = i;

                if (color > 3) {
                    color = 3;
                }

                DrawPixelPalCodeSoftImage(debugSolfImage, static_cast<int>(xPx), static_cast<int>(y), color);
            }
        }

        _debugImage = CreateGraphFromSoftImage(debugSolfImage);
#endif // DEBUG


    }

    float TimelineComponent::GetMax()
    {
        float result{ 0.0f };

        for (auto&& timeline : _timeLines) {
            auto max = std::max_element(timeline.begin(), timeline.end(), [](const auto& l, const auto& r) {return l.value < r.value; });

            if (max->value > result) {
                result = max->value;
            }
        }

        return result;
    }

    float TimelineComponent::GetMin()
    {
        float result = _timeLines[0][0].value;

        for (auto&& timeline : _timeLines) {
            auto min = std::max_element(timeline.begin(), timeline.end(), [](const auto& l, const auto& r) {return l.value > r.value; });

            if (min->value < result) {
                result = min->value;
            }
        }

        return result;
    }

}