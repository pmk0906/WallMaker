#pragma once
#include "stdafx.h"

////�͈͓��ɓ������v���C���[�����b�N�I�����ĂR�A�˂���G
namespace basecross {
	class RapidFireEnemy : public GameObject
	{
		// �傫���A��]�A�ʒu
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

