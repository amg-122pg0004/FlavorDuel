/*****************************************************************//**
 * \file   CheckCollision.h
 * \brief  �R���W�����̌���������s���֐������N���X
 *
 * \author �y�������Y
 * \date   April 2023
 *********************************************************************/
#pragma once
namespace AppFrame {
    class SphereCollisionComponent;
    class AABBCollisionComponent;
    class CheckCollision
    {
    public:
        /**
         * \brief ��������
         * \param sphereLeft ����R���W����1��
         * \param sphereRight ����R���W����2��
         * \return �������Ă�����true
         */
        static bool Intersect(SphereCollisionComponent* sphereLeft, SphereCollisionComponent* sphereRight);
        /**
         * \brief ��������
         * \param sphere ����R���W����
         * \param aabb ����R���W����
         * \return �������Ă�����true
         */
        static bool Intersect(SphereCollisionComponent* sphere, AABBCollisionComponent* aabb);
        /**
         * \brief ��������
         * \param sphere ����R���W����
         * \param modelHandle 3D���f���n���h��
         * \return �������Ă�����true
         */
        static bool Intersect(SphereCollisionComponent* sphere, int modelHandle);
        /**
         * \brief ��������
         * \param aabb ����R���W����
         * \param sphere ����R���W����
         * \return �������Ă�����true
         */
        static bool Intersect(AABBCollisionComponent* aabb, SphereCollisionComponent* sphere);
        /**
         * \brief ��������
         * \param aabbLeft ����R���W����1��
         * \param aabbRight ����R���W����2��
         * \return �������Ă�����true
         */
        static bool Intersect(AABBCollisionComponent* aabbLeft, AABBCollisionComponent* aabbRight);
        /**
         * \brief ��������
         * \param modelHandle 3D���f���n���h��
         * \param sphere ����R���W����
         * \return �������Ă�����true
         */
        static bool Intersect(int modelHandle, SphereCollisionComponent* right);
    };
}