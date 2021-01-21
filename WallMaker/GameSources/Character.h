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

	class TestMagicWall : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		TestMagicWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~TestMagicWall();
		// ������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	// ����
	class TestObject : public GameObject
	{
		wstring camName;

		bool m_TestFlg;
		bool m_TestFlg2;

	public:
		// �\�z�Ɣj��
		TestObject(
			const shared_ptr<Stage>& StagePtr);
		virtual ~TestObject();

		// ������
		virtual void OnCreate()override;
		virtual void OnUpdate2() override;

		void DrawStrings();
		void SetCamName(wstring name);
		wstring GetCamName();
		void SetTestFlg(bool testFlg);
		bool GetTestFlg();
		void SetTestFlg2(bool testFlg2);
		bool GetTestFlg2();
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
		void GenerateEffect(int GenerateNum, Vec3 MoveSpeed);
	};

	// �������锽�˃u���b�N
	class MoveEnableReflectBlock : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		shared_ptr<GameObject> m_Child1 = nullptr;
		shared_ptr<GameObject> m_Child2 = nullptr;
		shared_ptr<GameObject> m_Child3 = nullptr;
		shared_ptr<GameObject> m_Child4 = nullptr;

	public:
		// �\�z�Ɣj��
		MoveEnableReflectBlock(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~MoveEnableReflectBlock();

		// ������
		virtual void OnCreate()override;
	};

	// �������锽�˃u���b�N�̕�
	class MoveEnableReflectWall : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		const shared_ptr<GameObject>& m_Parent;

	public:
		// �\�z�Ɣj��
		MoveEnableReflectWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const shared_ptr<GameObject>& Parent);
		virtual ~MoveEnableReflectWall();

		// ������
		virtual void OnCreate()override;
	};

	class ActionLine : public GameObject {
		weak_ptr<GameObject> m_StartObj;
		weak_ptr<GameObject> m_EndObj;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	StartObj	�X�^�[�g�̃I�u�W�F�N�g
		@param[in]	EndObj	�G���h�̃I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		ActionLine(const shared_ptr<Stage>& StagePtr, const shared_ptr<GameObject>& StartObj,
			const shared_ptr<GameObject>& EndObj);
		virtual ~ActionLine() {}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		//���̃X�^�[�g�I�u�W�F�N�g�̎擾
		shared_ptr<GameObject> GetStartObj() const {
			return m_StartObj.lock();
		}
		//���̃X�^�[�g�I�u�W�F�N�g�̐ݒ�
		void SetStartObj(const shared_ptr<GameObject>& Obj) {
			m_StartObj = Obj;
		}
		//���̃G���h�I�u�W�F�N�g�̎擾
		shared_ptr<GameObject> GetEndObj() const {
			return m_EndObj.lock();
		}
		//���̃G���h�I�u�W�F�N�g�̐ݒ�
		void SetEndObj(const shared_ptr<GameObject>& Obj) {
			m_EndObj = Obj;
		}
		//���̃X�^�[�g�ƃG���h�I�u�W�F�N�g�̐ݒ�
		void ResetObject(const shared_ptr<GameObject>& StartObj, const shared_ptr<GameObject>& EndObj) {
			m_StartObj = StartObj;
			m_EndObj = EndObj;
		}
	};
}
//end basecross
