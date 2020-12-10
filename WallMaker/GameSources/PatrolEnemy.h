#pragma once
#include "stdafx.h"

////往復する敵（左右移動）
namespace basecross {
	class PatrolEnemy : public GameObject
	{
		shared_ptr<GameObject> m_Shield = nullptr;

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
		PatrolEnemy(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~PatrolEnemy();

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void Fire();
		void Reload();
		void Move();
		void Damage(float damage);
		void Die();
		void CreateShield();
		void GenerataFire(int GenerateNum, Vec3 MoveSpeed);

		Vec3 GetPosition() const;
	};
}

