/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------
	// �v���C���[
	//--------------------------------------------------
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

	//�ǂ̃X�g�b�N����
	void Player::WallStockDecrease()
	{
		if (m_wallDecreaseFlg == true)
		{
			m_WallStock = m_WallStock - 1;
			m_wallDecreaseFlg = false;
		}

	}
	void Player::WallStockDecreaseFlg()
	{
		m_wallDecreaseFlg = true;
	}

	void Player::Damage(float damage)
	{
		m_PlayerHp -= damage;
	}

	void Player::Die()
	{
		if (m_PlayerHp <= 0.0f)
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	// RTrigger�t���O�؂�ւ�
	void Player::RTriggerHandler()
	{
		if (m_BeforePushRTFlg != m_PushRTFlg)
		{
			m_BeforePushRTFlg = m_PushRTFlg;

		}
	}

	// �v���C���[���g�p����R���g���[���̓���
	Vec2 Player::GetInputState() const
	{
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
	Vec2 Player::GetInputStateR() const
	{
		Vec2 ret;
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbRX;
			ret.y = cntlVec[0].fThumbRY;
		}
		return ret;
	}
	//�ړ��x�N�g���̎擾
	Vec3 Player::GetMoveVector() const
	{
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
	Vec3 Player::GetMoveVectorR() const
	{
		Vec3 angleR(0, 0, 0);
		// ���͂̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		float fThumbRY = 0.0f;
		float fThumbRX = 0.0f;
		if (cntlVec.bConnected) {
			fThumbRX = cntlVec.fThumbRX;
			fThumbRY = cntlVec.fThumbRY;
		}
		if (fThumbRX != 0 || fThumbRY != 0) {

			auto ptrTrans = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//�i�s�����̌������v�Z
			auto front = ptrTrans->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//�i�s�����̌�������̊p�x���Z�o
			float frontAngle = atan2(front.z, front.x);
			//�R���g���[���̌����v�Z
			auto moveX = fThumbRX;
			auto moveZ = fThumbRY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//�R���g���[���̌�������p�x���v�Z
			float cntlAngle = atan2(-moveX, moveZ);
			// �g�[�^���̊p�x���Z�o
			float totalAngle = frontAngle + cntlAngle;
			angleR = Vec3(cos(totalAngle), 0, sin(totalAngle));
			// ���K������
			angleR.normalize();
			//�ړ��T�C�Y��ݒ�
			angleR *= moveSize;
			// Y���͕ω������Ȃ�
			angleR.y = 0;
		}
		return angleR;
	}

	void Player::MovePlayer()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f){
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);

			auto utiPtr = GetBehavior<UtilBehavior>();
			utiPtr->RotToHead(angle, 1.0f);
		
		}
		auto angleR = GetMoveVectorR();
		if (angleR.length() > 0.0f) {

			auto utiPtr = GetBehavior<UtilBehavior>();
			utiPtr->RotToHead(angleR, 1.0f);
		}
	}
	void Player::MovePlayer2() {

		// �O�̃t���[������̌o�ߎ��Ԃ��擾����i�P�ʁF�b�j
		float delta = App::GetApp()->GetElapsedTime();

		auto device = App::GetApp()->GetInputDevice(); // ���͑��u���擾����
		auto pad = device.GetControlerVec()[0]; // ���͑��u�̒�����O�Ԗڂ̃p�b�h���擾����

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition(); // �����݂̍��W���擾����

		float PlayerSpeed = 10.0f;

		// ���ꂼ��̍��W(XYZ)�Ɉړ��ʂ�������
		pos.x += PlayerSpeed * pad.fThumbLX * delta; // �b��5���ړ�
		//pos.y = 1.0f;
		pos.z += PlayerSpeed * pad.fThumbLY * delta;

		// �X�e�B�b�N���|��Ă����炻�̌����ɉ�]������
		if (pad.fThumbLX != 0.0f && pad.fThumbLY != 0.0f) {
			// atan2f�֐���p���āA�X�e�B�b�N��XY�����W�A���p�ɕϊ�����
			transComp->SetRotation(0.0f, atan2f(-pad.fThumbLY, pad.fThumbLX), 0.0f); // X�����S�̉�], Y�����S�̉�], Z�����S�̉�]�����W�A���p�Őݒ肷��
			forward = Vec3(pad.fThumbLX, 0, pad.fThumbLY).normalize();
		}
	}

	void Player::CreateMagicWall()
	{
		if (m_WallStock < 3)
		{
			auto ptrChild = dynamic_pointer_cast<MagicSkeltonWall>(m_MagicSkeltonWall);
			if (ptrChild->GetCollisionFlg() == false)
			{
				GetStage()->AddGameObject<MagicWall>(
					Vec3(ptrChild->GetScale()),
					Vec3(GetComponent<Transform>()->GetRotation()),
					Vec3(ptrChild->GetPosition()));
				m_WallStock++;
			}
		}
	}

	void Player::OnCreate()
	{
		auto ptrTrans = AddComponent<Transform>();
		ptrTrans->SetScale(Vec3(m_Scale.x, m_Scale.y, m_Scale.z));
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(Vec3(m_Position.x, m_Position.y, m_Position.z));
		
		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetDrawActive(true);

		//�d�͂�t����
		auto prtGra = AddComponent<Gravity>();

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetFogEnabled(true);
		//�`�悷��e�N�X�`����ݒ�
		ptrDraw->SetTextureResource(L"TRACE_TX");
		SetAlphaActive(true);
		//�^�O�t��
		AddTag(WstringKey::Tag_Player);

		m_MagicSkeltonWall = GetStage()->AddGameObject<MagicSkeltonWall>(m_Scale, m_Rotation, m_Position, GetThis<Player>());
	
		// DrawString�p
		auto strComp = AddComponent<StringSprite>();
		strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		strComp->SetTextRect(Rect2D<float>(1000, 10, 1270, 210));
	}

	void Player::OnUpdate()
	{
		////�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();
		WallStockDecrease();
		Die();
	}

	void Player::OnUpdate2()
	{
		DrawStrings();
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (auto magicWall = dynamic_pointer_cast<MagicWall>(other))
		{
			magicWall->SetHp(0.0f);
		}
	}

	void Player::DrawStrings()
	{
		//������\��
		
		auto rot = GetComponent<Transform>()->GetQuaternion();
		wstring playerRotation(L"PlayerRot.y: ");
		playerRotation += Util::FloatToWStr(rot.y) + L"\n";

		auto angleR = GetInputStateR();
		wstring playerRStick(L"fThumbRX: ");
		playerRStick += Util::FloatToWStr(angleR.x)
			+ L" fThumbRY: " + Util::FloatToWStr(angleR.y) + L"\n";

		wstring wallStock(L"�g����ǂ̖��� : ");
		wallStock += Util::UintToWStr(m_WallStock) + L"\n";

		wstring str = playerRotation + playerRStick + wallStock + L"\n";
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

	bool Player::GetRTriggerPushFlg()
	{
		return m_PushRTFlg;
	}

	Vec3 Player::GetRotation() const
	{
		return GetComponent<Transform>()->GetRotation();
	}
	Vec3 Player::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	// A�{�^��
	void Player::OnPushA()
	{
		WallStockDecrease();
	}

	// B�{�^��
	void Player::OnPushB()
	{

	}

	// RTrigger������
	void Player::OnHoldRTrigger()
	{
		m_PushRTFlg = true;
	}
	// RTrigger�������Ă��Ȃ���
	void Player::OnReleaseRTrigger()
	{
		if (m_PushRTFlg == true)
		{
			CreateMagicWall();
		}
		m_PushRTFlg = false;
	}

	//--------------------------------------------------
	// ���@��
	//--------------------------------------------------
	// �\�z�Ɣj��
	MagicWall::MagicWall(
		const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position)
		:
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	MagicWall::~MagicWall() {}

	void MagicWall::Delete()
	{
		if (m_Hp <= 0)
		{
			auto objs = GetStage()->GetGameObjectVec();
			for (auto& obj : objs)
			{
				auto player_share = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
				
				player_share->WallStockDecreaseFlg();
			}

			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void MagicWall::OnCreate()
	{
		auto ptrMyTrans = AddComponent<Transform>();
		ptrMyTrans->SetScale(Vec3(m_Scale));
		ptrMyTrans->SetRotation(Vec3(0.0f, m_Rotation.y, 0.0f));
		ptrMyTrans->SetPosition(Vec3(m_Position.x, m_Position.y, m_Position.z));

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetAfterCollision(AfterCollision::Auto);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		AddTag(L"TagMagicWall");

		//�`�悷��e�N�X�`����ݒ�
		ptrDraw->SetTextureResource(L"MAGICWALL_TX");
		SetAlphaActive(true);
	}

	void MagicWall::OnUpdate()
	{
		Delete();
	}

	void MagicWall::SetHp(float hp)
	{
		m_Hp = hp;
	}

	//--------------------------------------------------
	// ���@��(�Œ�O)
	//--------------------------------------------------
	// �\�z�Ɣj��
	MagicSkeltonWall::MagicSkeltonWall(
		const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const shared_ptr<GameObject>& Parent)
		:
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Parent(Parent)
	{}
	MagicSkeltonWall::~MagicSkeltonWall() {}

	void MagicSkeltonWall::SkeltonWalllSwitch()
	{
		auto pushRTriggerFlg = m_Parent->GetComponent<Player>()->GetRTriggerPushFlg();
		if (pushRTriggerFlg == true)
		{
			// �F�𔼓����ɂ��鏈��
			
		}
		else
		{
			// �����ɂ��鏈��
		}
	}

	// ������
	void MagicSkeltonWall::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetParent(m_Parent->GetThis<GameObject>());
		
		auto ptrMyTrans = AddComponent<Transform>();
		ptrMyTrans->SetScale(Vec3(5.0f, 4.0f, 0.2f));
		ptrMyTrans->SetRotation(Vec3(0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 2.0f, 3.0f));

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		//�`�悷��e�N�X�`����ݒ�
		//ptrDraw->SetSpecularColor(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		SetAlphaActive(true);
		ptrDraw->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 0.5f));
		//ptrDraw->SetEmissive(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		ptrDraw->SetTextureResource(L"MAGICWALL_TX");

		// DrawString�p
		auto strComp = AddComponent<StringSprite>();
		strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		strComp->SetTextRect(Rect2D<float>(10, 10, 270, 210));
	}

	void MagicSkeltonWall::OnUpdate2()
	{
		DrawStrings();
	}

	void MagicSkeltonWall::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (dynamic_pointer_cast<MagicWall>(other))
		{
			m_CollisionFlg = true;
		}
	}
	void MagicSkeltonWall::OnCollisionExcute(shared_ptr<GameObject>& other) {
		if (dynamic_pointer_cast<MagicWall>(other))
		{
			m_CollisionFlg = true;
		}
	}
	void MagicSkeltonWall::OnCollisionExit(shared_ptr<GameObject>& other) {
		if (dynamic_pointer_cast<MagicWall>(other))
		{
			m_CollisionFlg = false;
		}
	}

	void MagicSkeltonWall::DrawStrings()
	{
		//������\��

		auto rot = GetComponent<Transform>()->GetPosition();
		wstring playerRotation(L"SkeltonWallRot.y : ");
		playerRotation += Util::FloatToWStr(rot.z) + L"\n";

		auto collisionFlg = m_CollisionFlg;
		wstring collision(L"�ǂɏd�Ȃ��Ă��邩 : ");
		collision += Util::UintToWStr(m_CollisionFlg) + L"\n";

		wstring str = playerRotation + collision + L"\n";
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);

	}

	void MagicSkeltonWall::SetCollisionFlg(bool flg)
	{
		m_CollisionFlg = flg;
	}

	bool MagicSkeltonWall::GetCollisionFlg()
	{
		return m_CollisionFlg;
	}

	Vec3 MagicSkeltonWall::GetScale() const
	{
		return GetComponent<Transform>()->GetScale();
	}

	Vec3 MagicSkeltonWall::GetRotation() const
	{
		return GetComponent<Transform>()->GetRotation();
	}

	Vec3 MagicSkeltonWall::GetPosition() const
	{
		return GetComponent<Transform>()->GetWorldPosition();
	}
}
//end basecross

