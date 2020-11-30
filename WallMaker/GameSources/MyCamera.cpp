/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void MyCamera::OnUpdate()
	{
		//ステージの取得
		auto scene = App::GetApp()->GetScene<Scene>();
		auto stage = scene->GetActiveStage();
		//プレイヤーの取得
		auto share_player = stage->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = share_player->GetPosition();
		Vec3 offset = Vec3(0.0f, 30.0f, -10.0f);
		Vec3 myPos = playerPos + offset;
		SetEye(myPos);
		auto at = GetAt();
		at = playerPos;
		SetAt(playerPos);

		SetUp(0, 1, 0); // カメラの上方向を示す単位ベクトル
	}

}
//end basecross
