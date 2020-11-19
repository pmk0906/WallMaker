/*!
@file DebugBoard.h
@brief デバッグ用文字列の表示先
*/

#include "stdafx.h"

namespace basecross {
	class DebugBoard : public GameObject
	{
		std::wstringstream stream; // デバッグ用文字列を蓄積させるための

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