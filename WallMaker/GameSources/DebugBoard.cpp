/*!
@file DebugBoard.h
@brief �f�o�b�O�p������̕\����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void DebugBoard::OnCreate()
	{
		auto strComp = AddComponent<StringSprite>();
		strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		strComp->SetTextRect(Rect2D<float>(10, 10, 300, 400));
	}

	void DebugBoard::OnUpdate2()
	{
		auto strComp = GetComponent<StringSprite>();
		if (strComp)
		{
			strComp->SetText(stream.str());
			stream.str(L"");
		}
	}
}