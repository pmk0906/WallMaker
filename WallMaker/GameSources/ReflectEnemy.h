#pragma once
#include "stdafx.h"

////�͈͓��ɓ������v���C���[��_���e�����G
namespace basecross {
	class ReflectEnemy : public GameObject
	{
		shared_ptr<GameObject> m_Shield = nullptr;
		shared_ptr<GameObject> m_RayObject = nullptr;

		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		Col4 m_color = { 1.0f, 0.0f, 0.0f, 1.0f };

		float m_EnemyHP;
		float m_RotY;
		float m_FireTime;

		bool flg_Ray;

	public:
		ReflectEnemy(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~ReflectEnemy();

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void Fire();
		void Reload();
		void LookPlayer();
		void Damage(float damage);
		void Die();
		void CreateShield();
		void CreateRay();
		void FireEffect();
		void GenerataFire(int GenerateNum, Vec3 MoveSpeed);

		Vec3 GetPosition() const;

		float GetHp();
		float GetFireTime();

		bool GetFlgRay();
		void SetFlgRay(bool rayFlg);
	};
}
