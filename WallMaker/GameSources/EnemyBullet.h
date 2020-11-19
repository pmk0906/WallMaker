#pragma once
#include "stdafx.h"

////ˆĞ—Í‚P‚Ìˆê”Ê’e
namespace basecross {
	class EnemyBullet : public GameObject
	{
		Vec3 dir; // ’e‚ÌˆÚ“®•ûŒü

		float m_BulletSpeed; // ’e‚ÌˆÚ“®ƒXƒs\ƒh
		float m_Attack; // ’e‚ÌˆĞ—Í
		float m_DieTime; // ’e‚Ì¶‘¶ŠÔ

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

		// Õ“Ë”»’è
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
