/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	// �v���C���[
	// �\�z�Ɣj��
	Player::Player(
		const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position)
		:
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Speed(6.0f)
	{
	}
	Player::~Player() {}

	Vec2 Player::GetInputState() const{
		Vec2 ret;
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		return ret;
	}
	Vec3 Player::GetMoveVector() const{
		Vec3 angle(0, 0, 0);
		// ���͂̎擾
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0; // �������Ƃ��̃X�s�[�h
			auto ptrTrans = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//�i�s�����̌������v�Z
			auto front = ptrTrans->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//�i�s�����̌�������̊p�x���Z�o
			float frontAngle = atan2(front.z, front.x);
			//�R���g���[���̌����v�Z
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//�R���g���[���̌�������p�x���v�Z
			float cntlAngle = atan2(-moveX, moveZ);
			// �g�[�^���̊p�x���Z�o
			float totalAngle = frontAngle + cntlAngle;
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			// ���K������
			angle.normalize();
			//�ړ��T�C�Y��ݒ�
			angle *= moveSize;
			// Y���͕ω������Ȃ�
			angle.y = 0;
		}
		return angle;
	}

	void Player::MovePlayer(){
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f){
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
		}
		if (angle.length() > 0.0f){
			auto utiPtr = GetBehavior<UtilBehavior>();
			utiPtr->RotToHead(angle, 1.0f);
		}
	}

	void Player::OnCreate()
	{
		auto ptrTrans = AddComponent<Transform>();
		ptrTrans->SetScale(Vec3(m_Scale.x, m_Scale.y, m_Scale.z));
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(Vec3(m_Position.x, m_Position.y, m_Position.z));
		
		//CollisionSphere�Փ˔����t����
		auto ptrCollision = AddComponent<CollisionSphere>();

		//�d�͂�t����
		auto prtGra = AddComponent<Gravity>();

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CAPSULE");

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		ptrDraw->SetFogEnabled(true);
		//�`�悷��e�N�X�`����ݒ�
		ptrDraw->SetTextureResource(L"TRACE_TX");
		SetAlphaActive(true);
	}

	void Player::OnUpdate()
	{
		////�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();
	}

	void Player::OnPushA()
	{

	}
}
//end basecross

