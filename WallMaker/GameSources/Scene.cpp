
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	
	void Scene::CreateResources() {
		// データディレクトリの取得
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		// テクスチャ
		wstring texturesDir = dataDir + L"Textures\\";
		// アニメーション
		wstring animDir = dataDir + L"Animations\\";

		struct Pairs
		{
			wstring Key;
			wstring FileName;
		};

		// テクスチャ
		Pairs txPairs[] =
		{
			{L"TRACE_TX", L"trace.png"},
			{L"FLOOR_TX", L"Floor.png"},
			{L"MAGICWALL_TX", L"MagicWall.jpg"},
			{L"HEART_TX", L"Heart.png"},
			{L"WALLSTOCK_TX", L"WallUI.png"}
		};

		// アニメーション
		Pairs animPairs[] = 
		{
			{WstringKey::Anim_Player, L"PL_Stand.bmf"}
		};
		////スタティック
		//Pairs staticPairs[] =
		//{
		//	{L"MAGICWALL_MESH", L"MagicWall.bmf"}
		//};
		//タンジェント有りスタティック
		Pairs staticTangentPairs[] =
		{
			{L"MAGICWALL_MESH", L"MagicWall.bmf"}
		};

		// テクスチャ
		for (auto pair : txPairs)
		{
			wstring strTexture = texturesDir + pair.FileName;
			App::GetApp()->RegisterTexture(pair.Key, strTexture);
		}

		// アニメーション
		for (auto pair : animPairs)
		{
			auto modelMesh = MeshResource::CreateBoneModelMesh(animDir, pair.FileName);
			App::GetApp()->RegisterResource(pair.Key, modelMesh);
		}
		////スタティック
		//for (auto pair : staticPairs)
		//{
		//	auto staticModelMesh = MeshResource::CreateStaticModelMesh(animDir, pair.FileName);
		//	App::GetApp()->RegisterResource(pair.Key, staticModelMesh);
		//}
		//タンジェント有りスタティック
		for (auto pair : staticTangentPairs)
		{
			auto staticModelMesh = MeshResource::CreateStaticModelMeshWithTangent(animDir, pair.FileName);
			App::GetApp()->RegisterResource(pair.Key, staticModelMesh);
		}
	}

	void Scene::OnCreate(){
		try {
			// リソースの作成
			CreateResources();

			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
