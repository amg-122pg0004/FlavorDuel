/*****************************************************************//**
 * \file   ModeServer.cpp
 * \brief  モードを管理するクラス
 *         プログラムはモード単位で分かれている（タイトルモード、ステージ選択モード、インゲームモード等）
 *         複数のモードが動いているとき、レイヤーが上の物を優先して描画する
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/

#include "ModeServer.h"
#include <cstddef>
#include "DxLib.h"
#include "ModeServer.h"
#include "InputManager.h"

namespace AppFrame {

    /// インスタンス
    ModeServer* ModeServer::_lpInstance = NULL;

    // --------------------------------------------------------------------------
    /// @brief コンストラクタ
    // --------------------------------------------------------------------------
    ModeServer::ModeServer()
    {
        _lpInstance = this;
        _uid_count = 1;
        _nowMode = NULL;
        _skipUpdateMode = NULL;
        _skipRenderMode = NULL;
        _pauseUpdateMode = NULL;
        _slowRate = 1.0f;
        _slowStart = 0;
        _slowDuration = 0.0f;
    }

    // --------------------------------------------------------------------------
    /// @brief
    // --------------------------------------------------------------------------
    ModeServer::~ModeServer()
    {
        Clear();
        _lpInstance = NULL;
    }


    // 登録はするが、一度メインを回さないといけない
    int ModeServer::Add(std::unique_ptr<ModeBase> mode, int layer, const char* name) {
        mode->SetUID(_uid_count);
        _uid_count++;
        mode->SetLayer(layer);
        mode->SetSZName(name);
        auto uid = mode->GetUID();
        _vModeAdd.push_back(std::move(mode));		// 登録予約
        return uid;
    }

    // 削除予約
    int ModeServer::Del(ModeBase* mode, int delayFrame) {
        _vModeDel.push_back(mode);
        _deleteDelay[mode] = delayFrame;
        return 0;
    }

    // 削除＆delete
    int ModeServer::Release(ModeBase* mode) {
        auto ite = _vMode.begin();

        for (; ite != _vMode.end(); ) {
            if ((*ite).get() == mode) {
                (*ite)->Terminate();
                ite = _vMode.erase(ite);
            }
            else {
                ++ite;
            }
        }

        return 1;
    }

    // 全部削除
    void ModeServer::Clear() {
        auto ite = _vMode.rbegin();

        for (; ite != _vMode.rend(); ++ite) {
            (*ite)->Terminate();
        }

        auto iteAdd = _vModeAdd.begin();

        for (; iteAdd != _vModeAdd.end(); ++iteAdd) {
            (*iteAdd)->Terminate();

        }

        _vMode.clear();
        _vModeAdd.clear();
        _vModeDel.clear();
    }



    // 削除予約されているか？
    bool ModeServer::IsDelRegist(ModeBase* mode) {
        if (_vModeDel.size() > 0) {
            auto iteDel = _vModeDel.begin();

            for (; iteDel != _vModeDel.end(); ++iteDel) {
                if ((*iteDel) == mode) { return true; }
            }
        }

        return false;
    }

    // モードリストにあるか？
    bool ModeServer::IsAdd(ModeBase* serchMode) {
        // 登録中のもの、登録予約中のものから検索する
        for (auto&& mode : _vMode) {
            if (!IsDelRegist(mode.get()) && mode.get() == serchMode) { return true; }
        }

        for (auto&& mode : _vMode) {
            if (!IsDelRegist(mode.get()) && mode.get() == serchMode) { return true; }
        }

        return false;
    }

    // 登録IDから検索
    ModeBase* ModeServer::Get(int uid) {
        // 登録中のもの、登録予約中のものから検索する
        for (auto&& mode : _vMode) {
            if (!IsDelRegist(mode.get()) && mode->GetUID() == uid) { return mode.get(); }
        }

        for (auto&& mode : _vModeAdd) {
            if (!IsDelRegist(mode.get()) && mode->GetUID() == uid) { return mode.get(); }
        }

        return nullptr;
    }

    // 名前から検索
    ModeBase* ModeServer::Get(const std::string name) {
        // 登録中のもの、登録予約中のものから検索する

        for (auto&& mode : _vMode) {
            if (!IsDelRegist(mode.get()) && mode->GetSZName() == name) { return mode.get(); }
        }

        for (auto&& mode : _vModeAdd) {
            if (!IsDelRegist(mode.get()) && mode->GetSZName() == name) { return mode.get(); }
        }

        return nullptr;
    }

    // ID取得
    int ModeServer::GetId(ModeBase* mode) {
        if (IsAdd(mode)) {
            return mode->GetUID();
        }

        return 0;
    }
    int ModeServer::GetId(const std::string name) {
        return GetId(Get(name));
    }

    // 名前取得
    const std::string ModeServer::GetName(ModeBase* mode) {
        if (IsAdd(mode)) {
            return mode->GetSZName();
        }

        return "";
    }
    const std::string ModeServer::GetName(int uid) {
        return GetName(Get(uid));
    }

    namespace {
        static bool modeSort(std::unique_ptr<ModeBase>& x, std::unique_ptr<ModeBase>& y) {
            return x->GetLayer() < y->GetLayer();
        }
    }

    // プロセスを回すための初期化
    int ModeServer::UpdateInit() {
        // 削除予約されていたものを削除
        if (_vModeDel.size() > 0) {
            auto ite = _vModeDel.begin();

            while (ite != _vModeDel.end()) {
                --_deleteDelay[(*ite)];

                if (_deleteDelay[(*ite)] < 0) {
                    Release((*ite));
                    _deleteDelay.erase((*ite));
                    ite = _vModeDel.erase(ite);
                }
                else {
                    ++ite;
                }
            }
        }

        // Add()されたものを有効にし、必要であればソートを行う
        if (_vModeAdd.size() > 0) {
            //Initialzieでモードを作成した際、配列サイズが変わってしまうため一時配列に移動
            std::vector<std::unique_ptr<ModeBase>> addArray;

            for (auto&& addMode : _vModeAdd) {
                addArray.emplace_back(std::move(addMode));
            };

            _vModeAdd.clear();

            auto ite = addArray.begin();

            for (; ite != addArray.end(); ++ite) {
                (*ite)->Initialize();
                _vMode.push_back(std::move((*ite)));
            }

            addArray.clear();
            // レイヤーによるソートを行う
            std::sort(_vMode.begin(), _vMode.end(), modeSort);
        }

        // スキップ、ポーズの解除
        _skipUpdateMode = NULL;
        _skipRenderMode = NULL;
        _pauseUpdateMode = NULL;
        return 0;
    }

    int ModeServer::Update(InputManager& input) {

        // 現在の時間を取得
        unsigned int t = GetNowCount();
        bool pause = false;

        if (_slowRate != 1.0f) {
            if (static_cast<float>((t - _slowStart) * 0.001f) > _slowDuration) {
                _slowRate = 1.0f;
                _slowDuration = 0.0f;
            }
        }

        // レイヤーの上の方から処理
        auto ite = _vMode.rbegin();

        for (; ite != _vMode.rend(); ++ite) {
            if (!IsDelRegist((*ite).get())) {
                _nowMode = (*ite).get();

                if (!pause) {
                    // 時間経過処理
                    (*ite)->StepTime(t, _slowRate);
                }

                // Processコール
                (*ite)->Update(input);

                // Modeが無い場合 (Reboot時)
                if (_vMode.empty()) {
                    break;
                }

                if (!pause) {
                    // カウンタ処理
                    (*ite)->StepCount();
                }
            }

            if (_skipUpdateMode == (*ite).get()) { break; }

            if (_pauseUpdateMode == (*ite).get()) { pause = true; }
        }


        _nowMode = NULL;

        return 0;
    }

    // プロセスを回した後の後始末
    int ModeServer::UpdateFinish() {
        return 0;
    }

    // 描画を回すための初期化
    int ModeServer::RenderInit() {
        return 0;
    }

    int ModeServer::Render() {
        // レイヤーの下の方から処理
        auto ite = _vMode.begin();

        for (; ite != _vMode.end(); ++ite) {
            if (_skipRenderMode && _skipRenderMode != (*ite).get()) { continue; }

            _skipRenderMode = NULL;

            if (IsDelRegist((*ite).get())) {
                if (_deleteDelay[(*ite).get()] <= 0) {
                    continue;
                }
            }

            _nowMode = (*ite).get();
            (*ite)->Render();
        }

        _nowMode = NULL;
        return 0;
    }

    // 描画を回した後の後始末
    int ModeServer::RenderFinish() {
        return 0;
    }

    int ModeServer::DebugInit()
    {
        return 0;
    }

    int ModeServer::Debug()
    {
        // レイヤーの下の方から処理
        auto ite = _vMode.begin();

        for (; ite != _vMode.end(); ++ite) {
            if (_skipRenderMode && _skipRenderMode != (*ite).get()) { continue; }

            _skipRenderMode = NULL;

            if (!IsDelRegist((*ite).get())) {
                _nowMode = (*ite).get();
                (*ite)->Debug();
            }
        }

        _nowMode = NULL;
        return 0;
    }

    int ModeServer::DebugFinish()
    {
        return 0;
    }



    // 今処理しているレイヤーより下のレイヤーは、処理を呼ばない
    int ModeServer::SkipUpdateUnderLayer() {
        _skipUpdateMode = _nowMode;
        return 0;
    }

    // 今処理しているレイヤーより下のレイヤーは、描画を呼ばない
    int ModeServer::SkipRenderUnderLayer() {
        _skipRenderMode = _nowMode;
        return 0;
    }


    // 今処理しているレイヤーより下のレイヤーは、時間経過を止める
    int ModeServer::PauseProcessUnderLayer() {
        _pauseUpdateMode = _nowMode;
        return 0;
    }
    void ModeServer::SetSlow(float rate, float duration)
    {
        _slowRate = rate;
        _slowDuration = duration;
        _slowStart = GetNowCount();
    }
}