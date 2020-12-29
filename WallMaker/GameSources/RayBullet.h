#pragma once
#include "stdafx.h"

////�З͂P�̈�ʒe
namespace basecross {
	class RayBullet : public GameObject
	{
		Vec3 dir; // �e�̈ړ�����

		float m_BulletSpeed; // �e�̈ړ��X�s�\�h
		float m_DieTime; // �e�̐�������

		bool flg_Ray;

	public:
		RayBullet(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{

		}

		~RayBullet()
		{

		}

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void BulletMove();
		void Die();
		void SetDir(const Vec3& v);

		// �Փ˔���
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		Vec3 GetPosition() const;
		bool GetRayFlg();
	};
}

