/*****************************************************************//**
 * \file   SoundServer.cpp
 * \brief  音声の管理を行うクラス 音量調整の為にBGM,SE,ボイスに分けて管理
 *
 * \author 土居将太郎
 * \date   January 2023
 *********************************************************************/
#include "DxLib.h"
#include "SoundServer.h"
#include "../AppFrameMath.h"
namespace AppFrame {
    std::unordered_map<std::string, int> SoundServer::_mapBGM;
    std::unordered_map<std::string, int> SoundServer::_mapSE;
    std::unordered_map<std::string, int> SoundServer::_mapVoice;
    std::unordered_map<std::string, int> SoundServer::_mapDefaultVolume;
    std::unordered_map<std::string, int> SoundServer::_softHandle;
    std::vector< SoundServer::ASyncSoundData> SoundServer::_aSyncLoadingHandles;
    float SoundServer::_bgmVolume = 1.0f;
    float SoundServer::_seVolume = 1.0f;
    float SoundServer::_voiceVolume = 1.0f;

    void SoundServer::Init() {
        _mapBGM.clear();
    }

    void SoundServer::Release() {
        ClearSounds();
    }

    void SoundServer::ClearSounds() {
        for (auto&& graph : _mapBGM) {
            DeleteGraph(graph.second);
        }

        _mapBGM.clear();
        _mapSE.clear();
        _mapVoice.clear();
    }

    void SoundServer::CheckLoad()
    {
        auto itr = _aSyncLoadingHandles.begin();

        while (itr != _aSyncLoadingHandles.end()) {
            if (CheckHandleASyncLoad((*itr).soundHandle)) {
                ++itr;
                continue;
            }

            InitializeSoundFile((*itr).soundHandle, (*itr).filename, (*itr).volumeContainer);
            itr = _aSyncLoadingHandles.erase(itr);
        }
    }

    int SoundServer::LoadSoftSound(std::string filename)
    {
        int sound = FindSound(filename, _softHandle);

        if (sound == -1) {
            sound = DxLib::LoadSoftSound(filename.c_str());
            _softHandle[filename] = sound;
        }

        return sound;
    }

    void SoundServer::StopBGM()
    {
        for (auto&& bgm : _mapBGM) {
            if (CheckSoundMem(bgm.second) == 1) {
                StopSoundMem(bgm.second);
            }
        }
    }

    int SoundServer::FindSound(std::string filename, std::unordered_map<std::string, int>& map)
    {
        auto itr = map.find(filename);

        if (itr != map.end()) {
            return itr->second;
        }

        return -1;
    }

    int SoundServer::EraseSound(std::string filename, std::unordered_map<std::string, int>& map)
    {
        auto itr = map.find(filename);

        if (itr != map.end()) {
            map.erase(itr);
            return 1;
        }

        return -1;
    }

    int SoundServer::LoadSound(std::string filename, std::unordered_map<std::string, int>& map, float& volumeContainer)
    {
        int sound = FindSound(filename, map);

        if (sound == -1) {
            sound = ::LoadSoundMem(filename.c_str());
            map[filename] = sound;

            if (GetUseASyncLoadFlag()) {
                ASyncSoundData data{ sound, filename, volumeContainer };
                _aSyncLoadingHandles.emplace_back(data);
            }
            else {
                InitializeSoundFile(sound, filename, volumeContainer);
            }
        }

        return sound;
    }

    void SoundServer::SetSoundVolume(float changeVolume, float& volumeContainer, std::unordered_map<std::string, int> map)
    {
        changeVolume = Math::Clamp(changeVolume, 0.0f, 1.0f);
        volumeContainer = changeVolume;

        for (auto&& voice : map) {
            int nextVolume = static_cast<int>(_mapDefaultVolume[voice.first] * volumeContainer);
            ChangeVolumeSoundMem(static_cast<int>(_mapDefaultVolume[voice.first] * volumeContainer), voice.second);
        }
    }
    void SoundServer::InitializeSoundFile(int soundHandle, std::string filename, float volumeContainer)
    {
        int defaultVolume = GetVolumeSoundMem2(soundHandle);
        _mapDefaultVolume[filename] = defaultVolume;
        int nextVolume = static_cast<int>(defaultVolume * volumeContainer);
        ChangeVolumeSoundMem(nextVolume, soundHandle);
    }
}