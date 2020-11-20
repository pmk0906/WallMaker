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
		m_Speed(6.0f)
	{
	}
	Player::~Player() {}

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
		
		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetDrawActive(true);

		//重力を付ける
		auto prtGra = AddComponent<Gravity>();

		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetFogEnabled(true);
		//描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"TRACE_TX");
		SetAlphaActive(true);
		//タグ付け
		AddTag(WstringKey::Tag_Player);

		m_MagicSkeltonWall = GetStage()->AddGameObject<MagicSkeltonWall>(m_Scale, m_Rotation, m_Position, GetThis<Player>());
	
		// DrawString用
		auto strComp = AddComponent<StringSprite>();
		strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		strComp->SetTextRect(Rect2D<float>(1000, 10, 1270, 210));
	}

	void Player::OnUpdate()
	{
		////コントローラチェックして入力があればコマンド呼び出し
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
		//文字列表示
		
		auto rot = GetComponent<Transform>()->GetQuaternion();
		wstring playerRotation(L"PlayerRot.y: ");
		playerRotation += Util::FloatToWStr(rot.y) + L"\n";

		auto angleR = GetInputStateR();
		wstring playerRStick(L"fThumbRX: ");
		playerRStick += Util::FloatToWStr(angleR.x)
			+ L" fThumbRY: " + Util::FloatToWStr(angleR.y) + L"\n";

		wstring wallStock(L"使える壁の枚数 : ");
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

	// Aボタン
	void Player::OnPushA()
	{
		WallStockDecrease();
	}

	// Bボタン
	void Player::OnPushB()
	{

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

		//描画するテクスチャを設定
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

	void MagicSkeltonWall::SkeltonWalllSwitch()
	{
		auto pushRTriggerFlg = m_Parent->GetComponent<Player>()->GetRTriggerPushFlg();
		if (pushRTriggerFlg == true)
		{
			// 色を半透明にする処理
			
		}
		else
		{
			// 透明にする処理
		}
	}

	// 初期化
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

		//描画するテクスチャを設定
		//ptrDraw->SetSpecularColor(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		SetAlphaActive(true);
		ptrDraw->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 0.5f));
		//ptrDraw->SetEmissive(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		ptrDraw->SetTextureResource(L"MAGICWALL_TX");

		// DrawString用
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

