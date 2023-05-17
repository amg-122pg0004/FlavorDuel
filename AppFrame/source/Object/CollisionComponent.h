/*****************************************************************//**
 * \file   CollisionComponent.h
 * \brief  ����R���W�����AAABB�R���W����
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "Object/ComponentBase.h"
namespace AppFrame {
	class  CollisionComponent :public ComponentBase
	{
	public:
		enum class Type {
			Sphere,
			AABB
		};
		CollisionComponent();
		~CollisionComponent();
		bool Init()override;
		void Update(InputManager& input)override;
		void Render()override;
		void Debug()override;
		bool Intersect(CollisionComponent& otherCollision, int selfIndex = 0, int otherIndex = 0);
		bool Intersect(int mv1Handle, int index = 0);

		void SetPosition(VECTOR value, int index = 0) { _params[index]._position = value; }
		VECTOR GetPosition(int index = 0) { return _params[index]._position; }
		void SetRadius(float value, int index = 0) { _params[index]._radius = value; }
		float GetRadius(int index = 0) { return _params[index]._radius; }
		void SetAttachFrame(int value, int index = 0) { _params[index]._attachFrame = value; }
		int GetAttachFrame(int index = 0) { return _params[index]._attachFrame; }
		void SetType(Type type, int index = 0) { _params[index]._type = type; }
		Type GetType(int index = 0) { return _params[index]._type; }
		void SetSize(VECTOR value, int index = 0) { _params[index]._size = value; }
		VECTOR GetSize(int index = 0) { return _params[index]._size; }
		void SetOffset(VECTOR value, int index = 0) { _params[index]._offset = value; }
		VECTOR GetOffset(int index = 0) { return _params[index]._offset; }

		void AddSphere(float radius, VECTOR _offset = { 0.0f,0.0f,0.0f });
		void AddBox(VECTOR size, VECTOR _offset = { 0.0f,0.0f,0.0f });
		//first Mix second Max
		std::pair<VECTOR, VECTOR> GetAABB(int index = 0);
	private:
		bool IntersectSphere(int mv1Handle, int index = 0);
		// mv1��Box�e�ӂ̂ǂꂩ�ɐG��Ă�����true
		bool IntersectAABB(int mv1Handle, int index = 0);

		struct Params {
			Type _type;//�`��
			VECTOR _offset;//�e�I�u�W�F�N�g�̃��[�g�A���邢�̓A�^�b�`�{�[������̈ʒu�I�t�Z�b�g��
			VECTOR _position;
			float _radius;//����R���W�����T�C�Y�p
			VECTOR _size;//����R���W�����T�C�Y�p
			int _attachFrame;//�A�^�b�`����Ă���t���[���i�{�[���̕ʏ́j
		};
		std::vector<Params> _params;
	};
}