#pragma once
#include "stdafx.h"

////��C
namespace basecross {
	class Cannon : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float m_FireTime;

	public:
		Cannon(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~Cannon();

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();
		void Fire();
		void Reload();

		Vec3 GetPosition() const;
	};
}
