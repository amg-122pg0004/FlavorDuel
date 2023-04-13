/*****************************************************************//**
 * \file   MV1Component.cpp
 * \brief  MV1�̃g�����X�t�H�[���X�V�A�`��A�A�j���[�V�����t���[���̐i�s�@�\
 *
 * \author �y�������Y
 * \date   November 2022
 *********************************************************************/
#include "MV1Component.h"
#include "ObjectBase.h"
#include "../Mode/ModeBase.h"
#include "ApplicationBase.h"
#include "BlurRenderer.h"
#include "ChangeScreen.h"
#include <sstream>
namespace AppFrame {
    MV1Component::MV1Component(int modelHandle)
        :_modelHandle{ modelHandle }
        , _attahIndex{ -1 }
        , _playTime{ 0.0f }
        , _totalTime{ 0.0f }
        , _animSpeed{ 60.0f }
        , _animIndex{ -1 }
        , _isValid{ true }
        , _useOriginalShader{ false }
        , _vertexShader{ -1 }
        , _pixelShader{ -1 }
        , _bloom{ false }
    {
        int animNumber = MV1GetAnimNum(_modelHandle);
        _animFunction.clear();
        _animFunction.resize(animNumber);

        _constantBufferArray.clear();
    }

    MV1Component::~MV1Component()
    {
        for (auto&& handle : _constantBufferArray) {
            DeleteShaderConstantBuffer(handle._bufferHandle);
        }

        DeleteShader(_vertexShader);
        DeleteShader(_pixelShader);
        MV1DeleteModel(_modelHandle);
    }

    bool MV1Component::Init()
    {
        MV1SetScale(_modelHandle, _parent->GetScale());
        MV1SetRotationXYZ(_modelHandle, _parent->GetRotation());
        MV1SetPosition(_modelHandle, _parent->GetPosition());
        return true;
    }

    void MV1Component::Update(InputManager& input)
    {
        if (_attahIndex == -1) {
            return;
        }

        float preTime = _playTime;

        if (_isValid) {
            _playTime += _parent->GetMode()->GetStepTime() * 0.001f * _animSpeed;
        }

        CheckAnimFunction(preTime, _playTime);

        if (_playTime >= _totalTime) {
            _playTime = 0.0f;
        }
    }

    void MV1Component::Render()
    {
        if (!_parent->GetVisible()) {
            return;
        }

        if (_useOriginalShader) {
            SetShader();
        }

        MV1SetScale(_modelHandle, _parent->GetScale());
        MV1SetRotationXYZ(_modelHandle, _parent->GetRotation());
        MV1SetPosition(_modelHandle, _parent->GetPosition());
        MV1SetAttachAnimTime(_modelHandle, _attahIndex, _playTime);

        bool skinMesh{ false };

        if (_attahIndex != -1) {
            skinMesh = true;
        }

        if (!_parent->GetMode()->GetBlurFlag() || _parent->GetLayer() > 9) {
            MV1DrawModel(_modelHandle);
            ChangeScreen::ChangeScreenAndSaveCamera(_parent->GetMode()->GetPostProcess()->GetOutputScreen());
            MV1SetUseOrigShader(false);
            return;
        }

        if (_bloom) {
            auto camera = ChangeScreen::GetCameraParam();

            _parent->GetMode()->GetPostProcess()->DrawBlurBuffer(_modelHandle, skinMesh);

            SetDrawScreen(_parent->GetMode()->GetPostProcess()->GetOutputScreen());
            ChangeScreen::SetCameraParam(camera);
        }
        else {
            _parent->GetMode()->GetPostProcess()->DrawNotBlurBuffer(_modelHandle, skinMesh);
        }
    }
    void MV1Component::Debug()
    {

    }

    void MV1Component::SetModelHandle(int modelHandle)
    {
        _modelHandle = modelHandle;
        int animNumber = MV1GetAnimNum(modelHandle);
        _animFunction.clear();
        _animFunction.resize(animNumber);
    }

    void MV1Component::SetAnimation(int index)
    {
        _isValid = true;
        MV1DetachAnim(_modelHandle, _attahIndex);
        _animIndex = index;
        _attahIndex = MV1AttachAnim(_modelHandle, _animIndex, -1, true);
        _totalTime = MV1GetAttachAnimTotalTime(_modelHandle, _attahIndex);
        _playTime = 0.0f;
    }

    void MV1Component::AddAnimFunction(int animIndex, float activateTime, std::function<void(void)> function)
    {
        if (_animFunction.size() - 1 < animIndex) {
            return;
        }

        _animFunction[animIndex].push_back({ activateTime, function });

        typedef std::pair<float, std::function<void(void)>> AnimFuncType;
        auto sortAnimFunc = [](AnimFuncType lhs, AnimFuncType rhs) {return lhs.first < rhs.first; };

        std::sort(_animFunction[animIndex].begin(), _animFunction[animIndex].end(), sortAnimFunc);
    }

    void MV1Component::SetOriginalShader(const CHAR* vertexShaderPath, const CHAR* pixelShaderPath)
    {
        _vertexShader = LoadVertexShader(vertexShaderPath);
        _pixelShader = LoadPixelShader(pixelShaderPath);

        if (_vertexShader != -1 && _pixelShader != -1) {
            _useOriginalShader = true;
        }
    }

    void MV1Component::AddShaderBuffer(std::function<FLOAT4()> func, bool usePixelShader)
    {
        shaderBuffer addBuffer;
        SetUseVertexShader(_vertexShader);
        SetUsePixelShader(_pixelShader);
        addBuffer._bufferHandle = CreateShaderConstantBuffer(sizeof(float) * 4);
        addBuffer._getter = func;
        addBuffer._usePixelShader = usePixelShader;
        int size = static_cast<int>(_constantBufferArray.size());
        addBuffer._slot = size + 2;
        _constantBufferArray.emplace_back(addBuffer);
    }

    void MV1Component::CheckAnimFunction(float preTime, float nowTime)
    {
        for (auto&& func : _animFunction[_animIndex]) {
            if (func.first > preTime && func.first <= nowTime) {
                func.second();
            }
        }
    }

    void MV1Component::SetShader()
    {
        SetUseVertexShader(_vertexShader);
        SetUsePixelShader(_pixelShader);
        MV1SetUseOrigShader(true);

        if (static_cast<int>(_constantBufferArray.size()) > 0) {
            for (auto&& handle : _constantBufferArray) {
                auto bufferAdress = (FLOAT4*)GetBufferShaderConstantBuffer(handle._bufferHandle);
                FLOAT4 value = handle._getter();

                *bufferAdress = value;
                UpdateShaderConstantBuffer(handle._bufferHandle);

                auto type = DX_SHADERTYPE_VERTEX;

                if (handle._usePixelShader) {
                    type = DX_SHADERTYPE_PIXEL;
                }

                SetShaderConstantBuffer(handle._bufferHandle, type, handle._slot);
            }
        }
    }

}