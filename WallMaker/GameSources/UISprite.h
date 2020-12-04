/*!
@file Character.h
@brief �L�����N??�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	///-----------------------------------------------
	/// �ėp�X�v���C�g
	///-----------------------------------------------

	// ����
	class Sprite : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		int m_Layer;
		Col4 m_Color;

		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColorTexture> m_BackupVertices;

		//�t�F�[�h�C���E�A�E�g�p
		float m_AlphaValue = 0;

		wstring m_TextureKey;

	public:
		// �\�z�Ɣj��
		Sprite(
			const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec2& StartPos,
			const wstring TextureKey,
			const int& Layer = 0,
			const Col4& Color = Col4(1.0f, 1.0f, 1.0f, 1.0f)
		);
		virtual ~Sprite();

		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	///-----------------------------------------------
	/// �v���C���[�̃��C�t
	///-----------------------------------------------
	// ����
	class PlayerLife : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColorTexture> m_BackupVertices;

		wstring m_TextureKey;

		int m_LifeNum;

	public:
		// �\�z�Ɣj��
		PlayerLife(
			const shared_ptr<Stage>& StagePtr, 
			bool Trace,
			const Vec2& StartScale, 
			const Vec3& StartPos,
			const int LifeNum
		);
		virtual ~PlayerLife();

		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	///-----------------------------------------------
	/// �g����ǂ̐�
	///-----------------------------------------------

	// ����
	class WallStock : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColorTexture> m_BackupVertices;

		wstring m_TextureKey;

		int m_WallNum;

	public:
		// �\�z�Ɣj��
		WallStock(
			const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos,
			const int WallNum
		);
		virtual ~WallStock();

		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	///-----------------------------------------------
	///�X�v���C�g(�t�F�[�h�C��/�A�E�g�p)
	///-----------------------------------------------

	// ����
	class FadeSprite : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColorTexture> m_BackupVertices;

		//�t�F�[�h�C���E�A�E�g�p
		bool m_FadeFlg; // true:������� false:�����
		bool m_FadeFlgChanged = true;
		float m_AlphaValue = 0;

		int m_Layer;
		Col4 m_Color; // w�͍Ō�̓����x

		float m_AlphaLimit;

		wstring m_TextureKey;

	public:
		// �\�z�Ɣj��
		FadeSprite(
			const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec2& StartPos,
			bool FadeFlg,
			float AlphaLimit,
			const wstring TextureKey,
			const int& Layer = 0,
			const Col4& Color = Col4(1.0f, 1.0f, 1.0f, 1.0f)
		);
		virtual ~FadeSprite();

		//�t�F�[�h�C���E�A�E�g�؂�ւ�
		void SwitchFadeFlg();
		void SetFadeFlgChanged(bool flg);

		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	///-----------------------------------------------
	///�{�^���X�v���C�g
	///-----------------------------------------------

	// ����
	class ButtonSprite : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;

		Vec3 m_FirstScale;

		float m_Timer = 0.0f;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColorTexture> m_BackupVertices;

		//�t�F�[�h�C���E�A�E�g�p
		bool m_FadeFlg; // true:������� false:�����
		bool m_FadeFlgChanged = true;
		float m_AlphaValue = 0;

		int m_Layer;
		Col4 m_Color; // w�͍Ō�̓����x

		float m_AlphaLimit;

		wstring m_TextureKey;

		int m_SelectButtonNum = 0;
		bool m_SelectingThis = false;
		void SelectingThis();


	public:
		// �\�z�Ɣj��
		ButtonSprite(
			const shared_ptr<Stage>& StagePtr,
			bool Trace,
			const Vec2& StartScale,
			const Vec2& StartPos,
			bool FadeFlg,
			float AlphaLimit,
			const wstring TextureKey,
			const int& SelectedButtonNum,
			const int& Layer = 0,
			const Col4& Color = Col4(1.0f, 1.0f, 1.0f, 1.0f)
		);
		virtual ~ButtonSprite();

		//�t�F�[�h�C���E�A�E�g�؂�ւ�
		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross