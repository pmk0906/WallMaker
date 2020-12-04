/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum DPadNum
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	//--------------------------------------------------------------------------------------
	///	コントローラのボタンのハンドラ
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr <T> & Obj) {
			//キーボードの取得（優先）
			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				Obj->OnPushA();
				return;
			}
			// コントローラの取得(優先)
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (cntlVec.bConnected) {
				// Aボタン
				if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}
				// Aボタン
				if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				//RTrigger
				if (cntlVec.bRightTrigger >= 10)
				{
					Obj->OnHoldRTrigger();
				}
				else
				{
					Obj->OnReleaseRTrigger();
				}
				//十字キー
				//if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP)
				//{
				//	Obj->OnPushDPad(DPadNum::UP);
				//}
				//if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN)
				//{
				//	Obj->OnPushDPad(DPadNum::DOWN);
				//}
				//if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				//{
				//	Obj->OnPushDPad(DPadNum::LEFT);
				//}
				//if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				//{
				//	Obj->OnPushDPad(DPadNum::RIGHT);
				//}
			}
		}
	};


}

//end basecross

