#pragma once
#include "stdafx.h"

////ˆĞ—Í‚P‚Ìˆê”Ê’e
namespace basecross {
	class RayBullet : public GameObject
	{
		Vec3 dir; // ’e‚ÌˆÚ“®•ûŒü

		float m_BulletSpeed; // ’e‚ÌˆÚ“®ƒXƒs\ƒh
		float m_DieTime; // ’e‚Ì¶‘¶ŠÔ

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

		// Õ“Ë”»’è
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		Vec3 GetPosition() const;
		bool GetRayFlg();
	};
}

