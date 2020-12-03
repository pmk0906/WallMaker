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
	//敵
	const wstring Tag_Enemy = L"TagEnemy";
	//宝
	const wstring Tag_Treasure = L"TagTreasure";

	//テクスチャキー
	const wstring Tx_Player = L"TXPlayer";

	// アニメーション用
	// プレイヤー
	const wstring Anim_Player = L"AnimPlayer";
	const wstring Anim_Player_Walk = L"AnimPlayerWalk";

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

	// シェアオブジェクト用
	// プレイヤー
	const wstring ShareObj_Player = L"ObjPlayer";
	// フェード用スプライト
	const wstring ShareObj_FadeSprite = L"ObjFadeSprite";

	//シーン名
	const wstring ToGameTitle = L"ToGameTitleScene";
	const wstring ToGameStageSelect = L"ToGameStageScene";
	const wstring ToGameStage = L"ToGameScene";
}