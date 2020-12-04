#pragma once
#include "stdafx.h"
namespace basecross {

	enum SelectingButton
	{
		ToNextStage,
		ToStageSelect,
		ToRetry,
		ToShutdown,
		ToGameStage1,
		ToGameStage2,
		ToGameStage3,
		ToGameStage4,
		ToGameStage5
	};

	class GameManager {
	private:
		// �������邩
		bool m_MoveEnabled = true;
		// �N���A������
		bool m_ClearFlg = false;
		bool m_ClearFlgChanged = false;
		// �v���C���[�����񂾂�
		bool m_DeathFlg = false;
		bool m_DeathFlgChanged = false;

		int m_SelectingButtonNum = 0;
		int m_MaxButtonNum = 0;

		//InputHandler<GameStage> m_InputHandler;

		static GameManager* GM;
	public:
		static GameManager* GetInstance();

		// �Q�[���}�l�[�W���[������
		void InitGameManager()
		{
			SetClearFlg(false);
			SetClearFlgChanged(false); 
			SetDeathFlg(false);
			SetDeathFlgChanged(false);
			SetSelectingButton(0);
		}


		void ClearCheck(shared_ptr<Stage>& stage)
		{
			for (auto obj : stage->GetGameObjectVec())
			{
				if (obj->FindTag(WstringKey::Tag_Treasure))
				{
					if (auto treasure = dynamic_pointer_cast<Treasure>(obj))
					{
						if (treasure->GetTreasureFlg() == true)
						{
							m_ClearFlg = true;
						}
					}
				}
				if (obj->FindTag(WstringKey::Tag_Player))
				{
					if (auto player = dynamic_pointer_cast<Player>(obj))
					{
						if (player->GetPlayerDiedFlg() == true)
						{
							m_DeathFlg = true;
						}
					}
				}
			}
		}

		// �N���A������
		bool GetClearFlg()
		{
			return m_ClearFlg;
		}
		void SetClearFlg(bool flg)
		{
			m_ClearFlg = flg;
		}
		// �N���A�t���O���ς������
		bool GetClearFlgChanged()
		{
			return m_ClearFlgChanged;
		}
		void SetClearFlgChanged(bool flg)
		{
			m_ClearFlgChanged = flg;
		}


		// �|���ꂽ��
		bool GetDeathFlg()
		{
			return m_DeathFlg;
		}
		void SetDeathFlg(bool flg)
		{
			m_DeathFlg = flg;
		}
		// ���S�t���O���ς������
		bool GetDeathFlgChanged()
		{
			return m_DeathFlgChanged;
		}
		void SetDeathFlgChanged(bool flg)
		{
			m_DeathFlgChanged = flg;
		}

		//�c�̃{�^���ԍ��̎擾
		int GetSelectingButtonNum()
		{
			return m_SelectingButtonNum;
		}

		void ChangeButton()
		{

		}
		//�I�����Ă���{�^��
		//int GetSelectingButton()
		//{
		//	return m_SelectingButton;
		//}
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
		// ���݂̃{�^���̔ԍ��̍ő�l
		int GetMaxButtonNum()
		{
			return m_MaxButtonNum;
		}
		void SetMaxButtonNum(int maxButtonNum)
		{
			m_MaxButtonNum = maxButtonNum;
		}

		//void OnPushDpad(int dPadNum) {
		//	switch (dPadNum)
		//	{
		//	case DPadNum::UP:
		//		if (m_SelectingButtonNum < GetMaxButtonNum())
		//		{
		//			m_SelectingButtonNum++;
		//		}
		//		break;
		//	case DPadNum::DOWN:
		//		if (m_SelectingButtonNum > 0)
		//		{
		//			m_SelectingButtonNum--;
		//		}
		//		break;
		//	case DPadNum::RIGHT:
		//		break;
		//	case DPadNum::LEFT:
		//		break;
		//	}
		//};
	};
}