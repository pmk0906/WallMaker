/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	// 仮床
	class TreasureBox : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		bool m_TreasureFlg = false;

	public:
		// 構築と破棄
		TreasureBox(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~TreasureBox();

		void DrawStrings();

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate2()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		//ゲームのクリアフラグの取得
		bool GetTreasureFlg();
		void SetTreasureFlg(bool flg);
	};
}
//end basecross
