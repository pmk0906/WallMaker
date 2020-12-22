#pragma once
#include "stdafx.h"

namespace WstringKey {
	// タグ名
	// プレイヤー
	const wstring Tag_Player = L"TagPlayer";
	//反射壁
	const wstring Tag_MagicWall = L"TagMagicWall";
	const wstring Tag_ReflectWall = L"TagReflectWall";
	//ステージに配置するオブジェクト
	const wstring Tag_Wall = L"TagWall";
	const wstring Tag_CrackedWall = L"TagCrackedWall";
	const wstring Tag_Floor = L"TagFloor";
	const wstring Tag_DrawActiveFalse = L"TagDrawActiveFalse";
	//敵
	const wstring Tag_Enemy = L"TagEnemy";
	//宝
	const wstring Tag_Treasure = L"TagTreasure";

	//テクスチャキー
	const wstring Tx_Player = L"TXPlayer";

	//モーションキー
	//プレイヤー
	const wstring AM_PlayerStand = L"PlayerStand";
	const wstring AM_PlayerWalk = L"PlayerWalk";
	const wstring AM_PlayerStandMagic = L"PlayerStandMagic";
	const wstring AM_PlayerWalkMagic = L"PlayerWalkMagic";
	//敵
	const wstring AM_EnemyGearSpin = L"EnemyGearSpin";

	// アニメーション用
	// プレイヤー
	const wstring Anim_Player = L"AnimPlayer";
	const wstring Anim_Player_Walk = L"AnimPlayerWalk";
	const wstring Anim_Enemy = L"AnimEnemy";
	const wstring Anim_EnemyBlue = L"AnimEnemyBlue";

	//音
	//BGM
	//SE
	const wstring SE_CreateMagicWall = L"SE_CraeteMagicWall";
	const wstring SE_Bullet = L"SE_Bullet";
	const wstring SE_Reflection = L"SE_Reflection";
	const wstring SE_EnemyDamage = L"SE_EnemyDamage";
	const wstring SE_BreakWall = L"SE_BreakWall";
	const wstring SE_PlayerDamage = L"SE_PlayerDamage";
	const wstring SE_MainBGM = L"SE_MainBGM";
	const wstring SE_GameClear = L"SE_GameClear";
	const wstring SE_GameTitle = L"SE_GameTitle";
	const wstring SE_GameSelect = L"SE_GameSelect";
	const wstring SE_BreakStageWall = L"SE_BreakStageWall";

	// シェアオブジェクト用
	// プレイヤー
	const wstring ShareObj_Player = L"ObjPlayer";
	//宝箱
	const wstring ShareObj_TreasureBox = L"ObjTreasureBox";
	// フェード用スプライト
	const wstring ShareObj_FadeSprite = L"ObjFadeSprite";
	//パーティクル
	const wstring ShareObj_BreakWallEffect = L"ObjBreakWallEffect";

	//シーン名
	const wstring ToGameTitle = L"ToGameTitleScene";
	const wstring ToGameStageSelect = L"ToGameStageScene";
	const wstring ToGameStage1 = L"ToGameScene1";
	const wstring ToGameStage2 = L"ToGameScene2";
	const wstring ToGameStage3 = L"ToGameScene3";
	const wstring ToGameStage4 = L"ToGameScene4";
	const wstring ToGameStage5 = L"ToGameScene5";
	const wstring ToGameTestStage = L"ToGameTestStage";
}