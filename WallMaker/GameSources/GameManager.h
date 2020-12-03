#pragma once
#include "stdafx.h"
namespace basecross {
	class GameManager {
	private:

		static GameManager* GM;
	public:
		static GameManager* GetInstance();

		bool m_ClearFlg = false;

		void ClearCheck(shared_ptr<Stage>& stage)
		{
			for (auto obj : stage->GetGameObjectVec())
			{
				if (obj->FindTag(WstringKey::Tag_Treasure))
				{
					if (auto treasure = dynamic_pointer_cast<Treasure>(obj))
					{
						if (treasure->GetTreasureFlg() == true)
						{
							m_ClearFlg = true;
						}
					}
				}
			}
		}

		bool GetClearFlg()
		{
			return m_ClearFlg;
		}

		void SetClearFlg(bool flg)
		{
			m_ClearFlg = flg;
		}
	};
}