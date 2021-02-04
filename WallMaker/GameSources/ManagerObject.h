/*!
@file Character.h
@brief �L�����N??�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	// ����
	class ManagerObject : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		bool testFlg = false;

		float m_Timer = 0.0f;

		//�v���C���[��������t���O���ς������
		bool m_PlayerMoveFlgChanged = false;

		InputHandler<ManagerObject> m_InputHandler;

		// �V�[����ǂݍ���
		void LoadScene(int stageNum);
		//�V�[���ɓ��������̃t�F�[�h�C��
		void EnterScene();
		//�V�[������o�鎞�Ƀt�F�[�h�A�E�g
		void ExitScene();
		//�v���C���[�̍s���̋���
		void PlayerMoveEnabled();

		// �\���{�^���̑���
		void ButtonControl();

		//�G�t�F�N�g���X�e�[�W�ɓo�^����
		void StageEffect();

		//�ǂ������t���O
		bool m_WallDeleteFlg = false;
		bool m_WallDeleteFlgChanged = false;

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
		ManagerObject(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~ManagerObject();

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
