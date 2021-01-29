/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	MyCameraman::MyCameraman(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}
	MyCameraman::~MyCameraman() {}
	//初期化
	void MyCameraman::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(0.0f));
	}
	//操作
	void MyCameraman::OnUpdate() {
		//auto gm = GameManager::GetInstance();
		//if (gm->GetClearFlg() == true && gm->GetClearFlgChanged() == false)
		//{
		//	ChangeCamera();
		//}
	}

	void MyCameraman::ChangeCamera()
	{
		auto gm = GameManager::GetInstance();
		int stageNum = gm->GetSceneNum();

		if (stageNum == SceneNum::GameStage_1)
		{
			auto ptrGameGtage = GetTypeStage<GameStage>();
			ptrGameGtage->ToMyCamera();
		}
		else if (stageNum == SceneNum::GameStage_2)
		{
			auto ptrGameGtage = GetTypeStage<GameStage2>();
			ptrGameGtage->ToMyCamera();
		}
		else if (stageNum == SceneNum::GameStage_3)
		{
			auto ptrGameGtage = GetTypeStage<GameStage3>();
			ptrGameGtage->ToMyCamera();
		}
		else if (stageNum == SceneNum::GameStage_4)
		{
			auto ptrGameGtage = GetTypeStage<GameStage4>();
			ptrGameGtage->ToMyCamera();
		}
		else if (stageNum == SceneNum::GameStage_5)
		{
			auto ptrGameGtage = GetTypeStage<GameStage5>();
			ptrGameGtage->ToMyCamera();
		}
		else if (stageNum == SceneNum::GameStage_Test)
		{
			auto ptrGameGtage = GetTypeStage<TestStage>();
			ptrGameGtage->ToMyCamera();
		}
	}

	//--------------------------------------------------------------------------------------
	//	MyCamera()
	//--------------------------------------------------------------------------------------
	void MyCamera::OnUpdate()
	{
		//ステージの取得
		auto scene = App::GetApp()->GetScene<Scene>();
		auto stage = scene->GetActiveStage();
		//プレイヤーの取得
		auto share_player = stage->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetPosition();
		Vec3 myPos = playerPos + offset;
		SetEye(myPos);
		auto at = GetAt();
		at = playerPos;
		SetAt(playerPos);

		SetUp(0, 0, 1); // カメラの上方向を示す単位ベクトル
	}

	void MyCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	void MyCamera::ChangeCamera() {

	}

	//--------------------------------------------------------------------------------------
	//　プレイヤーカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
	PlayerCameraman::PlayerCameraman(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_StartPos(-20.0f, 5.0f, -20.0f),
		m_EndPos(18.0f, 2.0f, 10.0f),
		m_AtStartPos(0.0f, 0.0f, 0.0f),
		m_AtEndPos(18.0f, 0.0f, 18.0f),
		m_AtPos(m_AtStartPos),
		m_TotalTime(0.0f)
	{}
	PlayerCameraman::~PlayerCameraman() {}
	//初期化
	void PlayerCameraman::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_StartPos);
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<PlayerCameraman>(GetThis<PlayerCameraman>()));
		//最初のステートをOpeningCameramanToGoalStateに設定
		m_StateMachine->ChangeState(PlayerCameramanMoveToPlayerState::Instance());
	}
	//操作
	void PlayerCameraman::OnUpdate() {
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
		
		auto gm = GameManager::GetInstance();
		auto playerCameramanTrans = GetComponent<Transform>();
		auto cameramanPos = playerCameramanTrans->GetPosition();
		gm->SetTestText(L"playerCameramanPos : X_" + Util::FloatToWStr(cameramanPos.x) + L"  "
			+ L"Y_" + Util::FloatToWStr(cameramanPos.y) + L"  "
			+ L"Z_" + Util::FloatToWStr(cameramanPos.z) + L"\n");
	}

	void PlayerCameraman::ToTreasureEnterBehavior() {
		auto share_player = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetComponent<Transform>()->GetPosition();
		auto share_treasure = GetStage()->GetSharedGameObject<TreasureBox>(WstringKey::ShareObj_TreasureBox);
		auto treasurePos = share_treasure->GetComponent<Transform>()->GetPosition();
		auto startPos = (playerPos + treasurePos) * 0.5;
		m_StartPos = Vec3(startPos.x, startPos.y + offset.y, startPos.z + offset.z);
		m_EndPos = treasurePos + offset;
		m_AtStartPos = startPos + offset;
		m_AtEndPos = treasurePos;
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;

	}

	void PlayerCameraman::ToStartPointEnterBehavior() 
	{
		auto share_player = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetComponent<Transform>()->GetPosition();
		auto share_treasure = GetStage()->GetSharedGameObject<TreasureBox>(WstringKey::ShareObj_TreasureBox);
		auto treasurePos = share_treasure->GetComponent<Transform>()->GetPosition();


		m_StartPos = treasurePos + offset;
		m_EndPos = playerPos + offset;
		m_AtStartPos = treasurePos;
		m_AtEndPos = playerPos;
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void PlayerCameraman::MoveToPlayerEnterBehavior()
	{
	}

	void PlayerCameraman::MoveToPlayerExcuteBehavior()
	{
		auto gm = GameManager::GetInstance();
		auto share_player = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetComponent<Transform>()->GetPosition();
		m_StartPos = playerPos + gm->GetMyCameraOffset();
		m_EndPos = m_StartPos;
		m_AtStartPos = playerPos;
		m_AtEndPos = m_AtStartPos;
		m_AtPos = m_StartPos;
		m_TotalTime = 0.0f;
	}

	void PlayerCameraman::ZoomEnterBehavior()
	{
		auto gm = GameManager::GetInstance();
		auto share_player = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetComponent<Transform>()->GetPosition();
		auto share_treasure = GetStage()->GetSharedGameObject<TreasureBox>(WstringKey::ShareObj_TreasureBox);
		auto treasurePos = share_treasure->GetComponent<Transform>()->GetPosition();

		auto middlePos = (playerPos + treasurePos) * 0.5;
		auto startPos = playerPos + gm->GetMyCameraOffset();
		auto endPos = middlePos + gm->GetGoalCameraOffset();

		m_StartPos = playerPos + gm->GetMyCameraOffset();
		m_EndPos = playerPos + gm->GetGoalCameraOffset();
		m_AtStartPos = playerPos;
		m_AtEndPos = playerPos;
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	bool PlayerCameraman::ExcuteBehavior(float totaltime) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime;
		if (m_TotalTime > totaltime) {
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartPos, m_EndPos, m_TotalTime, totaltime);
		m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_TotalTime, totaltime);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos);

		return false;
	}

	void PlayerCameraman::ZoomDrawSwitch()
	{
		auto playerPos = GetComponent<Transform>()->GetPosition();

		for (auto obj : GetStage()->GetGameObjectVec())
		{
			if (obj->FindTag(WstringKey::Tag_DrawActiveFalse))
			{
				if (!obj->FindTag(WstringKey::Tag_Floor))
				{
					auto otherPos = obj->GetComponent<Transform>()->GetPosition();
					auto len = playerPos - otherPos;

					if (len.length() <= 8.0f)
					{
						obj->SetDrawActive(false);
					}
				}
			}
		}

	}

	void PlayerCameraman::MoveToPlayer()
	{
		auto gm = GameManager::GetInstance();
		auto share_player = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetComponent<Transform>()->GetPosition();

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(playerPos + gm->GetMyCameraOffset());


		m_StartPos = playerPos + gm->GetMyCameraOffset();
		m_EndPos = m_StartPos;
		m_AtStartPos = playerPos;
		m_AtEndPos = playerPos;
		m_AtPos = playerPos;
	}

	void PlayerCameraman::DrawActiveSwitch()
	{
		//for (auto obj : GetStage()->GetGameObjectVec())
		//{
		//	if (obj->FindTag(WstringKey::Tag_DrawActiveFalse))
		//	{
		//		auto pos = GetComponent<Transform>()->GetPosition();
		//		auto otherPos = obj->GetComponent<Transform>()->GetPosition();
		//		auto len = (pos - offset) - otherPos;
		//		if (obj->FindTag(WstringKey::Tag_Floor))
		//		{
		//			if (len.length() >= m_DrawActiveFloorLength)
		//			{
		//				obj->SetDrawActive(false);
		//				obj->SetUpdateActive(false);
		//			}
		//			else
		//			{
		//				obj->SetDrawActive(true);
		//				obj->SetUpdateActive(true);
		//			}
		//		}
		//		else
		//		{
		//			if (len.length() >= m_DrawActiveLength)
		//			{
		//				obj->SetDrawActive(false);
		//				obj->SetUpdateActive(false);
		//			}
		//			else
		//			{
		//				obj->SetDrawActive(true);
		//				obj->SetUpdateActive(true);
		//			}
		//		}
		//	}
		//}
	}

	//--------------------------------------------------------------------------------------
	//	class PlayerCameramanMoveToPlayerState : public ObjState<PlayerCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<PlayerCameramanMoveToPlayerState> PlayerCameramanMoveToPlayerState::Instance() {
		static shared_ptr<PlayerCameramanMoveToPlayerState> instance(new PlayerCameramanMoveToPlayerState);
		return instance;
	}
	void PlayerCameramanMoveToPlayerState::Enter(const shared_ptr<PlayerCameraman>& Obj) {
		auto gm = GameManager::GetInstance();
		gm->SetPlayerCameraMoveState(PlayerCamStateNum::MoveToPlayerState);
		gm->SetPlayerCameraStateName(L"MoveToPlayerState");
		Obj->MoveToPlayerEnterBehavior();
	}
	void PlayerCameramanMoveToPlayerState::Execute(const shared_ptr<PlayerCameraman>& Obj) {
		auto gm = GameManager::GetInstance();
		Obj->MoveToPlayer();

		if (gm->GetClearFlg() == true || gm->GetDeathFlg() == true)
		{
			gm->SetPlayerCameraMoveState(PlayerCamStateNum::ZoomState);
			Obj->GetStateMachine()->ChangeState(PlayerCameramanZoomState::Instance());
		}
	}
	void PlayerCameramanMoveToPlayerState::Exit(const shared_ptr<PlayerCameraman>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class PlayerCameramanZoomState : public ObjState<PlayerCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<PlayerCameramanZoomState> PlayerCameramanZoomState::Instance() {
		static shared_ptr<PlayerCameramanZoomState> instance(new PlayerCameramanZoomState);
		return instance;
	}
	void PlayerCameramanZoomState::Enter(const shared_ptr<PlayerCameraman>& Obj) {
		auto gm = GameManager::GetInstance();
		gm->SetPlayerCameraMoveState(PlayerCamStateNum::ZoomState);
		gm->SetPlayerCameraStateName(L"ZoomState");

		Obj->ZoomEnterBehavior();
	}
	void PlayerCameramanZoomState::Execute(const shared_ptr<PlayerCameraman>& Obj) {
		auto gm = GameManager::GetInstance();

		if (Obj->ExcuteBehavior(3.0f)) {
			Obj->GetStateMachine()->ChangeState(PlayerCameramanEndState::Instance());
		}

		Obj->ZoomDrawSwitch();

	}
	void PlayerCameramanZoomState::Exit(const shared_ptr<PlayerCameraman>& Obj) {
		auto gm = GameManager::GetInstance();
		if (gm->GetClearFlg()  == true)
		{
			gm->SetGoalCameraMoveEnd(true);
		}
	}
	//--------------------------------------------------------------------------------------
	//	class PlayerCameramanEndState : public ObjState<PlayerCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<PlayerCameramanEndState> PlayerCameramanEndState::Instance() {
		static shared_ptr<PlayerCameramanEndState> instance(new PlayerCameramanEndState);
		return instance;
	}
	void PlayerCameramanEndState::Enter(const shared_ptr<PlayerCameraman>& Obj) {
		auto gm = GameManager::GetInstance();
		gm->SetPlayerCameraMoveState(PlayerCamStateNum::EndState);
		gm->SetPlayerCameraStateName(L"EndState");

		if (gm->GetClearFlg() == true)
		{
			gm->SetTreasureBoxOpen(true);
		}
		else if (gm->GetDeathFlg() == true)
		{
			gm->SetCameraZoomEnd(true);
		}
	}
	void PlayerCameramanEndState::Execute(const shared_ptr<PlayerCameraman>& Obj) {

		Obj->ZoomDrawSwitch();

	}
	void PlayerCameramanEndState::Exit(const shared_ptr<PlayerCameraman>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	プレイヤーカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	PlayerCamera::PlayerCamera() :
		Camera()
	{}
	PlayerCamera::~PlayerCamera() {}

	void PlayerCamera::OnUpdate() {
		auto gm = GameManager::GetInstance();
		if (gm->GetPlayerCameraMoveState() == PlayerCamStateNum::MoveToPlayerState)
		{
			//ステージの取得
			auto scene = App::GetApp()->GetScene<Scene>();
			auto stage = scene->GetActiveStage();
			auto gm = GameManager::GetInstance();
			//プレイヤーの取得
			auto share_player = stage->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
			auto playerPos = share_player->GetPosition();
			Vec3 myPos = playerPos + gm->GetMyCameraOffset();
			SetEye(myPos);
			auto at = GetAt();
			at = playerPos;
			SetAt(playerPos);
			SetUp(0, 0, 1); // カメラの上方向を示す単位ベクトル
		}
		if (gm->GetPlayerCameraMoveState() == PlayerCamStateNum::ZoomState)
		{
			auto gm = GameManager::GetInstance();
			//ステージの取得
			auto scene = App::GetApp()->GetScene<Scene>();
			auto stage = scene->GetActiveStage();
			//プレイヤーの取得
			auto share_player = stage->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
			auto playerPos = share_player->GetPosition();
			Vec3 myPos = playerPos + gm->GetMyCameraOffset();
			auto ptrPlayerCameraman = stage->GetSharedGameObject<PlayerCameraman>(WstringKey::ShareObj_PlayerCameraman);
			if (ptrPlayerCameraman) {
				auto pos = ptrPlayerCameraman->GetPos();
				SetEye(pos);
			}
			//auto ptrPlayerCameraman = dynamic_pointer_cast<PlayerCameraman>(GetCameraObject());
			if (ptrPlayerCameraman) {
				//auto at = ptrPlayerCameraman->GetAtPos();
				//SetAt(at);
				auto eye = ptrPlayerCameraman->GetPos();
				SetEye(eye);
			}
			SetUp(0, 1, 0); // カメラの上方向を示す単位ベクトル
		}
		auto ptrPlayerCameraman = dynamic_pointer_cast<PlayerCameraman>(GetCameraObject());
		if (ptrPlayerCameraman) {
			auto at = ptrPlayerCameraman->GetAtPos();
			SetAt(at);
		}
		Camera::OnUpdate();
	}


	//--------------------------------------------------------------------------------------
	//　オープニングカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
	OpeningCameraman::OpeningCameraman(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_StartPos(-20.0f, 5.0f, -20.0f),
		m_EndPos(18.0f, 2.0f, 10.0f),
		m_AtStartPos(0.0f, 0.0f, 0.0f),
		m_AtEndPos(18.0f, 0.0f, 18.0f),
		m_AtPos(m_AtStartPos),
		m_TotalTime(0.0f)
	{}
	OpeningCameraman::~OpeningCameraman() {}
	//初期化
	void OpeningCameraman::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_StartPos);
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<OpeningCameraman>(GetThis<OpeningCameraman>()));
		//最初のステートをOpeningCameramanToGoalStateに設定
		m_StateMachine->ChangeState(OpeningCameramanStartState::Instance());
	}
	//操作
	void OpeningCameraman::OnUpdate() {
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
	}

	void OpeningCameraman::ToGoalEnterBehavior() {
		auto share_player = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetComponent<Transform>()->GetPosition();
		auto share_treasure = GetStage()->GetSharedGameObject<TreasureBox>(WstringKey::ShareObj_TreasureBox);
		auto treasurePos = share_treasure->GetComponent<Transform>()->GetPosition();
		auto startPos = (playerPos + treasurePos) * 0.5;

		m_StartPos = treasurePos + offset;
		m_EndPos = treasurePos + offset;
		m_AtStartPos = treasurePos;
		m_AtEndPos = treasurePos;
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void OpeningCameraman::ToGoalExcuteBehavior() {
		auto delta = App::GetApp()->GetElapsedTime();
		
		m_TotalTime += delta;
	}

	float OpeningCameraman::GetTotalTime() {
		return m_TotalTime;
	}

	void OpeningCameraman::ToStartEnterBehavior() {
		auto share_player = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetComponent<Transform>()->GetPosition();
		auto share_treasure = GetStage()->GetSharedGameObject<TreasureBox>(WstringKey::ShareObj_TreasureBox);
		auto treasurePos = share_treasure->GetComponent<Transform>()->GetPosition();
		m_StartPos = treasurePos + offset;
		m_EndPos = playerPos + offset;
		m_AtStartPos = treasurePos;
		m_AtEndPos = playerPos;
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	bool OpeningCameraman::ExcuteBehavior(float totaltime) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime;
		if (m_TotalTime > totaltime) {
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartPos, m_EndPos, m_TotalTime, totaltime);
		m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_TotalTime, totaltime);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos);
		return false;
	}

	void OpeningCameraman::EndStateEnterBehavior() {
		auto gameManagement = GetStage()->GetSharedGameObject<GameManagement>(WstringKey::ShareObj_GameManagement);
		gameManagement->ChangeCamera();

		auto gm = GameManager::GetInstance();
		gm->SetOpeningCameraMoveEnd(true);
	}

	void OpeningCameraman::DrawActiveSwitch()
	{
		for (auto obj : GetStage()->GetGameObjectVec())
		{
			if (obj->FindTag(WstringKey::Tag_DrawActiveFalse))
			{
				auto pos = GetComponent<Transform>()->GetPosition();
				auto otherPos = obj->GetComponent<Transform>()->GetPosition();
				auto len = (pos - offset) - otherPos;
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


	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanStartState> OpeningCameramanStartState::Instance() {
		static shared_ptr<OpeningCameramanStartState> instance(new OpeningCameramanStartState);
		return instance;
	}
	void OpeningCameramanStartState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->ToGoalEnterBehavior();
	}
	void OpeningCameramanStartState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		//Obj->ToGoalExcuteBehavior();
		if (Obj->ExcuteBehavior(1.0f)) {
			Obj->GetStateMachine()->ChangeState(OpeningCameramanMoveState::Instance());
		}
	}
	void OpeningCameramanStartState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanMoveState> OpeningCameramanMoveState::Instance() {
		static shared_ptr<OpeningCameramanMoveState> instance(new OpeningCameramanMoveState);
		return instance;
	}
	void OpeningCameramanMoveState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->ToStartEnterBehavior();
	}
	void OpeningCameramanMoveState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		auto gm = GameManager::GetInstance();
		if (gm->GetMoveEnabledFlg() == false)
		{
			if (gm->GetPoseFlg() == false)
			{
				if (gm->GetOpeningCameraMoveEnd() == false) {
					if (Obj->ExcuteBehavior(7.0f)) {
						Obj->GetStateMachine()->ChangeState(OpeningCameramanEndState::Instance());
					}
				}
			}
		}
	}
	void OpeningCameramanMoveState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanEndState> OpeningCameramanEndState::Instance() {
		static shared_ptr<OpeningCameramanEndState> instance(new OpeningCameramanEndState);
		return instance;
	}
	void OpeningCameramanEndState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->EndStateEnterBehavior();
	}
	void OpeningCameramanEndState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
	}
	void OpeningCameramanEndState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	オープニングカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	OpeningCamera::OpeningCamera() :
		Camera()
	{}
	OpeningCamera::~OpeningCamera() {}

	void OpeningCamera::OnUpdate() {
		auto ptrOpeningCameraman = dynamic_pointer_cast<OpeningCameraman>(GetCameraObject());
		if (ptrOpeningCameraman) {
			auto pos = ptrOpeningCameraman->GetAtPos();
			SetAt(pos);
		}
		Camera::OnUpdate();
	}

	//--------------------------------------------------------------------------------------
	//　ゴールカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
	GoalCameraman::GoalCameraman(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_StartPos(-20.0f, 40.0f, -20.0f),
		m_EndPos(-20.0f, 40.0f, -20.0f),
		m_AtStartPos(0.0f, 0.0f, 0.0f),
		m_AtEndPos(18.0f, 0.0f, 18.0f),
		m_AtPos(m_AtStartPos),
		m_TotalTime(0.0f)
	{}
	GoalCameraman::~GoalCameraman() {}
	//初期化
	void GoalCameraman::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_StartPos);
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<GoalCameraman>(GetThis<GoalCameraman>()));
		//最初のステートをOpeningCameramanToGoalStateに設定
		m_StateMachine->ChangeState(GoalCameramanMovingState::Instance());

		// DrawString用
		auto strComp = AddComponent<StringSprite>();
		strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		strComp->SetTextRect(Rect2D<float>(1000, 510, 1270, 710));
	}
	//操作
	void GoalCameraman::OnUpdate() {
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
	}

	void GoalCameraman::OnUpdate2()
	{
		DrawStrings();
	}

	void GoalCameraman::DrawStrings()
	{
		wstring nowState = L"現在のステート：";
		switch (GetStateNum())
		{
		case 0:
			nowState += L"GoalCameramanMoveStartState";
			break;
		case 1:
			nowState += L"GoalCameramanMovingState";
			break;
		case 2:
			nowState += L"GoalCameramanMoveEndState";
			break;
		}

		wstring str = nowState + L"\n";
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);

	}

	//開始位置：ゴールとプレイヤーの中間の座標＋プレイヤーのカメラのオフセット
	//終了位置；ゴールとプレイヤーの中間の座標＋カメラの位置(これから設定)
	//向いている座標：ゴールとプレイヤーの中間の座標
	void GoalCameraman::MoveStartEnterBehavior() {
		auto share_player = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetPosition();
		auto share_treasure = GetStage()->GetSharedGameObject<TreasureBox>(WstringKey::ShareObj_TreasureBox);
		auto treasurePos = share_treasure->GetComponent<Transform>()->GetPosition();
		Vec3 endPos = (playerPos + treasurePos) * 0.5f;
		m_StartPos = playerPos + m_MyCamOffset;
		m_EndPos = m_StartPos;
		m_AtStartPos = playerPos;
		m_AtEndPos = m_AtEndPos;
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void GoalCameraman::MoveStartExcuteBehaviour()
	{
		auto gm = GameManager::GetInstance();
		auto share_player = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetPosition();
		auto myCamPos = gm->GetMyCameraOffset();
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(playerPos + myCamPos);

	}

	void GoalCameraman::MovingEnterBehavior() {
		auto gm = GameManager::GetInstance();
		auto share_player = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetComponent<Transform>()->GetPosition();
		auto share_treasure = GetStage()->GetSharedGameObject<TreasureBox>(WstringKey::ShareObj_TreasureBox);
		auto treasurePos = share_treasure->GetComponent<Transform>()->GetPosition();

		auto middlePos = playerPos; //(playerPos + treasurePos) * 0.5;
		auto startPos = playerPos + gm->GetMyCameraOffset();
		auto endPos = middlePos + gm->GetGoalCameraOffset();
		
		m_StartPos = startPos;
		m_EndPos = endPos;
		m_AtStartPos = playerPos;
		m_AtEndPos = middlePos;
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void GoalCameraman::MovingExcuteBehavior()
	{
		auto gm = GameManager::GetInstance();
		auto share_player = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetComponent<Transform>()->GetPosition();
		auto share_treasure = GetStage()->GetSharedGameObject<TreasureBox>(WstringKey::ShareObj_TreasureBox);
		auto treasurePos = share_treasure->GetComponent<Transform>()->GetPosition();

		auto middlePos = playerPos; //(playerPos + treasurePos) * 0.5;
		auto startPos = playerPos + gm->GetMyCameraOffset();
		auto endPos = middlePos + gm->GetGoalCameraOffset();

		m_StartPos = startPos;
		m_EndPos = endPos;
		m_AtStartPos = playerPos;
		m_AtEndPos = middlePos;
		m_AtPos = m_AtStartPos;
	}

	bool GoalCameraman::ExcuteBehavior(float totaltime) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime;
		if (m_TotalTime > totaltime) {
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartPos, m_EndPos, m_TotalTime, totaltime);
		m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_TotalTime, totaltime);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos);
		return false;
	}
	
	void GoalCameraman::MoveEndEnterBehavior()
	{

	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<GoalCameramanMoveStartState> GoalCameramanMoveStartState::Instance() {
		static shared_ptr<GoalCameramanMoveStartState> instance(new GoalCameramanMoveStartState);
		return instance;
	}
	void GoalCameramanMoveStartState::Enter(const shared_ptr<GoalCameraman>& Obj) {
		Obj->MoveStartEnterBehavior();
		auto gm = GameManager::GetInstance();
		gm->SetGoalCameraMoveState(GoalCamStateNum::MoveStartState);
	}
	void GoalCameramanMoveStartState::Execute(const shared_ptr<GoalCameraman>& Obj) {
		//Obj->MoveStartExcuteBehaviour();

		auto gm = GameManager::GetInstance();
		if (gm->GetClearFlg() == true && gm->GetClearFlgChanged() == false)
		{
			Obj->GetStateMachine()->ChangeState(GoalCameramanMovingState::Instance());
			auto gm = GameManager::GetInstance();
			gm->SetGoalCameraMoveState(GoalCamStateNum::MovingState);
		}
		Obj->SetStateNum(0);
	}
	void GoalCameramanMoveStartState::Exit(const shared_ptr<GoalCameraman>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<GoalCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<GoalCameramanMovingState> GoalCameramanMovingState::Instance() {
		static shared_ptr<GoalCameramanMovingState> instance(new GoalCameramanMovingState);
		return instance;
	}
	void GoalCameramanMovingState::Enter(const shared_ptr<GoalCameraman>& Obj) {
		Obj->MovingEnterBehavior();
		auto gm = GameManager::GetInstance();
		gm->SetGoalCameraMoveState(GoalCamStateNum::MovingState);
	}
	void GoalCameramanMovingState::Execute(const shared_ptr<GoalCameraman>& Obj) {
		
		Obj->MovingExcuteBehavior();

		auto gm = GameManager::GetInstance();
		if (gm->GetClearFlg() == true && gm->GetClearFlgChanged() == false)
		{
			if (Obj->ExcuteBehavior(3.0f)) {
				Obj->GetStateMachine()->ChangeState(GoalCameramanMoveEndState::Instance());
				auto gm = GameManager::GetInstance();
				gm->SetGoalCameraMoveState(GoalCamStateNum::MoveEndState);
			}
		}

		//if (Obj->ExcuteBehavior(3.0f)) {
		//	Obj->GetStateMachine()->ChangeState(GoalCameramanMoveEndState::Instance());
		//	auto gm = GameManager::GetInstance();
		//	gm->SetGoalCameraMoveState(GoalCamStateNum::MoveEndState);
		//}
		Obj->SetStateNum(1);
	}
	void GoalCameramanMovingState::Exit(const shared_ptr<GoalCameraman>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<GoalCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<GoalCameramanMoveEndState> GoalCameramanMoveEndState::Instance() {
		static shared_ptr<GoalCameramanMoveEndState> instance(new GoalCameramanMoveEndState);
		return instance;
	}
	void GoalCameramanMoveEndState::Enter(const shared_ptr<GoalCameraman>& Obj) {
		auto gm = GameManager::GetInstance();
		gm->SetGoalCameraMoveEnd(true);
		gm->SetGoalCameraMoveState(GoalCamStateNum::MoveEndState);
	}
	void GoalCameramanMoveEndState::Execute(const shared_ptr<GoalCameraman>& Obj) {
		Obj->SetStateNum(2);
	}
	void GoalCameramanMoveEndState::Exit(const shared_ptr<GoalCameraman>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	ゴールカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	GoalCamera::GoalCamera() :
		Camera()
	{}
	GoalCamera::~GoalCamera() {}

	void GoalCamera::OnUpdate() {
		auto ptrGoalCameraman = dynamic_pointer_cast<GoalCameraman>(GetCameraObject());
		if (ptrGoalCameraman) {
			auto atPos = ptrGoalCameraman->GetAtPos();
			SetAt(atPos);
		}
		Camera::OnUpdate();

		//ここは無くても動く
		//auto gm = GameManager::GetInstance();
		//if (gm->GetClearFlg() != true && gm->GetClearFlgChanged() != false)
		//{
		//	auto gm = GameManager::GetInstance();
		//	//ステージの取得
		//	auto scene = App::GetApp()->GetScene<Scene>();
		//	auto stage = scene->GetActiveStage();
		//	//プレイヤーの取得
		//	auto share_player = stage->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		//	auto playerPos = share_player->GetPosition();
		//	Vec3 myPos = playerPos + gm->GetMyCameraOffset();
		//	SetEye(myPos);
		//	auto at = GetAt();
		//	at = playerPos;
		//	SetAt(playerPos);
		//}
		SetUp(0, 1, 0); // カメラの上方向を示す単位ベクトル
	}
}
//end basecross
