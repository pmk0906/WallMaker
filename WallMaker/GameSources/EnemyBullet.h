#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyBullet : public GameObject
	{
		Vec3 dir; // ’e‚ÌˆÚ“®•ûŒü
		float moveSpeed; // ’e‚ÌˆÚ“®ƒXƒs?ƒh

	public:
		EnemyBullet(const shared_ptr<Stage>& stage)
			: GameObject(stage), moveSpeed(30.0f)
		{

		}

		~EnemyBullet()
		{

		}

		void OnCreate() override;
		void OnUpdate() override;

		Vec3 GetPosition() const
		{
			return GetComponent<Transform>()->GetPosition();
		}

		void SetDir(const Vec3& v) {
			dir = v;
		}
	};

}


