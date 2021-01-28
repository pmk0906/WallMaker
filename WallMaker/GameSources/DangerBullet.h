#pragma once
#include "stdafx.h"

////�З͂Q�̋��͂Ȓe
namespace basecross {
	class DangerBullet : public GameObject
	{
		Vec3 dir; // �e�̈ړ�����

		const float MAX_SPEED = 25.0f;
		const float MAX_ATTACK = 5.0f;

		int m_ReflectCount;

		float m_BulletSpeed; // �e�̈ړ��X�s�\�h
		float m_Attack; // �e�̈З�
		float m_DieTime; // �e�̐�������
		float m_ReflectTime;
		float m_Damage;

		bool flg_reflectWall;
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
		void SetMaxAttack();
		void SetColor();
		void GenerateFire(int GenerateNum, Vec3 MoveSpeed);
		void GenerateFireBlue(int GenerateNum, Vec3 MoveSpeed);
		void BulletEffectRed(int GenerateNum, Vec3 MoveSpeed);
		void BulletEffectOrange(int GenerateNum, Vec3 MoveSpeed);
		void BulletEffectYellow(int GenerateNum, Vec3 MoveSpeed);
		void BulletEffectGreen(int GenerateNum, Vec3 MoveSpeed);
		void BulletEffectBlue(int GenerateNum, Vec3 MoveSpeed);
		void BulletEffectBlack(int GenerateNum, Vec3 MoveSpeed);
		void GenerateReflectEffect(int GenerateNum, Vec3 MoveSpeed);
		void SetReflectflg();

		// �Փ˔���
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		Vec3 GetPosition() const;

		Vec3 Reflect(Vec3 wall, Vec3 bullet);
	};
}