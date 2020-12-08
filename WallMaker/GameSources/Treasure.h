/*!
@file Character.h
@brief �L�����N??�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	// ����
	class TreasureBox : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		bool m_TreasureFlg = false;

	public:
		// �\�z�Ɣj��
		TreasureBox(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~TreasureBox();

		void DrawStrings();

		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate2()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		//�Q�[���̃N���A�t���O�̎擾
		bool GetTreasureFlg();
		void SetTreasureFlg(bool flg);
	};
}
//end basecross
