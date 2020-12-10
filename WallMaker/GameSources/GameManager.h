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
		End
	};

	class GameManager {
	private:
		// 動かせるか
		bool m_MoveEnabledFlg = false;
		float m_PlayerMoveTime = 5.0f;
		//カメラの移動
		bool m_OpeningCameraMoveEnd = false;
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
		//選択しているボタンの番号
		int m_SelectingButtonNum = 0;
		//ボタンの番号の最大値
		int m_MaxButtonNum = 0;

		//ステージの数
		int m_StageNumMax = 5;
		//開放されたステージ
		bool m_StageNumArray[5] = {true, true, true, true, true};
		//現在のシーンの番号
		int m_NowSceneNum = 0;

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
			SetSelectingButton(0);
			SetMoveEnabledFlg(false); 
			SetOpeningCameraMoveEnd(false);
			SetMagicSircleMoved(false);
			SetMagicSircleEnabledLook(false);
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
		//オープニングカメラの移動が終わったか
		bool GetOpeningCameraMoveEnd()
		{
			return m_OpeningCameraMoveEnd;
		}
		void SetOpeningCameraMoveEnd(bool opCamMoveEnd)
		{
			m_OpeningCameraMoveEnd = opCamMoveEnd;
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

	};
}