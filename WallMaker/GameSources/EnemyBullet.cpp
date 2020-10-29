#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �ÓI�����o�ϐ�
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
			// ���ׂẴQ??�I�u�W�F�N�g�̒�����G�I�u�W�F�N�g��T���ďՓˌ��o���s��
			auto player = dynamic_pointer_cast<Player>(obj);
			auto gameStage = dynamic_pointer_cast<GameStage>(GetStage());
		}

		transComp->SetPosition(pos);
	}
}
