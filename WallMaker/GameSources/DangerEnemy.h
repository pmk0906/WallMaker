#pragma once
#include "stdafx.h"

////�͈͓��ɓ������v���C���[��_���e�����G
namespace basecross {
	class DangerEnemy : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		Col4 m_color = { 1.0f, 0.0f, 0.0f, 1.0f };

		float m_EnemyHP;
		float m_RotY;
		float m_FireTime;

	public:
		DangerEnemy(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~DangerEnemy();

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void Fire();
		void Reload();
		void LookPlayer();
		void Damage(float damage);
		void Die();

		Vec3 GetPosition() const
		{
			return GetComponent<Transform>()->GetPosition();
		}
	};
}

