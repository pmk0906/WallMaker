#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyFirst : public GameObject 
	{
		// ëÂÇ´Ç≥ÅAâÒì]ÅAà íu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		Col4 m_color = { 1.0f, 0.0f, 0.0f, 1.0f };

		float m_EnemyHP;
		float m_rotY;

	public:
		EnemyFirst(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~EnemyFirst();

		void OnCreate() override;
		void OnUpdate() override;

		void Initialize();

		Vec3 GetPosition() const
		{
			return GetComponent<Transform>()->GetPosition();
		}
	};
}
