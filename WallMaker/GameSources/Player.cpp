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
		m_Speed(5.0f)
	{
	}
	Player::~Player() {}


	void Player::SetCountWall()
	{
		m_ArrivedWall = 0;
		auto stage = GetStage();
		for (auto obj : stage->GetGameObjectVec())
		{
			// �ǂ��c���Ă�Ȃ�
			if (obj->FindTag(WstringKey::Tag_MagicWall))
			{
				if (auto magicWall = dynamic_pointer_cast<MagicWall>(obj))
				{
					m_ArrivedWall++;
				}
			}
		}
		m_WallStock = m_MaxWallStock - m_ArrivedWall;
		if (m_WallStock == m_MaxWallStock)
		{
			auto ptrChild = dynamic_pointer_cast<MagicSkeltonWall>(m_MagicSkeltonWall);
			ptrChild->SetCollisionFlg(false);
		}
	}

	void Player::WallAllDelete()
	{
		auto stage = GetStage();
		for (auto obj : stage->GetGameObjectVec())
		{
			// ���@�ǂ��c���Ă�Ȃ�
			if (obj->FindTag(WstringKey::Tag_MagicWall))
			{
				if (auto magicWall = dynamic_pointer_cast<MagicWall>(obj))
				{
					magicWall->SetHp(0.0f);
					m_TestFlg = false;
				}
			}
		}
	}

	void Player::DrawActiveSwitch()
	{
		auto playerPos = GetComponent<Transform>()->GetPosition();

		for (auto obj : GetStage()->GetGameObjectVec())
		{
			if (obj->FindTag(WstringKey::Tag_DrawActiveFalse))
			{
				auto otherPos = obj->GetComponent<Transform>()->GetPosition();
				auto len = playerPos - otherPos;
				if (obj->FindTag(WstringKey::Tag_Floor))
				{
					if (len.length() >= m_DrawActiveFloorLength)
					{
						obj->SetDrawActive(false);
						obj->SetUpdateActive(false);
					}
					else
					{
						obj->SetDrawActive(true);
						obj->SetUpdateActive(true);
					}
				}
				else
				{
					if (len.length() >= m_DrawActiveLength)
					{
						obj->SetDrawActive(false);
						obj->SetUpdateActive(false);
					}
					else
					{
						obj->SetDrawActive(true);
						obj->SetUpdateActive(true);
					}
				}
			}
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
		if (angle.length() > 0.0f)
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);

			auto utiPtr = GetBehavior<UtilBehavior>();
			utiPtr->RotToHead(angle, 1.0f);

			if (GetRTriggerPushFlg() == true)
			{
				if (GetMotionName() != WstringKey::AM_PlayerWalkMagic)
				{
					auto ptrDraw = GetComponent<PNTBoneModelDraw>();
					ptrDraw->ChangeCurrentAnimation(WstringKey::AM_PlayerWalkMagic);
					SetMotionName(WstringKey::AM_PlayerWalkMagic);
				}

				m_Speed = m_HoldSpeed;
			}
			else
			{
				if (GetMotionName() != WstringKey::AM_PlayerWalk) {
					auto ptrDraw = GetComponent<PNTBoneModelDraw>();
					ptrDraw->ChangeCurrentAnimation(WstringKey::AM_PlayerWalk);
					SetMotionName(WstringKey::AM_PlayerWalk);
				}

				m_Speed = m_DefaultSpeed;
			}
		}
		else
		{
			if (GetRTriggerPushFlg() == true)
			{
				if (GetMotionName() != WstringKey::AM_PlayerStandMagic)
				{
					auto ptrDraw = GetComponent<PNTBoneModelDraw>();
					ptrDraw->ChangeCurrentAnimation(WstringKey::AM_PlayerStandMagic);
					SetMotionName(WstringKey::AM_PlayerStandMagic);
				}

			}
			else 
			{
				if (GetMotionName() != WstringKey::AM_PlayerStand)
				{
					auto ptrDraw = GetComponent<PNTBoneModelDraw>();
					ptrDraw->ChangeCurrentAnimation(WstringKey::AM_PlayerStand);
					SetMotionName(WstringKey::AM_PlayerStand);
				}
			}

		}
		auto angleR = GetMoveVectorR();
		if (angleR.length() > 0.0f) {

			auto utiPtr = GetBehavior<UtilBehavior>();
			utiPtr->RotToHead(angleR, 1.0f);
		}
	}

	void Player::CreateMagicWall()
	{
		if (m_WallStock > 0)
		{
				m_TestFlg = true;
			auto ptrChild = dynamic_pointer_cast<MagicSkeltonWall>(m_MagicSkeltonWall);
			if (ptrChild->GetCollisionFlg() == false)
			{
				auto rot = GetComponent<Transform>()->GetQuaternion();
				auto magicWall = GetStage()->AddGameObject<MagicWall>(
					Vec3(ptrChild->GetScale()),
					Vec3(rot.toRotVec().y),
					Vec3(ptrChild->GetPosition()));

			// SE
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_CreateMagicWall, 0, 1.0f);
			}
		}
	}

	void Player::InvincibleBehaviour()
	{
		//�_���\�W���󂯂Ă�����
		if (m_DamageFlg == true)
		{
			if (m_InvincibleTime < m_InvincibleTimeLimit)
			{
				if (GetMotionName() != WstringKey::AM_PlayerDamage) {
					auto ptrDraw = GetComponent<PNTBoneModelDraw>();
					ptrDraw->ChangeCurrentAnimation(WstringKey::AM_PlayerDamage);
					SetMotionName(WstringKey::AM_PlayerDamage);
				}

				SetDrawActive(!GetDrawActive());

				auto elapsedTime = App::GetApp()->GetElapsedTime();
				m_InvincibleTime += elapsedTime;
			}
			else
			{
				SetDrawActive(true);
				m_DamageFlg = false;
			}
		}
	}

	void Player::MotionUpdate(wstring motionKey)
	{
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->ChangeCurrentAnimation(motionKey);
		SetMotionName(motionKey);
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);
	}

	void Player::LookCamera()
	{
		auto& app = App::GetApp();

		auto transComp = GetComponent<Transform>();
		float delta = app->GetElapsedTime();
		auto objs = GetStage()->GetGameObjectVec();
		auto myPos = transComp->GetPosition();

		Vec3 lookPos(myPos.x, myPos.y, myPos.z + 1.0f);

		auto enemyToPlayer = lookPos - myPos;

		auto forward = transComp->GetForword();

		auto dir = enemyToPlayer.normalize();

		float rot = XMConvertToRadians(90.0f) * delta; // �P�t���\��������̐���p�x

		if (m_GoalTimer < m_GoalSpinTimer)
		{
			// �O�ς�p���ăv���C���[����������ɐ��񂷂�
			if (forward.cross(dir).y < 0.0f) {
				m_RotY += rot;
			}
			else {
				m_RotY -= rot;
			}

			transComp->SetRotation(0.0f, m_RotY, 0.0f);

			m_GoalTimer += delta;
		}
	}

	void Player::OnCreate()
	{
		auto ptrTrans = AddComponent<Transform>();
		ptrTrans->SetScale(Vec3(m_Scale.x, m_Scale.y, m_Scale.z));
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(Vec3(m_Position.x, m_Position.y + (m_Scale.y / 2), m_Position.z));

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
		);
		
		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionCapsule>();
		//ptrColl->SetDrawActive(true);

		//�d�͂�t����
		auto prtGra = AddComponent<Gravity>();
		
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`(���b�V��)���w��
		ptrShadow->SetMeshToTransformMatrix(spanMat);
		ptrShadow->SetDrawActive(false);
		SetAlphaActive(true);


		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(WstringKey::Anim_Player_Ver2);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//�A�j���[�V�����̒ǉ�
		ptrDraw->AddAnimation(WstringKey::AM_PlayerStand, 0, 30, true, 10.0f);
		ptrDraw->AddAnimation(WstringKey::AM_PlayerWalk, 31, 29, true, 30.0f);
		ptrDraw->AddAnimation(WstringKey::AM_PlayerStandMagic, 61, 29, true, 10.0f);
		ptrDraw->AddAnimation(WstringKey::AM_PlayerWalkMagic, 91, 29, true, 30.0f);
		ptrDraw->AddAnimation(WstringKey::AM_PlayerDamage, 121, 29, false, 45.0f);
		ptrDraw->AddAnimation(WstringKey::AM_PlayerGoal, 151, 29, false, 10.0f);
		ptrDraw->ChangeCurrentAnimation(WstringKey::AM_PlayerStand);
		SetMotionName(WstringKey::AM_PlayerStand);
		//�ŏ��͓����ɂ��Ă���
		auto col = ptrDraw->GetDiffuse();
		col.w = 0.0f;
		ptrDraw->SetDiffuse(col);

		//�^�O�t��
		AddTag(WstringKey::Tag_Player);

		m_MagicSkeltonWall = GetStage()->AddGameObject<MagicSkeltonWall>(m_Scale, m_Rotation, m_Position, GetThis<Player>());
		GetStage()->SetSharedGameObject(WstringKey::ShareObj_MagicSkeltonWall, m_MagicSkeltonWall);

		m_RotY = 0.0f;

		// DrawString�p
		auto strComp = AddComponent<StringSprite>();
		strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		strComp->SetTextRect(Rect2D<float>(1000, 110, 1270, 310));
	}

	void Player::OnUpdate()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetMoveEnabledFlg() == true)
		{
			////�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
			m_InputHandler.PushHandle(GetThis<Player>());
			if (m_DamageFlg == false)
			{
				MovePlayer();
			}
			//WallStockDecrease();
			SetCountWall();
			Die();
			DrawActiveSwitch();

			InvincibleBehaviour();

			auto ptrDraw = GetComponent<PNTBoneModelDraw>();
			float elapsedTime = App::GetApp()->GetElapsedTime();
			ptrDraw->UpdateAnimation(elapsedTime);

			auto rotation = GetComponent<Transform>()->GetRotation();
			m_RotY = rotation.y;
		}
		else //���������Ȃ���
		{
			// �X�^�[�g���ɖ��@�w����������
			if (gm->GetMagicSircleEnabledLook() == true)
			{
				auto ptrShadow = GetComponent<Shadowmap>();
				ptrShadow->SetMeshResource(WstringKey::Anim_Player);
				ptrShadow->SetDrawActive(true);
				//������悤�ɂ���
				auto ptrDraw = GetComponent<PNTBoneModelDraw>();
				auto delta = App::GetApp()->GetElapsedTime();
				auto col = ptrDraw->GetDiffuse();
				col.w = 1.0f;
				ptrDraw->SetDiffuse(col);
			}
			// �󔠂Ƀv���C���[���G�ꂽ��
			if (gm->GetTreasureFlg() == true)
			{
				auto ptrDraw = GetComponent<PNTBoneModelDraw>();

				float elapsedTime = App::GetApp()->GetElapsedTime();

				// �S�[������GoalStandFlg��false�Ȃ�
				if (m_GoalStandFlg == false)
				{
					//���̃��[�V������AM_PlayerStand�ł͖����Ȃ�
					if (GetMotionName() != WstringKey::AM_PlayerStand)
					{
						ptrDraw = GetComponent<PNTBoneModelDraw>();
						ptrDraw->ChangeCurrentAnimation(WstringKey::AM_PlayerStand);
						SetMotionName(WstringKey::AM_PlayerStand);
					}
					m_GoalStandFlg = true;
				}

				//�󔠂̌����ڂ��J���Ă�����
				if (gm->GetTreasureBoxOpen() == true)
				{
					// �^�C�}�[����]���鎞�Ԃ𒴂��Ă��Ȃ��ꍇ
					if (m_GoalTimer < m_GoalSpinTimer)
					{
						LookCamera();
					}
				}
				else
				{
					m_RotY = GetComponent<Transform>()->GetRotation().y;
				}
				// �^�C�}�[����]���鎞�Ԃ𒴂��Ă���ꍇ
				if(m_GoalSpinTimer <= m_GoalTimer)
				{
					//���̃��[�V������AM_PlayerGoal�ł͖����Ȃ�
					if (GetMotionName() != WstringKey::AM_PlayerGoal)
					{
						auto ptrDraw = GetComponent<PNTBoneModelDraw>();
						ptrDraw->ChangeCurrentAnimation(WstringKey::AM_PlayerGoal);
						SetMotionName(WstringKey::AM_PlayerGoal);
					}

					// �^�C�}�[��3�b�𒴂��Ă��Ȃ��ꍇ
					if (m_Timer < 3.0f)
					{
						//float elapsedTime = App::GetApp()->GetElapsedTime();
						//m_Timer + elapsedTime;
					}
					//3�b�𒴂����ꍇ
					else
					{
						gm->SetGoalMotionEnd(true);
					}
					m_Timer += elapsedTime;
				}

				ptrDraw->UpdateAnimation(elapsedTime);


			}
		}
	}

	void Player::OnUpdate2()
	{
		DrawStrings();
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (auto treasureBox = dynamic_pointer_cast<TreasureBox>(other))
		{
			if (GetMotionName() != WstringKey::AM_PlayerStand)
			{
				auto ptrDraw = GetComponent<PNTBoneModelDraw>();
				ptrDraw->ChangeCurrentAnimation(WstringKey::AM_PlayerStand);
				SetMotionName(WstringKey::AM_PlayerStand);
			}
		}
	}

	void Player::DrawStrings()
	{
		auto gm = GameManager::GetInstance();

		//������\��
		auto pos = GetComponent<Transform>()->GetPosition();
		wstring playerPos(L"PlayerPos.x:");
		playerPos += Util::FloatToWStr(pos.x) + L"\nPlayerPos.y:" + 
			Util::FloatToWStr(pos.y), +L"\nPlayerPos.z:" + Util::FloatToWStr(pos.z) + L"\n";
		
		auto rot = GetComponent<Transform>()->GetQuaternion();
		// Quartanion��Radian�ɂ��� �urot.toRotVec().y�v
		wstring playerRotation(L"PlayerRot.y: ");
		playerRotation += Util::FloatToWStr(rot.toRotVec().y) + L"\n";

		auto angleR = GetInputStateR();
		wstring playerRStick(L"fThumbRX: ");
		playerRStick += Util::FloatToWStr(angleR.x)
			+ L" fThumbRY: " + Util::FloatToWStr(angleR.y) + L"\n";

		wstring wallStock(L"�g����ǂ̖��� : ");
		wallStock += Util::UintToWStr(m_WallStock) + L"\n";
		
		wstring testFlg(L"�e�X�g�p�t���O : ");
		if (m_TestFlg == true) 
		{
			testFlg += L"true\n";
		}
		else
		{
			testFlg += L"false\n";
		}
		wstring RTriggerFlg(L"R�g���K�[��������Ă��邩 : ");
		if (GetRTriggerPushFlg() == true)
		{
			RTriggerFlg += L"true\n";
		}
		else
		{
			RTriggerFlg += L"false\n";
		}

		wstring arrivingWall(L"�X�e�[�W�ɑ��݂���ǂ̖��� : ");
		arrivingWall += Util::UintToWStr(m_ArrivedWall) + L"\n";

		wstring goalMotionEnd(L"m_Timer : ");
		goalMotionEnd += Util::FloatToWStr(m_Timer) + L"\n";

		wstring damageFlg(L"DamageFlg : ");
		 
		if (m_DamageFlg == true)
		{
			damageFlg += L"true\n";
		}
		else
		{
			damageFlg += L"false\n";
		}

		wstring str = playerPos + playerRotation + playerRStick + wallStock + testFlg + arrivingWall + goalMotionEnd + damageFlg + L"\n";
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

	void Player::SetMotionName(wstring motionName)
	{
		m_MotionChanged = true;
		m_MotionName = motionName;
	}

	wstring Player::GetMotionName()
	{
		return m_MotionName;
	}

	void Player::Damage(float damage)
	{
		if (m_DamageFlg == false)
		{
			m_InvincibleTime = 0.0f;
			m_PlayerHp -= damage;
			m_DamageFlg = true;
		}
	}

	void Player::Die()
	{
		if (m_PlayerHp <= 0.0f)
		{
			SetPlayerDiedFlg(true);

			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}
	//BGM���~�߂�
	void Player::StopBGM()
	{
		//auto gameStage = dynamic_pointer_cast<GameStage>(GetStage());

		//gameStage->StopBGM();
	}

	//HP�̎擾
	float Player::GetLife()
	{
		return m_PlayerHp;
	}

	//�v���C���[�����񂾂��̃t���O
	bool Player::GetPlayerDiedFlg()
	{
		return m_PlayerDiedFlg;
	}
	void Player::SetPlayerDiedFlg(bool diedFlg)
	{
		m_PlayerDiedFlg = diedFlg;
	}

	//�ǂ̃X�g�b�N�擾
	int Player::GetWallStock()
	{
		return m_WallStock;
	}

	// A�{�^��
	void Player::OnPushA()
	{
		WallStockDecrease();
	}

	// B�{�^��
	void Player::OnPushB()
	{
		WallAllDelete();
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

	bool Player::GetRTriggerFlg()
	{
		return m_PushRTFlg;
	}
	void Player::SetRTriggerFlg(bool triggerFlg)
	{
		m_PushRTFlg = triggerFlg;
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

	MagicWall::~MagicWall() 
	{
		auto magicSkeltonWall = GetStage()->GetSharedGameObject<MagicSkeltonWall>(WstringKey::ShareObj_MagicSkeltonWall);
		if (magicSkeltonWall)
		{
			if (m_CollisionFlg == true)
			{
				magicSkeltonWall->SetCollisionFlg(false);
			}
		}

		GenerateEffect(10, Vec3(10.0f));
	}

	void MagicWall::Delete()
	{
		if (m_Hp <= 0)
		{
			//SetDrawActive(false);
			//SetUpdateActive(false);


			GetStage()->RemoveGameObject<MagicWall>(GetThis<MagicWall>());
		}
	}

	void MagicWall::GenerateEffect(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<ReflectBulletEffect>(WstringKey::ShareObj_ReflectBulletEffect, false);
		if (PtrFire) {
			PtrFire->InsertEffect(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void MagicWall::OnCreate()
	{
		auto ptrMyTrans = AddComponent<Transform>();
		ptrMyTrans->SetScale(Vec3(m_Scale));
		ptrMyTrans->SetRotation(Vec3(0.0f, m_Rotation.y, 0.0f));
		ptrMyTrans->SetPosition(Vec3(m_Position.x, m_Position.y, m_Position.z));

		AddTag(L"TagMagicWall");

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 25.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);
		//ptrColl->SetFixed(true);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`(���b�V��)���w��
		ptrShadow->SetMeshToTransformMatrix(spanMat);
		ptrShadow->SetDrawActive(false);
		SetAlphaActive(true);
		//�`�揈��
		auto ptrDraw = AddComponent<BcPNTnTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MAGICWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetLightingEnabled(false);
		//ptrDraw->SetBlendState(BlendState::Additive);

		//�`�悷��e�N�X�`����ݒ�
		SetAlphaActive(true);
		//ptrDraw->SetTextureResource(L"MAGICWALL_TX");
	}

	void MagicWall::OnUpdate()
	{
		Delete();
	}

	void MagicWall::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (dynamic_pointer_cast<MagicSkeltonWall>(other))
		{
			m_CollisionFlg = true;
		}
	}
	void MagicWall::OnCollisionExcute(shared_ptr<GameObject>& other) {
		//if (dynamic_pointer_cast<MagicWall>(other))
		//{
		//}
		//m_CollisionFlg = true;
	}
	void MagicWall::OnCollisionExit(shared_ptr<GameObject>& other) {
		if (dynamic_pointer_cast<MagicSkeltonWall>(other))
		{
			m_CollisionFlg = false;
		}
	}

	void MagicWall::SetHp(float hp)
	{
		m_Hp = hp;
	}

	void MagicWall::Damage(float damage)
	{
		m_Hp -= damage;
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

	void MagicSkeltonWall::SkeltonWallSwitch()
	{
		auto player_share = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);

		auto pushRTriggerFlg = player_share->GetRTriggerPushFlg();
		if (pushRTriggerFlg == true)
		{
			// �F�𔼓����ɂ��鏈��
			auto ptrDraw = GetComponent<BcPNTnTStaticModelDraw>();
			SetDrawActive(true);
		}
		else
		{
			// �����ɂ��鏈��
			//auto ptrDraw = GetComponent<BcPNTnTStaticModelDraw>();
			SetDrawActive(false);
		}
	}

	void MagicSkeltonWall::ChangeColor()
	{
		if (m_CollisionFlg == true)
		{
			auto ptrDraw = GetComponent<BcPNTnTStaticModelDraw>();
			ptrDraw->SetMeshResource(L"MAGICWALL_RED_MESH");
		}
		else
		{
			auto ptrDraw = GetComponent<BcPNTnTStaticModelDraw>();
			ptrDraw->SetMeshResource(L"MAGICWALL_MESH");
		}
	}

	// ������
	void MagicSkeltonWall::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetParent(m_Parent->GetThis<GameObject>());
		
		auto ptrMyTrans = AddComponent<Transform>();
		ptrMyTrans->SetScale(Vec3(5.0f, 5.0f, 0.3f));
		ptrMyTrans->SetRotation(Vec3(0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 1.25f, 3.0f));

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 25.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`(���b�V��)���w��
		ptrShadow->SetMeshToTransformMatrix(spanMat);
		ptrShadow->SetDrawActive(false);
		SetAlphaActive(true);
		//�`�揈��
		auto ptrDraw = AddComponent<BcPNTnTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MAGICWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetLightingEnabled(false);
		ptrDraw->SetModelDiffusePriority(false);
		ptrDraw->SetAlpha(0.4f);
		
		//�^�O�t��
		AddTag(WstringKey::Tag_MagicWall);

		//�`�悷��e�N�X�`����ݒ�
		SetAlphaActive(true);
		//ptrDraw->SetTextureResource(L"MAGICWALL_TX");

		// DrawString�p
		//auto strComp = AddComponent<StringSprite>();
		//strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		//strComp->SetTextRect(Rect2D<float>(10, 600, 270, 210));
	}

	void MagicSkeltonWall::OnUpdate()
	{
		SkeltonWallSwitch();
		ChangeColor();
	}

	void MagicSkeltonWall::OnUpdate2()
	{
		//DrawStrings();
	}

	void MagicSkeltonWall::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (dynamic_pointer_cast<MagicWall>(other))
		{
		}
			m_CollisionFlg = true;
	}
	void MagicSkeltonWall::OnCollisionExcute(shared_ptr<GameObject>& other) {
		//if (dynamic_pointer_cast<MagicWall>(other))
		//{
		//}
			m_CollisionFlg = true;
	}
	void MagicSkeltonWall::OnCollisionExit(shared_ptr<GameObject>& other) {
		if (dynamic_pointer_cast<MagicWall>(other))
		{
		}
			m_CollisionFlg = false;
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

