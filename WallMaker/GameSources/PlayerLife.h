/*!
@file Character.h
@brief ƒLƒƒƒ‰ƒN??‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	// ‰¼°
	class PlayerLife : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;

	public:
		// \’z‚Æ”jŠü
		PlayerLife(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~PlayerLife();

		// ‰Šú‰»
		virtual void OnCreate()override;
	};
}
//end basecross
