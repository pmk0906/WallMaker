/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/
	
#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------
	// �v���C���[
	//--------------------------------------------------
	class Player : public GameObject
	{
		bool m_TestFlg = false;
		int m_ArrivedWall = 0;

		//�X�s�[�h
		float m_Speed;
		float m_DefaultSpeed = 5.0f;
		float m_HoldSpeed = 3.0f;
		//HP
		float m_PlayerHp = 3.0f;
		//���񂾂��̃t���O
		bool m_PlayerDiedFlg = false;

		//�v���C���[�̓����x
		float m_Alpha = 0.0f;

		// R�g���K�[��������Ă��邩
		bool m_BeforePushRTFlg = false;
		bool m_PushRTFlg = false;

		//���g�������Ă��邩
		bool m_MotionChanged = false;
		wstring m_MotionName = L"";

		//�ǂ̃X�g�b�N
		const int m_MaxWallStock = 3;
		int m_WallStock = 3;
		bool m_wallDecreaseFlg = false;
		
		//�S�[�����̃��[�V�����p�t���O
		bool m_GoalStandFlg = false;
		// �S�[�����ɉ�]
		float m_GoalTimer = 0.0f;
		float m_GoalSpinTimer = 2.0f;
		// ���S���ɉ�]
		float m_DeathTimer = 0.0f;
		float m_DeathSpinTimer = 1.0f;
		//�@���S�������Ƃɓ|���
		float m_FallDownTimer = 0.0f;
		float m_FallDownTimeLimit = 1.0f;
		// ��]���Ɏg�p����p�x
		float m_RotY;

		//�_���[�W���󂯂����p�̃^�C�}�[
		float m_InvincibleTime = 0.0f;
		// �_���[�W��̖��G����
		float m_InvincibleTimeLimit = 0.5f;
		// �_���[�W���󂯂����̃t���O
		bool m_DamageFlg = false;
		// �_���[�W��̖��G����
		void InvincibleBehaviour();

		//�ǂ̐��𐔂���
		void SetCountWall();
		//�ǂ�S�ď���
		void WallAllDelete();

		//�`��؂�ւ�
		float m_DrawActiveLength = 37.0f;
		float m_DrawActiveFloorLength = 45.0f;
		void DrawActiveSwitch();

		// �ŏ��ɏ�ɖ��@�w���o���猩����悤�ɂ���
		void VisiblePlayer();

		//RTrigger�ɂ���
		void RTriggerHandler();
		// �v���C���[���g�p����R���g���[���̓���
		Vec2 GetInputState() const;
		Vec2 GetInputStateR() const;
		//�����̎擾
		Vec3 GetMoveVector() const;
		Vec3 GetMoveVectorR() const;
		//�v���C���[�̈ړ�
		void MovePlayer();
		Vec3 forward = Vec3(1, 0, 0);

		// ���@�ǂ̐���
		void CreateMagicWall();
		// ���[�V������o�^����
		void MotionSetting();
		//�N���A���̓���
		void ClearBehaviour();
		//���S���̓���
		void GameOverBehaviour();

		// �S�[�����[�V�����p�t���O
		bool GoalMotionEndFlg;
		float m_Timer = 0.0f;
		//���[�V�����̍X�V
		void MotionChange(wstring motionKey);
		void AnimationUpdate();
		//�S�[�����ɃJ����������
		void LookCamera();



		//���̓n���h���[
		InputHandler<Player> m_InputHandler;

		// �q�I�u�W�F�N�g
		shared_ptr<GameObject> m_MagicSkeltonWall = nullptr;

		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public :
		Player(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~Player();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		//�f�o�b�O�p
		void DrawStrings();

		//RTrigger��������Ă��邩�̃t���O���擾
		bool GetRTriggerPushFlg();

		Vec3 GetRotation() const;
		Vec3 GetPosition() const;
		//HP�̎擾
		float GetLife();
		bool GetPlayerDiedFlg();
		void SetPlayerDiedFlg(bool diedFlg);

		//�ǂ̃X�g�b�N�̎擾
		int GetWallStock();

		//�ǂ̃X�g�b�N�����炷
		void WallStockDecrease();
		void WallStockDecreaseFlg();
		//�S�Ă̕ǂ�����
		void AllWallDelete();

		//���[�V�����̖��O��o�^
		void SetMotionName(wstring motionName);
		wstring GetMotionName();

		//Damage�֐�
		void Damage(float damage);

		//����
		void Die();
		//BGM���~�߂�
		void StopBGM();

		// �{�^��
		void OnPushA();
		void OnPushB();
		void OnPushStart() {}
		// RT������
		void OnHoldRTrigger(); // �����Ă����
		void OnReleaseRTrigger(); // �����Ă����
		bool GetRTriggerFlg();
		void SetRTriggerFlg(bool triggerFlg);
	};

	//--------------------------------------------------
	// ���@��
	//--------------------------------------------------
	class MagicWall : public GameObject
	{
		float m_Hp = 1.0f;

		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		
		bool m_CollisionFlg = false;

		void Delete();

		void GenerateEffect(int GenerateNum, Vec3 MoveSpeed);

	public:
		//�\�z�Ɣj��
		MagicWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~MagicWall();
		// ������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& other)override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& other)override;

		void SetHp(float hp);
		void Damage(float damage);
	};

	//--------------------------------------------------
	// ���@��(�Œ�O)
	//--------------------------------------------------
	class MagicSkeltonWall : public GameObject
	{
		//�ǂ𐶐�����Ƃ��ɉ����Əd�Ȃ��Ă��邩�̃t���O
		bool m_CollisionFlg = false;
		// �����Ȗ��@�ǂ̉��A�s���̐؂�ւ�
		void SkeltonWallSwitch();
		void ChangeColor();

		// �e�I�u�W�F�N�g
		const shared_ptr<GameObject>& m_Parent;

		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		//�\�z�Ɣj��
		MagicSkeltonWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const shared_ptr<GameObject>& Parent
		);
		virtual ~MagicSkeltonWall();
		// ������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& other)override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& other)override;

		void DrawStrings();

		void SetCollisionFlg(bool flg);
		bool GetCollisionFlg();
		Vec3 GetScale() const;
		Vec3 GetRotation() const;
		Vec3 GetPosition() const;

	};

}
//end basecross

