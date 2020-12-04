#pragma once
#include "stdafx.h"

////�З͂P�̈�ʒe
namespace basecross {
	class EnemyShield : public GameObject
	{
	public:
		EnemyShield(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{

		}

		~EnemyShield()
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void Initialize();

		Vec3 GetPosition() const;
	};
}

