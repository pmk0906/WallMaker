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
		// �������邩
		bool m_MoveEnabledFlg = false;
		float m_PlayerMoveTime = 5.0f;
		//�J�����̈ړ�
		bool m_OpeningCameraMoveEnd = false;
		//���@�w��������悤�ɂȂ���
		bool m_MagicSircleEnabledLook = false;
		//���@�w���~��؂���
		bool m_MagicSircleMoved = false;
		// �N���A������
		bool m_ClearFlg = false;
		bool m_ClearFlgChanged = false;
		// �v���C���[�����񂾂�
		bool m_DeathFlg = false;
		bool m_DeathFlgChanged = false;
		//�I�����Ă���{�^���̔ԍ�
		int m_SelectingButtonNum = 0;
		//�{�^���̔ԍ��̍ő�l
		int m_MaxButtonNum = 0;

		//�X�e�[�W�̐�
		int m_StageNumMax = 5;
		//�J�����ꂽ�X�e�[�W
		bool m_StageNumArray[5] = {true, true, true, true, true};
		//���݂̃V�[���̔ԍ�
		int m_NowSceneNum = 0;

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
			SetMoveEnabledFlg(false); 
			SetOpeningCameraMoveEnd(false);
			SetMagicSircleMoved(false);
			SetMagicSircleEnabledLook(false);
		}

		//�V�[���̔ԍ�
		void SetSceneNum(int sceneNum)
		{
			m_NowSceneNum = sceneNum;
		}
		int GetSceneNum()
		{
			return m_NowSceneNum;
		}
		//���̃V�[���̔ԍ�
		int GetNextSceneNum()
		{
			return m_NowSceneNum + 1;
		}
		int GetStageNumMax()
		{
			return m_StageNumMax;
		}

		//��ƃv���C���[�̃t���O�����ăt���O��؂�ւ�
		void ClearCheck(shared_ptr<Stage>& stage)
		{
			for (auto obj : stage->GetGameObjectVec())
			{
				//��
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
				//�v���C���[
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
		//�v���C���[�̍s������
		bool GetMoveEnabledFlg()
		{
			return m_MoveEnabledFlg;
		}
		void SetMoveEnabledFlg(bool moveEnabledFlg)
		{
			m_MoveEnabledFlg = moveEnabledFlg;
		}
		//�I�[�v�j���O�J�����̈ړ����I�������
		bool GetOpeningCameraMoveEnd()
		{
			return m_OpeningCameraMoveEnd;
		}
		void SetOpeningCameraMoveEnd(bool opCamMoveEnd)
		{
			m_OpeningCameraMoveEnd = opCamMoveEnd;
		}
		//���@�w��������悤�ɂȂ���
		bool GetMagicSircleEnabledLook()
		{
			return m_MagicSircleEnabledLook;
		}
		void SetMagicSircleEnabledLook(bool magicSircleEnabledLook)
		{
			m_MagicSircleEnabledLook = magicSircleEnabledLook;
		}
		//���@�w���~��؂�����
		bool GetMagicSircleMoved()
		{
			return m_MagicSircleMoved;
		}
		void SetMagicSircleMoved(bool magicSircleMoved)
		{
			m_MagicSircleMoved = magicSircleMoved;
		}
		// �v���C���[�̍s���܂ł̎���
		float GetPlayerMoveTime()
		{
			return m_PlayerMoveTime;
		}
		void SetPlayerMoveTime(float moveTime)
		{
			m_PlayerMoveTime = moveTime;
		}
		// �N���A�t���O
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
		// ���S�t���O
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
		// �I�����Ă���{�^���̔ԍ�
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
		// ���݂̃{�^���̔ԍ��̍ő�l
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