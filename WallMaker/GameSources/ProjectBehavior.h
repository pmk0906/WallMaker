/*!
@file ProjectBehavior.h
@brief �v���W�F�N��`�̍s���N���X
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
	///	�R���g���[���̃{�^���̃n���h��
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr <T> & Obj) {
			//�L�[�{�[�h�̎擾�i�D��j
			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				Obj->OnPushA();
				return;
			}
			// �R���g���[���̎擾(�D��)
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (cntlVec.bConnected) {
				// A�{�^��
				if (cntlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}
				// A�{�^��
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
				//�\���L�[
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

