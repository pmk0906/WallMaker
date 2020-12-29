#pragma once
#include "stdafx.h"

////�͈͓��ɓ������v���C���[��_���e�����G
namespace basecross {
	class RayObject : public GameObject
	{
		float m_RotY;
		float m_FireTime;

		bool flg_Ray;
	public:
		RayObject(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{

		}

		~RayObject()
		{

		}

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void Fire();
		void LookPlayer();
		void Reload();

		Vec3 GetPosition() const;
		bool GetRayFlg();
	};
}

