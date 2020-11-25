#pragma once
#include "stdafx.h"

////往復する敵（上下移動）
namespace basecross {
	class PatrolEnemyUPDown : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		Col4 m_color = { 1.0f, 0.0f, 0.0f, 1.0f };

		float m_EnemyHP;
		float m_FireTime;
		float m_MoveSpeed;
		float m_MoveDirect;
		float m_TimeOfChangeDirect;

	public:
		PatrolEnemyUPDown(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~PatrolEnemyUPDown();

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void Fire();
		void Reload();
		void Move();
		void Damage(float damage);
		void Die();

		Vec3 GetPosition() const
		{
			return GetComponent<Transform>()->GetPosition();
		}
	};
}