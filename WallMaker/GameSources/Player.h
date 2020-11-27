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
		//HP
		float m_PlayerHp = 3.0f;
		// R�g���K�[��������Ă��邩
		bool m_BeforePushRTFlg = false;
		bool m_PushRTFlg = false;

		//�ǂ̃X�g�b�N
		const int m_MaxWallStock = 3;
		int m_WallStock = 3;
		bool m_wallDecreaseFlg = false;

		//�ǂ̐��𐔂���
		void SetCountWall();

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
		void MovePlayer2();
		Vec3 forward = Vec3(1, 0, 0);

		// ���@�ǂ̐���
		void CreateMagicWall();
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
		//�ǂ̃X�g�b�N�̎擾
		int GetWallStock();

		//�ǂ̃X�g�b�N�����炷
		void WallStockDecrease();
		void WallStockDecreaseFlg();

		//Damage�֐�
		void Damage(float damage);

		//����
		void Die();

		// �{�^��
		void OnPushA();
		void OnPushB();
		// RT������
		void OnHoldRTrigger(); // �����Ă����
		void OnReleaseRTrigger(); // �����Ă����
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

		void Delete();

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

