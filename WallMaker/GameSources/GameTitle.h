/*!
@file Character.h
@brief �L�����N??�Ȃ�
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

		//�j��
		virtual ~TitleSprite();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override {}
	};

	// ����
	class GameTitle : public Stage
	{
		//�r���[�̍쐬
		void CreateViewLight();
		//UI�̍쐬
		void CreateTitleSprite();

		// ���̓n���h���[
		InputHandler<GameTitle> m_InputHandler;

	public:
		// �\�z�Ɣj��
		GameTitle() :Stage() {}
		virtual ~GameTitle() {}

		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnPushA();
		void OnPushB();
		void OnHoldRTrigger() {}
		void OnReleaseRTrigger() {}
	};
}
//end basecross
