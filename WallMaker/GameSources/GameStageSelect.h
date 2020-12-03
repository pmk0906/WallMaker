/*!
@file Character.h
@brief �L�����N??�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	// ����
	class GameStageSelect : public Stage
	{
		float delta = 0.0f;

		//�r���[�̍쐬
		void CreateViewLight();
		//UI�̍쐬
		void CreateTitleSprite();

		// ���̓n���h���[
		InputHandler<GameStageSelect> m_InputHandler;

	public:
		// �\�z�Ɣj��
		GameStageSelect() :Stage() {}
		virtual ~GameStageSelect() {}

		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnPushA();
		void OnPushB() {}
		void OnHoldRTrigger() {}
		void OnReleaseRTrigger() {}
	};
}
//end basecross
