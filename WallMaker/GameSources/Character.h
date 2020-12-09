/*!
@file Character.h
@brief �L�����N??�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	// ����
	class FixedBox : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		// �\�z�Ɣj��
		FixedBox(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~FixedBox();

		// ������
		virtual void OnCreate()override;
	};

	// ����
	class Floor : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		// �\�z�Ɣj��
		Floor(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~Floor();

		// ������
		virtual void OnCreate()override;
	};

	// ����
	class StageWall : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		// �\�z�Ɣj��
		StageWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~StageWall();

		// ������
		virtual void OnCreate()override;
	};

	// ����
	class StageRefrectWall : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		// �\�z�Ɣj��
		StageRefrectWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~StageRefrectWall();

		// ������
		virtual void OnCreate()override;
	};

	// �����
	class BreakWall : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float m_Hp = 1.0f;

	public:
		// �\�z�Ɣj��
		BreakWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~BreakWall();

		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void Damage(float damage);
		void Die();
	};
}
//end basecross
