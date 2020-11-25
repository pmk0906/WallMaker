/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	///-----------------------------------------------
	/// プレイヤーのライフ
	///-----------------------------------------------
	// 仮床
	class PlayerLife : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		//バックアップ頂点データ
		vector<VertexPositionColorTexture> m_BackupVertices;

		wstring m_TextureKey;

		int m_LifeNum;

	public:
		// 構築と破棄
		PlayerLife(
			const shared_ptr<Stage>& StagePtr, 
			bool Trace,
			const Vec2& StartScale, 
			const Vec3& StartPos,
			const int LifeNum
		);
		virtual ~PlayerLife();

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	///-----------------------------------------------
	/// 使える壁の数
	///-----------------------------------------------

	// 仮床
	class WallStock : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		//バックアップ頂点データ
		vector<VertexPositionColorTexture> m_BackupVertices;

		wstring m_TextureKey;

		int m_WallNum;

	public:
		// 構築と破棄
		WallStock(
			const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos,
			const int WallNum
		);
		virtual ~WallStock();

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
//end basecross
