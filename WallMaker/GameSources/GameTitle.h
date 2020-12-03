/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class TitleSprite : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
	public:
		TitleSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);

		//破棄
		virtual ~TitleSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override {}
	};

	// 仮床
	class GameTitle : public Stage
	{
		//ビューの作成
		void CreateViewLight();
		//UIの作成
		void CreateTitleSprite();

		// 入力ハンドラー
		InputHandler<GameTitle> m_InputHandler;

	public:
		// 構築と破棄
		GameTitle() :Stage() {}
		virtual ~GameTitle() {}

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnPushA();
		void OnPushB();
		void OnHoldRTrigger() {}
		void OnReleaseRTrigger() {}
	};
}
//end basecross
