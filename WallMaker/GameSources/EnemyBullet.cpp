#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// 静的メンバ変数
	//int Bullet::count = 0;

	void EnemyBullet::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
	}

	void EnemyBullet::OnUpdate()
	{
		auto &app = App::GetApp();
		auto delta = app->GetElapsedTime();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		pos += moveSpeed * dir * delta;

		auto gameStage = dynamic_pointer_cast<GameStage>(GetStage());

		auto objs = GetStage()->GetGameObjectVec();
		for (auto& obj : objs) {
			// すべてのゲ??オブジェクトの中から敵オブジェクトを探して衝突検出を行う
			auto player = dynamic_pointer_cast<Player>(obj);
			auto gameStage = dynamic_pointer_cast<GameStage>(GetStage());
		}

		transComp->SetPosition(pos);
	}
}
