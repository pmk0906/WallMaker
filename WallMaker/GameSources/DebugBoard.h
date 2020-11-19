/*!
@file DebugBoard.h
@brief �f�o�b�O�p������̕\����
*/

#include "stdafx.h"

namespace basecross {
	class DebugBoard : public GameObject
	{
		std::wstringstream stream; // �f�o�b�O�p�������~�ς����邽�߂�

	public :
		DebugBoard(const std::shared_ptr<Stage>& stage)
			:GameObject(stage) 
		{
		}

		void OnCreate() override;
		void OnUpdate2() override;

		void AddText(const std::wstring& str) 
		{
			stream << str;
		}

	};
}