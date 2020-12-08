#pragma once
#include "stdafx.h"

////�З͂P�̈�ʒe
namespace basecross {
	class EnemyBullet : public GameObject
	{
		Vec3 dir; // �e�̈ړ�����

		const float MAX_SPEED = 25.0f;
		const float ATTACK = 1.0f;

		float m_BulletSpeed; // �e�̈ړ��X�s�\�h
		float m_Attack; // �e�̈З�
		float m_DieTime; // �e�̐�������
		float m_ReflectTime;

		bool flg_reflect;

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
		void SetDir(const Vec3& v);
		void SetMaxSpeed();
		void SetColor();

		// �Փ˔���
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		Vec3 GetPosition() const;

		Vec3 Reflect(Vec3 wall, Vec3 bullet);
	};
}
