/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	// 仮床
	class FixedBox : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		// 構築と破棄
		FixedBox(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~FixedBox();

		// 初期化
		virtual void OnCreate()override;
	};

	// 仮床
	class TestObject : public GameObject
	{
		wstring camName;

		bool m_TestFlg;
		bool m_TestFlg2;

	public:
		// 構築と破棄
		TestObject(
			const shared_ptr<Stage>& StagePtr);
		virtual ~TestObject();

		// 初期化
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

	// 仮床
	class Floor : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		// 構築と破棄
		Floor(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~Floor();

		// 初期化
		virtual void OnCreate()override;
	};

	// 仮床
	class StageWall : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		// 構築と破棄
		StageWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~StageWall();

		// 初期化
		virtual void OnCreate()override;
	};

	// 仮床
	class StageRefrectWall : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		// 構築と破棄
		StageRefrectWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~StageRefrectWall();

		// 初期化
		virtual void OnCreate()override;
	};

	// 壊れる壁
	class BreakWall : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float m_Hp = 1.0f;

	public:
		// 構築と破棄
		BreakWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~BreakWall();

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void Damage(float damage);
		void Die();
		void GenerateEffect(int GenerateNum, Vec3 MoveSpeed);
	};

	// 動かせる反射ブロック
	class MoveEnableReflectBlock : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		shared_ptr<GameObject> m_Child1 = nullptr;
		shared_ptr<GameObject> m_Child2 = nullptr;
		shared_ptr<GameObject> m_Child3 = nullptr;
		shared_ptr<GameObject> m_Child4 = nullptr;

	public:
		// 構築と破棄
		MoveEnableReflectBlock(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~MoveEnableReflectBlock();

		// 初期化
		virtual void OnCreate()override;
	};

	// 動かせる反射ブロックの壁
	class MoveEnableReflectWall : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		const shared_ptr<GameObject>& m_Parent;

	public:
		// 構築と破棄
		MoveEnableReflectWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const shared_ptr<GameObject>& Parent);
		virtual ~MoveEnableReflectWall();

		// 初期化
		virtual void OnCreate()override;
	};
}
//end basecross
