#pragma once
#include "stdafx.h"

namespace WstringKey {
	// �^�O��
	// �v���C���[
	const wstring Tag_Player = L"TagPlayer";
	//���˕�
	const wstring Tag_MagicWall = L"TagMagicWall";
	const wstring Tag_ReflectWall = L"TagReflectWall";
	//�X�e�[�W�ɔz�u����I�u�W�F�N�g
	const wstring Tag_Wall = L"TagWall";
	const wstring Tag_CrackedWall = L"TagCrackedWall";
	const wstring Tag_Floor = L"TagFloor";
	const wstring Tag_DrawActiveFalse = L"TagDrawActiveFalse";
	//�G
	const wstring Tag_Enemy = L"TagEnemy";
	//��
	const wstring Tag_Treasure = L"TagTreasure";

	//�e�N�X�`���L�[
	const wstring Tx_Player = L"TXPlayer";

	//���[�V�����L�[
	//�v���C���[
	const wstring AM_PlayerStand = L"PlayerStand";
	const wstring AM_PlayerWalk = L"PlayerWalk";
	const wstring AM_PlayerStandMagic = L"PlayerStandMagic";
	const wstring AM_PlayerWalkMagic = L"PlayerWalkMagic";
	const wstring AM_PlayerDamage = L"PlayerDamage";
	const wstring AM_PlayerGoal = L"PlayerGoal";
	const wstring AM_PlayerDeath = L"PlayerDeath";
	//�G
	const wstring AM_EnemyGearSpin = L"EnemyGearSpin";
	//��
	const wstring AM_TreasureBoxClosing = L"TreasureBoxClosing";
	const wstring AM_TreasureBoxOpen = L"TreasureBoxOpen";


	// �A�j���[�V�����p
	// �v���C���[
	const wstring Anim_Player = L"AnimPlayer";
	const wstring Anim_Player_Walk = L"AnimPlayerWalk";
	const wstring Anim_Player_Ver2 = L"AnimPlayerAnimation";
	const wstring Anim_Enemy = L"AnimEnemy";
	const wstring Anim_EnemyBlue = L"AnimEnemyBlue";
	const wstring Anim_EnemyBlack = L"AnimEnemyBlack";
	const wstring Anim_EnemyYellow = L"AnimEnemyYellow";
	const wstring Anim_TreasureBox = L"AnimTreasureBox";

	//��
	//BGM
	const wstring BGM_MainBGM = L"BGM_MAINBGM";
	const wstring BGM_GameTitle = L"SE_GameTitle";
	const wstring BGM_GameSelect = L"SE_GameSelect";
	//SE
	const wstring SE_CreateMagicWall = L"SE_CraeteMagicWall";
	const wstring SE_Bullet = L"SE_Bullet";
	const wstring SE_Reflection = L"SE_Reflection";
	const wstring SE_EnemyDamage = L"SE_EnemyDamage";
	const wstring SE_BreakWall = L"SE_BreakWall";
	const wstring SE_PlayerDamage = L"SE_PlayerDamage";
	const wstring SE_GameClear = L"SE_GameClear";
	const wstring SE_BreakStageWall = L"SE_BreakStageWall";
	const wstring SE_Enter = L"SE_ENTER";
	const wstring SE_Cancel = L"SE_CANCEL";
	const wstring SE_Cursol = L"SE_CURSOL";
	const wstring SE_BULLET_RED = L"SE_BULLET_RED";
	const wstring SE_BULLET_ORANGE = L"SE_BULLET_ORANGE";
	const wstring SE_BULLET_YELLOW = L"SE_BULLET_YELLOW";
	const wstring SE_BULLET_GREEN = L"SE_BULLET_GREEN";
	const wstring SE_BULLET_BLUE = L"SE_BULLET_BLUE";

	// �V�F�A�I�u�W�F�N�g�p
	// �v���C���[
	const wstring ShareObj_Player = L"ObjPlayer";
	const wstring ShareObj_MagicSkeltonWall = L"ObjMagicSkeltonWall";
	// GameManagement
	const wstring ShareObj_GameManagement = L"ObjGameManagement";
	// ��
	const wstring ShareObj_TreasureBox = L"ObjTreasureBox";
	// �t�F�[�h�p�X�v���C�g
	const wstring ShareObj_FadeSprite = L"ObjFadeSprite";
	//�p�[�e�B�N��
	const wstring ShareObj_BreakWallEffect = L"ObjBreakWallEffect";
	const wstring ShareObj_ReflectBulletEffect = L"ObjReflectBulletEffect";
	const wstring ShareObj_RedFire = L"RED_BULLET_TX";
	const wstring ShareObj_OrangeFire = L"ORANGE_BULLET_TX";
	const wstring ShareObj_YellowFire = L"YELLOW_BULLET_TX";
	const wstring ShareObj_GreenFire = L"GREEN_BULLET_TX";
	const wstring ShareObj_BlueFire = L"BLUE_BULLET_TX";
	const wstring ShareObj_BlackFire = L"ENEMY_BULLET_TX";

	// �J����
	const wstring ShareObj_PlayerCameraman = L"ObjPlayerCameraman";
	const wstring ShareObj_OpeningCameraman = L"ObjOpeningCameraman";
	const wstring ShareObj_GoalCameraman = L"ObjGoalCameraman";
	//�e�X�g�p
	const wstring ShareObj_TestObject = L"ObjTestObject";

	//�V�[����
	const wstring ToGameTitle = L"ToGameTitleScene";
	const wstring ToGameStageSelect = L"ToGameStageScene";
	const wstring ToGameStage1 = L"ToGameScene1";
	const wstring ToGameStage2 = L"ToGameScene2";
	const wstring ToGameStage3 = L"ToGameScene3";
	const wstring ToGameStage4 = L"ToGameScene4";
	const wstring ToGameStage5 = L"ToGameScene5";
	const wstring ToGameTestStage = L"ToGameTestStage";
}