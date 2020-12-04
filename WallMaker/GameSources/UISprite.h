/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
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
	///スプライト(フェードイン/アウト用)
	///-----------------------------------------------

	// 仮床
	class FadeSprite : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		//バックアップ頂点データ
		vector<VertexPositionColorTexture> m_BackupVertices;

		//フェードイン・アウト用
		bool m_FadeFlg; // true:透明状態 false:可視状態
		bool m_FadeFlgChanged = true;
		float m_AlphaValue = 0;

		int m_Layer;
		Col4 m_Color; // wは最後の透明度

		float m_AlphaLimit;

		wstring m_TextureKey;

	public:
		// 構築と破棄
		FadeSprite(
			const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec2& StartPos,
			bool FadeFlg,
			float AlphaLimit,
			const wstring TextureKey,
			const int& Layer = 0,
			const Col4& Color = Col4(1.0f, 1.0f, 1.0f, 1.0f)
		);
		virtual ~FadeSprite();

		//フェードイン・アウト切り替え
		void SwitchFadeFlg();
		void SetFadeFlgChanged(bool flg);

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	///-----------------------------------------------
	///ボタンスプライト
	///-----------------------------------------------

	// 仮床
	class ButtonSprite : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;

		Vec3 m_FirstScale;

		float m_Timer = 0.0f;
		//バックアップ頂点データ
		vector<VertexPositionColorTexture> m_BackupVertices;

		//フェードイン・アウト用
		bool m_FadeFlg; // true:透明状態 false:可視状態
		bool m_FadeFlgChanged = true;
		float m_AlphaValue = 0;

		int m_Layer;
		Col4 m_Color; // wは最後の透明度

		float m_AlphaLimit;

		wstring m_TextureKey;

		int m_SelectButtonNum = 0;
		bool m_SelectingThis = false;
		void SelectingThis();


	public:
		// 構築と破棄
		ButtonSprite(
			const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec2& StartPos,
			bool FadeFlg,
			float AlphaLimit,
			const wstring TextureKey,
			const int& SelectedButtonNum,
			const int& Layer = 0,
			const Col4& Color = Col4(1.0f, 1.0f, 1.0f, 1.0f)
		);
		virtual ~ButtonSprite();

		//フェードイン・アウト切り替え
		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross