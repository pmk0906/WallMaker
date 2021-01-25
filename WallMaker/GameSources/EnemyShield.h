#pragma once
#include "stdafx.h"

////ˆÐ—Í‚P‚Ìˆê”Ê’e
namespace basecross {
	class EnemyShield : public GameObject
	{
		const shared_ptr<GameObject>& m_Parent;

		float m_Hp;

	public:
		EnemyShield(const shared_ptr<Stage>& stage, const shared_ptr<GameObject>& Parent);
			
		/*{

		}*/

		~EnemyShield()
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void Initialize();
		void Damage(float damage);
		void Die();
		void DirectDie();
		void SetColor();
		void GenerataFire(int GenerateNum, Vec3 MoveSpeed);

		float GetHP() const;
		Vec3 GetPosition() const;
	};

	class PatrolShield : public GameObject
	{
		const shared_ptr<GameObject>& m_Parent;

		float m_Hp;

	public:
		PatrolShield(const shared_ptr<Stage>& stage, const shared_ptr<GameObject>& Parent);

		/*{

		}*/

		~PatrolShield()
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void Initialize();
		void Damage(float damage);
		void Die();
		void DirectDie();
		void SetColor();
		void GenerataFire(int GenerateNum, Vec3 MoveSpeed);

		float GetHP() const;
		Vec3 GetPosition() const;
	};

	class UPPatrolShield : public GameObject
	{
		const shared_ptr<GameObject>& m_Parent;

		float m_Hp;

	public:
		UPPatrolShield(const shared_ptr<Stage>& stage, const shared_ptr<GameObject>& Parent);

		/*{

		}*/

		~UPPatrolShield()
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void Initialize();
		void Damage(float damage);
		void Die();
		void DirectDie();
		void SetColor();
		void GenerataFire(int GenerateNum, Vec3 MoveSpeed);

		float GetHP() const;
		Vec3 GetPosition() const;
	};

	class RapidShield : public GameObject
	{
		const shared_ptr<GameObject>& m_Parent;

		float m_Hp;

	public:
		RapidShield(const shared_ptr<Stage>& stage, const shared_ptr<GameObject>& Parent);

		/*{

		}*/

		~RapidShield()
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void Initialize();
		void Damage(float damage);
		void Die();
		void DirectDie();
		void SetColor();
		void GenerataFire(int GenerateNum, Vec3 MoveSpeed);

		float GetHP() const;
		Vec3 GetPosition() const;
	};

	class DangerShield : public GameObject
	{
		const shared_ptr<GameObject>& m_Parent;

		float m_Hp;

	public:
		DangerShield(const shared_ptr<Stage>& stage, const shared_ptr<GameObject>& Parent);

		/*{

		}*/

		~DangerShield()
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void Initialize();
		void Damage(float damage);
		void Die();
		void DirectDie();
		void SetColor();
		void GenerataFire(int GenerateNum, Vec3 MoveSpeed);

		float GetHP() const;
		Vec3 GetPosition() const;
	};

	class ReflectShield : public GameObject
	{
		const shared_ptr<GameObject>& m_Parent;

		float m_Hp;

	public:
		ReflectShield(const shared_ptr<Stage>& stage, const shared_ptr<GameObject>& Parent);

		/*{

		}*/

		~ReflectShield()
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void Initialize();
		void Damage(float damage);
		void Die();
		void DirectDie();
		void SetColor();
		void GenerataFire(int GenerateNum, Vec3 MoveSpeed);

		float GetHP() const;
		Vec3 GetPosition() const;
	};
}

