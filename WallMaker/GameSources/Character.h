/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	// 仮床
	class FixedBox : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		// 構築と破棄
		FixedBox(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~FixedBox();

		// 初期化
		virtual void OnCreate()override;
	};

}
//end basecross
