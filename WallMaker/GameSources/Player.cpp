/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	// プレイヤー
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
		
		//CollisionSphere衝突判定を付ける
		auto ptrCollision = AddComponent<CollisionSphere>();

		//重力を付ける
		auto prtGra = AddComponent<Gravity>();

		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CAPSULE");

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_CAPSULE");
		ptrDraw->SetFogEnabled(true);
		//描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"TRACE_TX");
		SetAlphaActive(true);
	}

	void Player::OnUpdate()
	{
		////コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();
	}

	void Player::OnPushA()
	{

	}
}
//end basecross

