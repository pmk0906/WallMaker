/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------
	// プレイヤー
	//--------------------------------------------------
	// 構築と破棄
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
		m_Speed(4.0f)
	{
	}
	Player::~Player() {}


	void Player::SetCountWall()
	{
		m_ArrivedWall = 0;
		auto stage = GetStage();
		for (auto obj : stage->GetGameObjectVec())
		{
			// 壁が残ってるなら
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
			// 魔法壁が残ってるなら
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
				if (len.length() >= 25.0f)
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

	// RTriggerフラグ切り替え
	void Player::RTriggerHandler()
	{
		if (m_BeforePushRTFlg != m_PushRTFlg)
		{
			m_BeforePushRTFlg = m_PushRTFlg;
		}

	}

	// プレイヤーが使用するコントローラの入力
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
	//移動ベクトルの取得
	Vec3 Player::GetMoveVector() const
	{
		Vec3 angle(0, 0, 0);
		// 入力の取得
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0; // 動いたときのスピード
			auto ptrTrans = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//進行方向の向きを計算
			auto front = ptrTrans->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//進行方向の向きからの角度を算出
			float frontAngle = atan2(front.z, front.x);
			//コントローラの向き計算
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			float cntlAngle = atan2(-moveX, moveZ);
			// トータルの角度を算出
			float totalAngle = frontAngle + cntlAngle;
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			// 正規化する
			angle.normalize();
			//移動サイズを設定
			angle *= moveSize;
			// Y軸は変化させない
			angle.y = 0;
		}
		return angle;
	}
	Vec3 Player::GetMoveVectorR() const
	{
		Vec3 angleR(0, 0, 0);
		// 入力の取得
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
			//進行方向の向きを計算
			auto front = ptrTrans->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//進行方向の向きからの角度を算出
			float frontAngle = atan2(front.z, front.x);
			//コントローラの向き計算
			auto moveX = fThumbRX;
			auto moveZ = fThumbRY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			float cntlAngle = atan2(-moveX, moveZ);
			// トータルの角度を算出
			float totalAngle = frontAngle + cntlAngle;
			angleR = Vec3(cos(totalAngle), 0, sin(totalAngle));
			// 正規化する
			angleR.normalize();
			//移動サイズを設定
			angleR *= moveSize;
			// Y軸は変化させない
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

			if (GetMotionName() != WstringKey::AM_PlayerWalk)
			{
				auto ptrDraw = GetComponent<PNTBoneModelDraw>();
				ptrDraw->ChangeCurrentAnimation(WstringKey::AM_PlayerWalk);
				SetMotionName(WstringKey::AM_PlayerWalk);
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
		auto angleR = GetMoveVectorR();
		if (angleR.length() > 0.0f) {

			auto utiPtr = GetBehavior<UtilBehavior>();
			utiPtr->RotToHead(angleR, 1.0f);
		}
	}
	void Player::MovePlayer2() {

		// 前のフレームからの経過時間を取得する（単位：秒）
		float delta = App::GetApp()->GetElapsedTime();

		auto device = App::GetApp()->GetInputDevice(); // 入力装置を取得する
		auto pad = device.GetControlerVec()[0]; // 入力装置の中から０番目のパッドを取得する

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition(); // 今現在の座標を取得する

		float PlayerSpeed = 10.0f;

		// それぞれの座標(XYZ)に移動量を加える
		pos.x += PlayerSpeed * pad.fThumbLX * delta; // 秒間5ｍ移動
		//pos.y = 1.0f;
		pos.z += PlayerSpeed * pad.fThumbLY * delta;

		// スティックが倒れていたらその向きに回転させる
		if (pad.fThumbLX != 0.0f && pad.fThumbLY != 0.0f) {
			// atan2f関数を用いて、スティックのXYをラジアン角に変換する
			transComp->SetRotation(0.0f, atan2f(-pad.fThumbLY, pad.fThumbLX), 0.0f); // X軸中心の回転, Y軸中心の回転, Z軸中心の回転をラジアン角で設定する
			forward = Vec3(pad.fThumbLX, 0, pad.fThumbLY).normalize();
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
				//m_WallStock--;

			// SE
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_CreateMagicWall, 0, 0.5f);
			}
		}
	}

	void Player::OnCreate()
	{
		auto ptrTrans = AddComponent<Transform>();
		ptrTrans->SetScale(Vec3(m_Scale.x, m_Scale.y, m_Scale.z));
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(Vec3(m_Position.x, m_Position.y + (m_Scale.y / 2), m_Position.z));

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
		);
		
		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionCapsule>();
		//ptrColl->SetDrawActive(true);

		//重力を付ける
		auto prtGra = AddComponent<Gravity>();

		////影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形(メッシュ)を指定
		ptrShadow->SetMeshResource(WstringKey::Anim_Player);
		ptrShadow->SetMeshToTransformMatrix(spanMat);
		SetAlphaActive(true);


		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(WstringKey::Anim_Player);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//アニメーションの追加
		ptrDraw->AddAnimation(WstringKey::AM_PlayerStand, 0, 30, true, 10.0f);
		ptrDraw->AddAnimation(WstringKey::AM_PlayerWalk, 31, 60, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(WstringKey::AM_PlayerStand);
		SetMotionName(WstringKey::AM_PlayerStand);

		//タグ付け
		AddTag(WstringKey::Tag_Player);

		m_MagicSkeltonWall = GetStage()->AddGameObject<MagicSkeltonWall>(m_Scale, m_Rotation, m_Position, GetThis<Player>());
	
		// DrawString用
		//auto strComp = AddComponent<StringSprite>();
		//strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		//strComp->SetTextRect(Rect2D<float>(1000, 110, 1270, 310));
	}

	void Player::OnUpdate()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetClearFlgChanged() == false)
		{
			////コントローラチェックして入力があればコマンド呼び出し
			m_InputHandler.PushHandle(GetThis<Player>());
			MovePlayer();
			//WallStockDecrease();
			SetCountWall();
			Die();

			auto ptrDraw = GetComponent<PNTBoneModelDraw>();
			float elapsedTime = App::GetApp()->GetElapsedTime();
			ptrDraw->UpdateAnimation(elapsedTime);
		}

		DrawActiveSwitch();

	}

	void Player::OnUpdate2()
	{
		//DrawStrings();
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (auto magicWall = dynamic_pointer_cast<MagicWall>(other))
		{
			//magicWall->SetHp(0.0f);
		}
	}

	void Player::DrawStrings()
	{
		//文字列表示
		auto pos = GetComponent<Transform>()->GetPosition();
		wstring playerPos(L"PlayerPos.x:");
		playerPos += Util::FloatToWStr(pos.x) + L"\nPlayerPos.y:" + 
			Util::FloatToWStr(pos.y), +L"\nPlayerPos.z:" + Util::FloatToWStr(pos.z) + L"\n";
		
		auto rot = GetComponent<Transform>()->GetQuaternion();
		// QuartanionをRadianにする 「rot.toRotVec().y」
		wstring playerRotation(L"PlayerRot.y: ");
		playerRotation += Util::FloatToWStr(rot.toRotVec().y) + L"\n";

		auto angleR = GetInputStateR();
		wstring playerRStick(L"fThumbRX: ");
		playerRStick += Util::FloatToWStr(angleR.x)
			+ L" fThumbRY: " + Util::FloatToWStr(angleR.y) + L"\n";

		wstring wallStock(L"使える壁の枚数 : ");
		wallStock += Util::UintToWStr(m_WallStock) + L"\n";
		
		wstring testFlg(L"テスト用フラグ : ");
		if (m_TestFlg == true) 
		{
			testFlg += L"true\n";
		}
		else
		{
			testFlg += L"false\n";
		}

		wstring arrivingWall(L"ステージに存在する壁の枚数 : ");
		arrivingWall += Util::UintToWStr(m_ArrivedWall) + L"\n";

		wstring str = playerPos + playerRotation + playerRStick + wallStock + testFlg + arrivingWall + L"\n";
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

	//壁のストック減少
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
		m_PlayerHp -= damage;
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
	//BGMを止める
	void Player::StopBGM()
	{
		auto gameStage = dynamic_pointer_cast<GameStage>(GetStage());

		gameStage->StopBGM();
	}

	//HPの取得
	float Player::GetLife()
	{
		return m_PlayerHp;
	}

	//プレイヤーが死んだかのフラグ
	bool Player::GetPlayerDiedFlg()
	{
		return m_PlayerDiedFlg;
	}
	void Player::SetPlayerDiedFlg(bool diedFlg)
	{
		m_PlayerDiedFlg = diedFlg;
	}

	//壁のストック取得
	int Player::GetWallStock()
	{
		return m_WallStock;
	}

	// Aボタン
	void Player::OnPushA()
	{
		WallStockDecrease();
	}

	// Bボタン
	void Player::OnPushB()
	{
		WallAllDelete();
	}

	// RTrigger長押し
	void Player::OnHoldRTrigger()
	{
		m_PushRTFlg = true;
	}
	// RTriggerを押していない時
	void Player::OnReleaseRTrigger()
	{
		if (m_PushRTFlg == true)
		{
			CreateMagicWall();
		}
		m_PushRTFlg = false;
	}

	//--------------------------------------------------
	// 魔法壁
	//--------------------------------------------------
	// 構築と破棄
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
			//auto objs = GetStage()->GetGameObjectVec();
			//for (auto& obj : objs)
			//{
			//	auto player_share = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
			//	
			//	player_share->WallStockDecreaseFlg();
			//}

			//SetDrawActive(false);
			//SetUpdateActive(false);

			GetStage()->RemoveGameObject<MagicWall>(GetThis<MagicWall>());
		}
	}

	void MagicWall::OnCreate()
	{
		auto ptrMyTrans = AddComponent<Transform>();
		ptrMyTrans->SetScale(Vec3(m_Scale));
		ptrMyTrans->SetRotation(Vec3(0.0f, m_Rotation.y, 0.0f));
		ptrMyTrans->SetPosition(Vec3(m_Position.x, m_Position.y, m_Position.z));

		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//ptrColl->SetAfterCollision(AfterCollision::Auto);
		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		AddTag(L"TagMagicWall");

		////描画するテクスチャを設定
		//ptrDraw->SetTextureResource(L"MAGICWALL_TX");
		//SetAlphaActive(true);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.55f, 0.5f, 5.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(true);
		//ptrColl->SetFixed(true);

		//描画処理
		auto ptrDraw = AddComponent<BcPNTnTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MAGICWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetLightingEnabled(false);
		//ptrDraw->SetBlendState(BlendState::Additive);

		//描画するテクスチャを設定
		SetAlphaActive(true);
		//ptrDraw->SetTextureResource(L"MAGICWALL_TX");
	}

	void MagicWall::OnUpdate()
	{
		Delete();
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
	// 魔法壁(固定前)
	//--------------------------------------------------
	// 構築と破棄
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
			// 色を半透明にする処理
			auto ptrDraw = GetComponent<BcPNTnTStaticModelDraw>();
			SetDrawActive(true);
		}
		else
		{
			// 透明にする処理
			//auto ptrDraw = GetComponent<BcPNTnTStaticModelDraw>();
			SetDrawActive(false);
		}
	}

	void MagicSkeltonWall::ChangeColor()
	{
		if (m_CollisionFlgChanged == true)
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
			m_CollisionFlgChanged = false;
		}
	}

	// 初期化
	void MagicSkeltonWall::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetParent(m_Parent->GetThis<GameObject>());
		
		auto ptrMyTrans = AddComponent<Transform>();
		ptrMyTrans->SetScale(Vec3(5.0f, 5.0f, 0.3f));
		ptrMyTrans->SetRotation(Vec3(0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 1.25f, 3.0f));

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.55f, 0.5f, 5.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(true);

		//描画処理
		auto ptrDraw = AddComponent<BcPNTnTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MAGICWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetLightingEnabled(false);
		ptrDraw->SetModelDiffusePriority(false);
		ptrDraw->SetAlpha(0.4f);
		
		//タグ付け
		AddTag(WstringKey::Tag_MagicWall);

		//描画するテクスチャを設定
		SetAlphaActive(true);
		//ptrDraw->SetTextureResource(L"MAGICWALL_TX");

		// DrawString用
		auto strComp = AddComponent<StringSprite>();
		strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		strComp->SetTextRect(Rect2D<float>(10, 600, 270, 210));
	}

	void MagicSkeltonWall::OnUpdate()
	{
		SkeltonWallSwitch();
		ChangeColor();
	}

	void MagicSkeltonWall::OnUpdate2()
	{
		DrawStrings();
	}

	void MagicSkeltonWall::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (dynamic_pointer_cast<MagicWall>(other))
		{
			m_CollisionFlg = true;
			m_CollisionFlgChanged = true;

		}
	}
	void MagicSkeltonWall::OnCollisionExcute(shared_ptr<GameObject>& other) {
		if (dynamic_pointer_cast<MagicWall>(other))
		{
			m_CollisionFlg = true;

		}
		else
		{
			m_CollisionFlg = false;
		}
	}
	void MagicSkeltonWall::OnCollisionExit(shared_ptr<GameObject>& other) {
		if (dynamic_pointer_cast<MagicWall>(other))
		{
			m_CollisionFlg = false;
			m_CollisionFlgChanged = true;

		}
	}

	void MagicSkeltonWall::DrawStrings()
	{
		//文字列表示

		auto rot = GetComponent<Transform>()->GetPosition();
		wstring playerRotation(L"SkeltonWallRot.y : ");
		playerRotation += Util::FloatToWStr(rot.z) + L"\n";

		auto collisionFlg = m_CollisionFlg;
		wstring collision(L"壁に重なっているか : ");
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

