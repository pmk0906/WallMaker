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
		// �������邩
		bool m_MoveEnabledFlg = false;
		float m_PlayerMoveTime = 5.0f;
		// �v���C���[�̃J����
		PlayerCamStateNum m_PlayerCameraStateNum;
		//�I�[�v�j���O�J�����̈ړ����I�������
		bool m_OpeningCameraMoveEnd = false;
		//�S�[���J�����̈ړ����I�������
		bool m_GoalCameraMoveEnd = false;
		GoalCamStateNum m_GoalCameraStateNum;
		//�J�����̃I�t�Z�b�g
		Vec3 m_MyCamOffset = Vec3(0.0f, 40.0f, -7.0f); // MyCamera
		Vec3 m_GoalCamOffset = Vec3(0.0f, 10.0f, -7.0f); // GoalCamera
		// ���݂̃J�����̖��O
		wstring m_CameraName = L"";
		wstring m_PlayerCameraState = L"";
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
		//�|�[�Y��ԂɂȂ��Ă��邩
		bool m_PoseFlg = false;
		bool m_PoseFlgChanged = false;
		//�I�����Ă���{�^���̔ԍ�
		int m_SelectingButtonNum = 0;
		//�{�^���̔ԍ��̍ő�l
		int m_MaxButtonNum = 0;
		// �t�F�[�h�C���A�E�g�p�̃t���O
		bool m_FadeFlg = false;
		bool m_FadeFlgChanged = false;

		//�X�e�[�W�̐�
		int m_StageNumMax = 5;
		//�J�����ꂽ�X�e�[�W
		bool m_StageNumArray[5] = {true, true, true, true, true};
		//���݂̃V�[���̔ԍ�
		int m_NowSceneNum = 0;
		int m_LoadSceneNum = 0;

		//�e�X�g�p�t���O
		bool m_TestFlg = false;
		//�e�X�g�p�e�L�X�g
		wstring m_TestText = L"";
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
		//�ǂݍ��ރV�[���̔ԍ�
		void SetLoadSceneNum(int loadSceneNum)
		{
			m_LoadSceneNum = loadSceneNum;
		}
		int GetLoadSceneNum()
		{
			return m_LoadSceneNum;
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
		//�v���C���[�J�����̃X�e�[�g�̔ԍ�
		PlayerCamStateNum GetPlayerCameraMoveState()
		{
			return m_PlayerCameraStateNum;
		}
		void SetPlayerCameraMoveState(PlayerCamStateNum playerCamMoveState)
		{
			m_PlayerCameraStateNum = playerCamMoveState;
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
		//�S�[���J�����̈ړ����I�������
		bool GetGoalCameraMoveEnd()
		{
			return m_GoalCameraMoveEnd;
		}
		void SetGoalCameraMoveEnd(bool goalCamMoveEnd)
		{
			m_GoalCameraMoveEnd = goalCamMoveEnd;
		}
		//�S�[���J�����̃X�e�[�g�̔ԍ�
		GoalCamStateNum GetGoalCameraMoveState()
		{
			return m_GoalCameraStateNum;
		}
		void SetGoalCameraMoveState(GoalCamStateNum goalCamMoveState)
		{
			m_GoalCameraStateNum = goalCamMoveState;
		}
		//�J�����̍��W�Ɏg���I�t�Z�b�g
		Vec3 GetMyCameraOffset()
		{
			return m_MyCamOffset;
		}
		Vec3 GetGoalCameraOffset()
		{
			return m_GoalCamOffset;
		}
		// ���݂̃J�����̖��O
		wstring GetCameraName()
		{
			return m_CameraName;
		}
		void SetCameraName(wstring camName)
		{
			m_CameraName = camName;
		}
		// ���݂̃v���C���[�J�����̃X�e�[�g
		wstring GetPlayerCameraStateName()
		{
			return m_PlayerCameraState;
		}
		void SetPlayerCameraStateName(wstring camPlayerState)
		{
			m_PlayerCameraState = camPlayerState;
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
		//�|�[�Y���
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
		// �N���A�t���O
		bool GetFadeFlg()
		{
			return m_FadeFlg;
		}
		void SetFadeFlg(bool flg)
		{
			m_FadeFlg = flg;
		}
		// �N���A�t���O���ς������
		bool GetFadeFlgChanged()
		{
			return m_FadeFlgChanged;
		}
		void SetFadeFlgChanged(bool flg)
		{
			m_FadeFlgChanged = flg;
		}

		//�e�X�g�p�t���O
		bool GetTestFlg()
		{
			return m_TestFlg;
		}
		void SetTestFlg(bool testFlg)
		{
			m_TestFlg = testFlg;
		}
		// �e�X�g�p�e�L�X�g
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