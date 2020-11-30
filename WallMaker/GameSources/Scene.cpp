
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	
	void Scene::CreateResources() {
		// �f�[�^�f�B���N�g���̎擾
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		// �e�N�X�`��
		wstring texturesDir = dataDir + L"Textures\\";
		// �A�j���[�V����
		wstring animDir = dataDir + L"Animations\\";
		// �I�[�f�B�I
		wstring audioDir = dataDir + L"Audios\\";
		// BGM
		wstring bgmDir = audioDir + L"BGM\\";
		// SE
		wstring seDir = audioDir + L"SE\\";

		struct Pairs
		{
			wstring Key;
			wstring FileName;
		};

		// �e�N�X�`��
		Pairs txPairs[] =
		{
			{L"TRACE_TX", L"trace.png"},
			{L"FLOOR_TX", L"Floor.png"},
			{L"MAGICWALL_TX", L"MagicWall.jpg"},
			{L"WALL_TX", L"Wall.jpg"},
			{L"HEART_TX", L"Heart.png"},
			{L"WALLSTOCK_TX", L"UI_MagicWall.png"}
		};

		// �A�j���[�V����
		Pairs animPairs[] = 
		{
			{WstringKey::Anim_Player, L"PL_Stand.bmf"}
		};
		////�X�^�e�B�b�N
		//Pairs staticPairs[] =
		//{
		//	{L"MAGICWALL_MESH", L"MagicWall.bmf"}
		//};
		//�^���W�F���g�L��X�^�e�B�b�N
		Pairs staticTangentPairs[] =
		{
			{L"MAGICWALL_MESH", L"MagicWall.bmf"}
		};

		Pairs bgmPairs[] =
		{
			{L"SE_CraeteMagicWall", L"magicwall.wav"}
		};

		Pairs sePairs[] =
		{
			{L"SE_CraeteMagicWall", L"magicwall.wav"}
		};

		// �e�N�X�`��
		for (auto pair : txPairs)
		{
			wstring strTexture = texturesDir + pair.FileName;
			App::GetApp()->RegisterTexture(pair.Key, strTexture);
		}

		// �A�j���[�V����
		for (auto pair : animPairs)
		{
			auto modelMesh = MeshResource::CreateBoneModelMesh(animDir, pair.FileName);
			App::GetApp()->RegisterResource(pair.Key, modelMesh);
		}
		////�X�^�e�B�b�N
		//for (auto pair : staticPairs)
		//{
		//	auto staticModelMesh = MeshResource::CreateStaticModelMesh(animDir, pair.FileName);
		//	App::GetApp()->RegisterResource(pair.Key, staticModelMesh);
		//}
		//�^���W�F���g�L��X�^�e�B�b�N
		for (auto pair : staticTangentPairs)
		{
			auto staticModelMesh = MeshResource::CreateStaticModelMeshWithTangent(animDir, pair.FileName);
			App::GetApp()->RegisterResource(pair.Key, staticModelMesh);
		}

		//BGM
		for (auto pair : sePairs)
		{
			wstring strBGM = bgmDir + pair.FileName;
			App::GetApp()->RegisterWav(pair.Key, strBGM);
		}

		//SE
		for (auto pair : sePairs)
		{
			wstring strSE = seDir + pair.FileName;
			App::GetApp()->RegisterWav(pair.Key, strSE);
		}
	}

	void Scene::OnCreate(){
		try {
			// ���\�[�X�̍쐬
			CreateResources();

			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
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
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
	}

}
//end basecross
