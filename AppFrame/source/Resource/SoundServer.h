/*****************************************************************//**
 * \file   SoundServer.h
 * \brief  音声の管理を行うクラス 音量調整の為にBGM,SE,ボイスに分けて管理
 *
 * \author 土居将太郎
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <string>
#include <unordered_map>
#include <tchar.h>
namespace AppFrame {
    class SoundServer {
    public:
        static void Init();//<_mapGraphの初期化
        static void Release();//<ClearGraph呼び出し
        static void ClearSounds();//<_mapGraphデータの全削除
        static void CheckLoad();//読み込み完了したら音量の変更・登録を行う

        /**
         * \brief 読み込み済のファイルでなければmapに登録
         *
         * \param filename 読み込むファイル名
         * \return 読み込んだ値、読み込み済みなら-1を返す
         */
        static int LoadBGM(std::string filename) { return LoadSound(filename, _mapBGM, _bgmVolume); }
        /**
        * \brief 読み込み済のファイルでなければmapに登録
        *
        * \param filename 読み込むファイル名
        * \return 読み込んだ値、読み込み済みなら-1を返す
        */
        static int LoadSE(std::string filename) { return LoadSound(filename, _mapSE, _seVolume); }
        /**
        * \brief 読み込み済のファイルでなければmapに登録
        *
        * \param filename 読み込むファイル名
        * \return 読み込んだ値、読み込み済みなら-1を返す
        */
        static int LoadVoice(std::string filename) { return LoadSound(filename, _mapVoice, _voiceVolume); }
        /**
        * \brief 読み込み済のファイルでなければmapに登録
        *
        * \param filename 読み込むファイル名
        * \return 読み込んだ値、読み込み済みなら-1を返す
        */
        static int LoadSoftSound(std::string filename);
        /**
         * \brief _mapGraphのキー検索
         *
         * \param filename 検索するキー名
         * \return キーに対応した値を返す
         */
        static int FindBGM(std::string filename) { return FindSound(filename, _mapBGM); }
        /**
        * \brief _mapBGMのキー検索
        *
        * \param filename 検索するキー名
        * \return キーに対応した値を返す
        */
        static int FindSE(std::string filename) { return FindSound(filename, _mapSE); }
        /**
        * \brief _mapVoiceのキー検索
        *
        * \param filename 検索するキー名
        * \return キーに対応した値を返す
        */
        static int FindVoice(std::string filename) { return FindSound(filename, _mapVoice); }

        static int EraseBGM(std::string filename) { return EraseSound(filename, _mapBGM); }
        static int EraseSE(std::string filename) { return EraseSound(filename, _mapSE); }
        static int EraseVoice(std::string filename) { return EraseSound(filename, _mapVoice); }


        /* \brief BGMのボリュームを設定する　(0.0f~1.0f 1.0は音声ファイル元々の音量)*/
        static void SetBGMVolume(float volume) { SetSoundVolume(volume, _bgmVolume, _mapBGM); }
        /* \brief SEのボリュームを設定する　(0.0f~1.0f 1.0は音声ファイル元々の音量)*/
        static void SetSEVolume(float volume) { SetSoundVolume(volume, _seVolume, _mapSE); }
        /* \brief ボイスのボリュームを設定する　(0.0f~1.0f 1.0は音声ファイル元々の音量)*/
        static void SetVoiceVolume(float volume) { SetSoundVolume(volume, _voiceVolume, _mapVoice); }

        static float GetBGMVolume() { return _bgmVolume; }
        static float GetSEVolume() { return _seVolume; }
        static float GetVoiceVolume() { return _voiceVolume; }

        static void StopBGM();
    private:
        static int FindSound(std::string filename, std::unordered_map<std::string, int>& map);
        static int EraseSound(std::string filename, std::unordered_map<std::string, int>& map);
        static int LoadSound(std::string filename, std::unordered_map<std::string, int>& map, float& volumeContainer);
        //音声ファイルのデフォルト音量の保存と設定ボリュームの適用
        static void InitializeSoundFile(int soundHandle, std::string filename, float volumeContainer);
        static void SetSoundVolume(float changeVolume, float& volumeContainer, std::unordered_map<std::string, int> map);


        static std::unordered_map<std::string, int> _mapBGM;
        static std::unordered_map<std::string, int> _mapSE;
        static std::unordered_map<std::string, int> _mapVoice;
        static std::unordered_map<std::string, int> _mapDefaultVolume;
        static std::unordered_map<std::string, int> _softHandle;
        struct ASyncSoundData {
            int soundHandle;
            std::string filename;
            float volumeContainer;
        };
        static std::vector<ASyncSoundData> _aSyncLoadingHandles;//非同期読み込み中のBGMデータ

        static float _bgmVolume;
        static float _seVolume;
        static float _voiceVolume;
    };

}