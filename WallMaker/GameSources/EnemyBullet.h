#pragma once
#include "stdafx.h"

////�З͂P�̈�ʒe
namespace basecross {
	class EnemyBullet : public GameObject
	{
		Vec3 dir; // �e�̈ړ�����

		float m_BulletSpeed; // �e�̈ړ��X�s�\�h
		float m_Attack; // �e�̈З�
		float m_DieTime; // �e�̐�������

	public:
		EnemyBullet(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{

		}

		~EnemyBullet()
		{

		}

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void BulletMove();
		void Die();

		// �Փ˔���
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		Vec3 GetPosition() const
		{
			return GetComponent<Transform>()->GetPosition();
		}

		void SetDir(const Vec3& v) {
			dir = v;
		}
	};
}
