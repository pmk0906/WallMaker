#pragma once
#include "stdafx.h"

namespace WstringKey {
	// タグ名
	// プレイヤー
	const wstring Tag_Player = L"TagPlayer";
	//反射壁
	const wstring Tag_MagicWall = L"TagMagicWall";
	const wstring Tag_ReflectWall = L"TagMagicWall";
	//ステージに配置するオブジェクト
	const wstring Tag_Wall = L"TagWall";
	const wstring Tag_CrackedWall = L"TagCracked";
	//敵
	const wstring Tag_Enemy = L"TagEnemy";

	//テクスチャキー
	const wstring Tx_Player = L"TXPlayer";

	// アニメーション用
	// プレイヤー
	const wstring Anim_Player = L"AnimPlayer";

	//音
	//BGM
	//SE
	const wstring SE_CreateMagicWall = L"SE_CraeteMagicWall";

	// シェアオブジェクト用
	// プレイヤー
	const wstring ShareObj_Player = L"ObjPlayer";
	const wstring ShareObj_MagicWall = L"ObjMagicWall";
}