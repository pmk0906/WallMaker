#pragma once
#include "stdafx.h"

////�З͂Q�̋��͂Ȓe
namespace basecross {
	class DangerBullet : public GameObject
	{
		Vec3 dir; // �e�̈ړ�����

		const float MAX_SPEED = 30.0f;
		const float ATTACK = 2.0f;

		int m_ReflectCount;

		float m_BulletSpeed; // �e�̈ړ��X�s�\�h
		float m_Attack; // �e�̈З�
		float m_DieTime; // �e�̐�������

		bool flg_reflect;

	public:
		DangerBullet(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{

		}

		~DangerBullet()
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

