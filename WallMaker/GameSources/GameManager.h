#pragma once
#include "stdafx.h"
namespace basecross {

	enum SceneNum
	{
		Title,
		StageSelect,
		GameStage_1,
		GameStage_2,
		GameStage_3,
		GameStage_4,
		GameStage_5,
		GameStage_6,
		GameStage_7,
		GameStage_8,
		GameStage_9,
		GameStage_10,
		End,
		GameStage_Test
	};

	class GameManager {
	private:
		// 動かせるか
		bool m_MoveEnabledFlg = false;
		float m_PlayerMoveTime = 5.0f;
		// プレイヤーのカメラ
		PlayerCamStateNum m_PlayerCameraStateNum;
		//オープニングカメラの移動が終わったか
		bool m_OpeningCameraMoveEnd = false;
		//ゴールカメラの移動が終わったか
		bool m_GoalCameraMoveEnd = false;
		GoalCamStateNum m_GoalCameraStateNum;
		//カメラのオフセット
		Vec3 m_MyCamOffset = Vec3(0.0f, 40.0f, -7.0f); // MyCamera
		Vec3 m_GoalCamOffset = Vec3(0.0f, 3.0f, -5.0f); // GoalCamera
		// 現在のカメラの名前
		wstring m_CameraName = L"";
		wstring m_PlayerCameraState = L"";
		//魔法陣が見えるようになった
		bool m_MagicSircleEnabledLook = false;
		//魔法陣が降り切った
		bool m_MagicSircleMoved = false;
		// カメラのズームが終わったか
		bool CameraZoomEnd = false;
		// 宝箱にプレイヤーが触れたか
		bool m_TreasureFlg = false;
		//宝箱を開けても良いか
		bool m_TreasureBoxOpenFlg = false;
		//宝箱が開き終わったか
		bool m_TreasureBoxOpened = false;
		//宝箱が開いたあとにプレイヤーのゴールモーションが終わったか
		bool m_GoalMotionEnd = false;
		// プレイヤーの死亡演出が終わったか
		bool m_DeathMotionEnd = false;
		// クリアしたか
		bool m_ClearFlg = false;
		bool m_ClearFlgChanged = false;
		// プレイヤーが死んだか
		bool m_DeathFlg = false;
		bool m_DeathFlgChanged = false;
		//ポーズ状態になっているか
		bool m_PoseFlg = false;
		bool m_PoseFlgChanged = false;
		//選択しているボタンの番号
		int m_SelectingButtonNum = 0;
		//ボタンの番号の最大値
		int m_MaxButtonNum = 0;
		// フェードインアウト用のフラグ
		bool m_FadeFlg = false;
		bool m_FadeFlgChanged = false;

		//ステージの数
		int m_StageNumMax = 6;
		//開放されたステージ
		bool m_StageNumArray[6] = {true, true, true, true, true, true};
		//現在のシーンの番号
		int m_NowSceneNum = 0;
		int m_LoadSceneNum = 0;

		//テスト用フラグ
		bool m_TestFlg = false;
		//テスト用テキスト
		wstring m_TestText = L"";
		//InputHandler<GameStage> m_InputHandler;

		static GameManager* GM;
	public:
		static GameManager* GetInstance();

		// ゲームマネージャー初期化
		void InitGameManager()
		{
			SetClearFlg(false);
			SetClearFlgChanged(false); 
			SetDeathFlg(false);
			SetDeathFlgChanged(false);
			SetPoseFlg(false);
			SetPoseFlgChanged(false);
			SetTreasureFlg(false);
			SetTreasureBoxOpen(false);
			SetTreasureBoxOpened(false); 
			SetGoalMotionEnd(false);
			SetDeathMotionEnd(false);
			SetCameraZoomEnd(false);
			SetSelectingButton(0);
			SetMoveEnabledFlg(false); 
			SetOpeningCameraMoveEnd(false);
			SetGoalCameraMoveEnd(false);
			SetMagicSircleMoved(false);
			SetMagicSircleEnabledLook(false);
			SetFadeFlgChanged(true);
			SetLoadSceneNum(0);
		}

		//シーンの番号
		void SetSceneNum(int sceneNum)
		{
			m_NowSceneNum = sceneNum;
		}
		int GetSceneNum()
		{
			return m_NowSceneNum;
		}
		//次のシーンの番号
		int GetNextSceneNum()
		{
			return m_NowSceneNum + 1;
		}
		int GetStageNumMax()
		{
			return m_StageNumMax;
		}
		//読み込むシーンの番号
		void SetLoadSceneNum(int loadSceneNum)
		{
			m_LoadSceneNum = loadSceneNum;
		}
		int GetLoadSceneNum()
		{
			return m_LoadSceneNum;
		}

		//宝とプレイヤーのフラグを見てフラグを切り替え
		void ClearCheck(shared_ptr<Stage>& stage)
		{
			for (auto obj : stage->GetGameObjectVec())
			{
				//プレイヤー
				if (obj->FindTag(WstringKey::Tag_Player))
				{
					if (auto player = dynamic_pointer_cast<Player>(obj))
					{
						if (player->GetPlayerDiedFlg() == true)
						{
							SetDeathFlg(true);
							SetMoveEnabledFlg(false);
						}
					}
				}
			}
			//宝
			if (GetTreasureFlg() == true)
			{
				SetClearFlg(true);
				SetMoveEnabledFlg(false);
			}
		}

		//プレイヤーの行動許可
		bool GetMoveEnabledFlg()
		{
			return m_MoveEnabledFlg;
		}
		void SetMoveEnabledFlg(bool moveEnabledFlg)
		{
			m_MoveEnabledFlg = moveEnabledFlg;
		}
		//プレイヤーカメラのステートの番号
		PlayerCamStateNum GetPlayerCameraMoveState()
		{
			return m_PlayerCameraStateNum;
		}
		void SetPlayerCameraMoveState(PlayerCamStateNum playerCamMoveState)
		{
			m_PlayerCameraStateNum = playerCamMoveState;
		}
		//オープニングカメラの移動が終わったか
		bool GetOpeningCameraMoveEnd()
		{
			return m_OpeningCameraMoveEnd;
		}
		void SetOpeningCameraMoveEnd(bool opCamMoveEnd)
		{
			m_OpeningCameraMoveEnd = opCamMoveEnd;
		}
		//ゴールカメラの移動が終わったか
		bool GetGoalCameraMoveEnd()
		{
			return m_GoalCameraMoveEnd;
		}
		void SetGoalCameraMoveEnd(bool goalCamMoveEnd)
		{
			m_GoalCameraMoveEnd = goalCamMoveEnd;
		}
		//ゴールカメラのステートの番号
		GoalCamStateNum GetGoalCameraMoveState()
		{
			return m_GoalCameraStateNum;
		}
		void SetGoalCameraMoveState(GoalCamStateNum goalCamMoveState)
		{
			m_GoalCameraStateNum = goalCamMoveState;
		}
		//カメラの座標に使うオフセット
		Vec3 GetMyCameraOffset()
		{
			return m_MyCamOffset;
		}
		Vec3 GetGoalCameraOffset()
		{
			return m_GoalCamOffset;
		}
		// 現在のカメラの名前
		wstring GetCameraName()
		{
			return m_CameraName;
		}
		void SetCameraName(wstring camName)
		{
			m_CameraName = camName;
		}
		// 現在のプレイヤーカメラのステート
		wstring GetPlayerCameraStateName()
		{
			return m_PlayerCameraState;
		}
		void SetPlayerCameraStateName(wstring camPlayerState)
		{
			m_PlayerCameraState = camPlayerState;
		}
		//魔法陣が見えるようになった
		bool GetMagicSircleEnabledLook()
		{
			return m_MagicSircleEnabledLook;
		}
		void SetMagicSircleEnabledLook(bool magicSircleEnabledLook)
		{
			m_MagicSircleEnabledLook = magicSircleEnabledLook;
		}
		//魔法陣が降り切ったか
		bool GetMagicSircleMoved()
		{
			return m_MagicSircleMoved;
		}
		void SetMagicSircleMoved(bool magicSircleMoved)
		{
			m_MagicSircleMoved = magicSircleMoved;
		}
		// プレイヤーの行動までの時間
		float GetPlayerMoveTime()
		{
			return m_PlayerMoveTime;
		}
		void SetPlayerMoveTime(float moveTime)
		{
			m_PlayerMoveTime = moveTime;
		}
		//宝箱にプレイヤーが触れたか
		bool GetTreasureFlg()
		{
			return m_TreasureFlg;
		}
		void SetTreasureFlg(bool treasureFlg)
		{
			m_TreasureFlg = treasureFlg;
		}
		//宝箱を開けても良いか
		bool GetTreasureBoxOpen()
		{
			return m_TreasureBoxOpenFlg;
		}
		void SetTreasureBoxOpen(bool treasureBoxOpenFlg)
		{
			m_TreasureBoxOpenFlg = treasureBoxOpenFlg;
		}
		// 宝箱が開いたか
		bool GetTreasureBoxOpened()
		{
			return m_TreasureBoxOpened;
		}
		void SetTreasureBoxOpened(bool treasureBoxOpened)
		{
			m_TreasureBoxOpened = treasureBoxOpened;
		}
		//宝箱が開いたあとにプレイヤーのゴールモーションが終わったか
		bool GetGoalMotionEnd()
		{
			return m_GoalMotionEnd;
		}
		void SetGoalMotionEnd(bool goalMotionEnd)
		{
			m_GoalMotionEnd = goalMotionEnd;
		}
		//プレイヤーの死んだモーションが終わったか
		bool GetDeathMotionEnd()
		{
			return m_DeathMotionEnd;
		}
		void SetDeathMotionEnd(bool deathMotionEnd)
		{
			m_DeathMotionEnd = deathMotionEnd;
		}
		// クリアフラグ
		bool GetClearFlg()
		{
			return m_ClearFlg;
		}
		void SetClearFlg(bool flg)
		{
			m_ClearFlg = flg;
		}
		// クリアフラグが変わったか
		bool GetClearFlgChanged()
		{
			return m_ClearFlgChanged;
		}
		void SetClearFlgChanged(bool flg)
		{
			m_ClearFlgChanged = flg;
		}
		// 死亡フラグ
		bool GetDeathFlg()
		{
			return m_DeathFlg;
		}
		void SetDeathFlg(bool flg)
		{
			m_DeathFlg = flg;
		}
		// 死亡フラグが変わったか
		bool GetDeathFlgChanged()
		{
			return m_DeathFlgChanged;
		}
		void SetDeathFlgChanged(bool flg)
		{
			m_DeathFlgChanged = flg;
		}
		//カメラのズームが終わったか
		bool GetCameraZoomEnd()
		{
			return CameraZoomEnd;
		}
		void SetCameraZoomEnd(bool cameraZoomEnd)
		{
			CameraZoomEnd = cameraZoomEnd;
		}
		//ポーズ状態
		bool GetPoseFlg()
		{
			return m_PoseFlg;
		}
		void SetPoseFlg(bool poseFlg)
		{
			m_PoseFlg = poseFlg;
		}
		bool GetPoseFlgChanged()
		{
			return m_PoseFlgChanged;
		}
		void SetPoseFlgChanged(bool poseFlgChanged)
		{
			m_PoseFlgChanged = poseFlgChanged;
		}
		// 選択しているボタンの番号
		int GetSelectingButtonNum()
		{
			return m_SelectingButtonNum;
		}
		void SetSelectingButton(int buttonNum)
		{
			m_SelectingButtonNum = buttonNum;
		}
		//プラス
		void SetSelectingButtonPlus()
		{
			m_SelectingButtonNum++;
		}
		void SetSelectingButtonPlus_5()
		{
			m_SelectingButtonNum += 5;
		}
		// マイナス
		void SetSelectingButtonMinus()
		{
			m_SelectingButtonNum--;
		}
		void SetSelectingButtonMinus_5()
		{
			m_SelectingButtonNum -= 5;
		}
		// 現在のボタンの番号の最大値
		int GetMaxButtonNum()
		{
			return m_MaxButtonNum;
		}
		void SetMaxButtonNum(int maxButtonNum)
		{
			m_MaxButtonNum = maxButtonNum;
		}
		// クリアフラグ
		bool GetFadeFlg()
		{
			return m_FadeFlg;
		}
		void SetFadeFlg(bool flg)
		{
			m_FadeFlg = flg;
		}
		// クリアフラグが変わったか
		bool GetFadeFlgChanged()
		{
			return m_FadeFlgChanged;
		}
		void SetFadeFlgChanged(bool flg)
		{
			m_FadeFlgChanged = flg;
		}

		//テスト用フラグ
		bool GetTestFlg()
		{
			return m_TestFlg;
		}
		void SetTestFlg(bool testFlg)
		{
			m_TestFlg = testFlg;
		}
		// テスト用テキスト
		wstring GetTestText()
		{
			return m_TestText;
		}
		void SetTestText(wstring testText)
		{
			m_TestText = testText;
		}
	};
}