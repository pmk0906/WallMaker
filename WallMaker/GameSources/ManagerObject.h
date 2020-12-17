/*!
@file Character.h
@brief �L�����N??�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	// ����
	class GameManagement : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		bool testFlg = false;
		float m_Timer = 0.0f;
		bool m_PlayerMoveFlgChanged = false;

		InputHandler<GameManagement> m_InputHandler;

		void LoadScene(int stageNum);
		void PlayerMoveEnabled();

		void ButtonControl();
		// �J�����̕ύX
		void ChangeCamera();

		void TitleButton_A();
		void TitleButton_B() {}
		void StageSelectButton_A();
		void StageSelectButton_B();
		void GameStageButton_A();
		void GameStageButton_B() {}
		void GameStageButton_Start();


	public:
		// �\�z�Ɣj��
		GameManagement(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~GameManagement();

		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2() override;

		void OnPushA();
		void OnPushB();
		void OnPushStart();
		// RT������
		void OnHoldRTrigger() {} // �����Ă����
		void OnReleaseRTrigger() {} // �����Ă����

		void DrawStrings();
	};
}
//end basecross
