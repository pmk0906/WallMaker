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
		Vec3 m_GoalCamOffset = Vec3(0.0f, 10.0f, -7.0f); // GoalCamera
		// 現在のカメラの名前
		wstring m_CameraName = L"";
		wstring m_PlayerCameraState = L"";
		//魔法陣が見えるようになった
		bool m_MagicSircleEnabledLook = false;
		//魔法陣が降り切った
		bool m_MagicSircleMoved = false;
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
		int m_StageNumMax = 5;
		//開放されたステージ
		bool m_StageNumArray[5] = {true, true, true, true, true};
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
				//宝
				if (obj->FindTag(WstringKey::Tag_Treasure))
				{
					if (auto treasure = dynamic_pointer_cast<TreasureBox>(obj))
					{
						if (treasure->GetTreasureFlg() == true)
						{
							m_ClearFlg = true;
							SetMoveEnabledFlg(false);
						}
					}
				}
				//プレイヤー
				if (obj->FindTag(WstringKey::Tag_Player))
				{
					if (auto player = dynamic_pointer_cast<Player>(obj))
					{
						if (player->GetPlayerDiedFlg() == true)
						{
							m_DeathFlg = true;
							SetMoveEnabledFlg(false);
						}
					}
				}
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
		void SetSelectingButtonPlus()
		{
			m_SelectingButtonNum++;
		}
		void SetSelectingButtonMinus()
		{
			m_SelectingButtonNum--;
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