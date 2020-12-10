#pragma once
#include "stdafx.h"

////”ÍˆÍ“à‚É“ü‚Á‚½ƒvƒŒƒCƒ„[‚ğ‘_‚¢’e‚ğŒ‚‚Â“G
namespace basecross {
	class EnemyFirst : public GameObject 
	{
		shared_ptr<GameObject> m_Shield = nullptr;

		// ‘å‚«‚³A‰ñ“]AˆÊ’u
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		Col4 m_color = { 1.0f, 0.0f, 0.0f, 1.0f };

		float m_EnemyHP;
		float m_RotY;
		float m_FireTime;

	public:
		EnemyFirst(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~EnemyFirst();

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void Fire();
		void Reload();
		void LookPlayer();
		void Damage(float damage);
		void Die();
		void CreateShield();
		void GenerataFire(int GenerateNum, Vec3 MoveSpeed);

		Vec3 GetPosition() const;

		float GetHp();
	};
}
