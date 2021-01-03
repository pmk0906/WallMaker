#pragma once
#include "stdafx.h"

////威力１の一般弾
namespace basecross {
	class RayBullet : public GameObject
	{
		Vec3 dir; // 弾の移動方向

		float m_BulletSpeed; // 弾の移動スピ―ド
		float m_DieTime; // 弾の生存時間

		bool flg_Ray;

		// 親オブジェクト
		const shared_ptr<GameObject>& m_Parent;

	public:
		RayBullet(
			const shared_ptr<Stage>& StagePtr,
			const shared_ptr<GameObject>& Parent
			);

		virtual ~RayBullet();

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void BulletMove();
		void Die();
		void SetDir(const Vec3& v);

		// 衝突判定
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		Vec3 GetPosition() const;
		bool GetRayFlg();
	};
}

