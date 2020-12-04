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
		void CreateButtonSprite();

		// ���̓n���h���[
		InputHandler<GameStageSelect> m_InputHandler;

		shared_ptr<SoundItem> m_BGM;

	public:
		// �\�z�Ɣj��
		GameStageSelect() :Stage() {}
		virtual ~GameStageSelect() {}

		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnPushA();
		void OnPushB();
		void OnPushDPad(int dPadNum) {};
		void OnHoldRTrigger() {}
		void OnReleaseRTrigger() {}
		void StopBGM();
	};
}
//end basecross
