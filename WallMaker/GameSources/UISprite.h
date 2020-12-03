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

	///-----------------------------------------------
	/// 汎用スプライト
	///-----------------------------------------------

	// 仮床
	class Sprite : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		int m_Layer;
		Col4 m_Color;

		//バックアップ頂点データ
		vector<VertexPositionColorTexture> m_BackupVertices;

		//フェードイン・アウト用
		float m_AlphaValue = 0;

		wstring m_TextureKey;

	public:
		// 構築と破棄
		Sprite(
			const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec2& StartPos,
			const wstring TextureKey,
			const int& Layer = 0,
			const Col4& Color = Col4(1.0f, 1.0f, 1.0f, 1.0f)
		);
		virtual ~Sprite();

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	///-----------------------------------------------
	///スプライト(フェードイン/アウト用)
	///-----------------------------------------------

	// 仮床
	class FadeSprite : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		//バックアップ頂点データ
		vector<VertexPositionColorTexture> m_BackupVertices;

		//フェードイン・アウト用
		bool m_FadeFlg;
		bool m_FadeFlgChanged = true;
		float m_AlphaValue = 0;

		wstring m_TextureKey;

	public:
		// 構築と破棄
		FadeSprite(
			const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos,
			bool FadeFlg,
			const wstring TextureKey
		);
		virtual ~FadeSprite();

		//フェードイン・アウト切り替え
		void SwitchFadeFlg();

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross