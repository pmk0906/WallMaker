#pragma once
#include "stdafx.h"

////ˆĞ—Í‚P‚Ìˆê”Ê’e
namespace basecross {
	class EnemyBullet : public GameObject
	{
		Vec3 dir; // ’e‚ÌˆÚ“®•ûŒü

		const float MAX_SPEED = 25.0f;
		const float MAX_ATTACK = 5.0f;

		float m_BulletSpeed; // ’e‚ÌˆÚ“®ƒXƒs\ƒh
		float m_Attack; // ’e‚ÌˆĞ—Í
		float m_DieTime; // ’e‚Ì¶‘¶ŠÔ
		float m_ReflectTime;

		bool flg_reflect;
		bool flg_reflectWall;

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

		// Õ“Ë”»’è
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		Vec3 GetPosition() const;

		Vec3 Reflect(Vec3 wall, Vec3 bullet);
	};
}
