/*****************************************************************//**
 * \file   SoundServer.h
 * \brief  �����̊Ǘ����s���N���X ���ʒ����ׂ̈�BGM,SE,�{�C�X�ɕ����ĊǗ�
 *
 * \author �y�������Y
 * \date   January 2023
 *********************************************************************/
#pragma once
#include <string>
#include <unordered_map>
#include <tchar.h>
namespace AppFrame {
    class SoundServer {
    public:
        static void Init();//<_mapGraph�̏�����
        static void Release();//<ClearGraph�Ăяo��
        static void ClearSounds();//<_mapGraph�f�[�^�̑S�폜
        static void CheckLoad();//�ǂݍ��݊��������特�ʂ̕ύX�E�o�^���s��

        /**
         * \brief �ǂݍ��ݍς̃t�@�C���łȂ����map�ɓo�^
         *
         * \param filename �ǂݍ��ރt�@�C����
         * \return �ǂݍ��񂾒l�A�ǂݍ��ݍς݂Ȃ�-1��Ԃ�
         */
        static int LoadBGM(std::string filename) { return LoadSound(filename, _mapBGM, _bgmVolume); }
        /**
        * \brief �ǂݍ��ݍς̃t�@�C���łȂ����map�ɓo�^
        *
        * \param filename �ǂݍ��ރt�@�C����
        * \return �ǂݍ��񂾒l�A�ǂݍ��ݍς݂Ȃ�-1��Ԃ�
        */
        static int LoadSE(std::string filename) { return LoadSound(filename, _mapSE, _seVolume); }
        /**
        * \brief �ǂݍ��ݍς̃t�@�C���łȂ����map�ɓo�^
        *
        * \param filename �ǂݍ��ރt�@�C����
        * \return �ǂݍ��񂾒l�A�ǂݍ��ݍς݂Ȃ�-1��Ԃ�
        */
        static int LoadVoice(std::string filename) { return LoadSound(filename, _mapVoice, _voiceVolume); }
        /**
        * \brief �ǂݍ��ݍς̃t�@�C���łȂ����map�ɓo�^
        *
        * \param filename �ǂݍ��ރt�@�C����
        * \return �ǂݍ��񂾒l�A�ǂݍ��ݍς݂Ȃ�-1��Ԃ�
        */
        static int LoadSoftSound(std::string filename);
        /**
         * \brief _mapGraph�̃L�[����
         *
         * \param filename ��������L�[��
         * \return �L�[�ɑΉ������l��Ԃ�
         */
        static int FindBGM(std::string filename) { return FindSound(filename, _mapBGM); }
        /**
        * \brief _mapBGM�̃L�[����
        *
        * \param filename ��������L�[��
        * \return �L�[�ɑΉ������l��Ԃ�
        */
        static int FindSE(std::string filename) { return FindSound(filename, _mapSE); }
        /**
        * \brief _mapVoice�̃L�[����
        *
        * \param filename ��������L�[��
        * \return �L�[�ɑΉ������l��Ԃ�
        */
        static int FindVoice(std::string filename) { return FindSound(filename, _mapVoice); }

        static int EraseBGM(std::string filename) { return EraseSound(filename, _mapBGM); }
        static int EraseSE(std::string filename) { return EraseSound(filename, _mapSE); }
        static int EraseVoice(std::string filename) { return EraseSound(filename, _mapVoice); }


        /* \brief BGM�̃{�����[����ݒ肷��@(0.0f~1.0f 1.0�͉����t�@�C�����X�̉���)*/
        static void SetBGMVolume(float volume) { SetSoundVolume(volume, _bgmVolume, _mapBGM); }
        /* \brief SE�̃{�����[����ݒ肷��@(0.0f~1.0f 1.0�͉����t�@�C�����X�̉���)*/
        static void SetSEVolume(float volume) { SetSoundVolume(volume, _seVolume, _mapSE); }
        /* \brief �{�C�X�̃{�����[����ݒ肷��@(0.0f~1.0f 1.0�͉����t�@�C�����X�̉���)*/
        static void SetVoiceVolume(float volume) { SetSoundVolume(volume, _voiceVolume, _mapVoice); }

        static float GetBGMVolume() { return _bgmVolume; }
        static float GetSEVolume() { return _seVolume; }
        static float GetVoiceVolume() { return _voiceVolume; }

        static void StopBGM();
    private:
        static int FindSound(std::string filename, std::unordered_map<std::string, int>& map);
        static int EraseSound(std::string filename, std::unordered_map<std::string, int>& map);
        static int LoadSound(std::string filename, std::unordered_map<std::string, int>& map, float& volumeContainer);
        //�����t�@�C���̃f�t�H���g���ʂ̕ۑ��Ɛݒ�{�����[���̓K�p
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
        static std::vector<ASyncSoundData> _aSyncLoadingHandles;//�񓯊��ǂݍ��ݒ���BGM�f�[�^

        static float _bgmVolume;
        static float _seVolume;
        static float _voiceVolume;
    };

}