
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

		struct Pairs
		{
			wstring Key;
			wstring FileName;
		};

		// テクスチャ
		Pairs txPairs[] =
		{
			{L"TRACE_TX", L"trace.png"},
			{L"FLOOR_TX", L"Floor.png"}
		};

		// テクスチャ
		for (auto pair : txPairs)
		{
			wstring strTexture = texturesDir + pair.FileName;
			App::GetApp()->RegisterTexture(pair.Key, strTexture);
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
