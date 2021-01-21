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
		void EnterScene();
		void ExitScene();
		void PlayerMoveEnabled();
		void ClearCheck();

		//�\���L�[�p
		void ButtonControl();

		//�G�t�F�N�g���X�e�[�W�ɓo�^����
		void StageEffect();

		//�t�F�[�h�C���E�A�E�g
		void CreateFadeIn(wstring textureKey, Col4 color);
		void CreateFadeOut(wstring textureKey, Col4 color);
		shared_ptr<GameObject> m_FadeSprite;

		//�V�[�����̃{�^���̏���
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

		// �J�����̕ύX
		void ChangeCamera();

		void DrawStrings();
	};
}
//end basecross
