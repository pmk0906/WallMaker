#pragma once
#include "stdafx.h"

////範囲内に入ったプレイヤーをロックオンして３連射する敵
namespace basecross {
	class RapidFireEnemy : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		Col4 m_color = { 1.0f, 0.0f, 0.0f, 1.0f };

		float m_EnemyHP;
		float m_RotY;
		float m_FireTime;
		float m_LockOnTime;

		int m_FireCount;

		bool flg_LockOn;

	public:
		RapidFireEnemy(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~RapidFireEnemy();

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void Fire();
		void Reload();
		void LookPlayer();
		void LockOn();
		void Damage(float damage);
		void Die();

		Vec3 GetPosition() const
		{
			return GetComponent<Transform>()->GetPosition();
		}
	};
}

