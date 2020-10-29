/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/
	
#pragma once
#include "stdafx.h"

namespace basecross{
	// �v���C���[
	class Player : public GameObject
	{
		// �v���C���[���g�p����R���g���[���̓���
		Vec2 GetInputState() const;
		Vec3 GetMoveVector() const;
		//�v���C���[�̈ړ�
		void MovePlayer();
		//���̓n���h���[
		InputHandler<Player> m_InputHandler;
		//�X�s�[�h
		float m_Speed;

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

		// A�{�^��
		void OnPushA();
	};

}
//end basecross

