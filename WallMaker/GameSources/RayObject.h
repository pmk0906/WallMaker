#pragma once
#include "stdafx.h"

////範囲内に入ったプレイヤーを狙い弾を撃つ敵
namespace basecross {
	class RayObject : public GameObject
	{
		float m_RotY;
		float m_FireTime;

		bool flg_Ray = false;

		// 親オブジェクト
		const shared_ptr<GameObject>& m_Parent;
	public:
		RayObject(
			const shared_ptr<Stage>& StagePtr,
			const shared_ptr<GameObject>& Parent
		);
		virtual ~RayObject();

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void Fire();
		void LookPlayer();
		void Reload();

		Vec3 GetPosition() const;
		bool GetRayFlg();
		void SetRayFlg(bool rayFlg);

		void SetParentRayFlg(bool rayFlg);
	};
}

