#pragma once
namespace CS2 {
	class CGameEntitySystem;
	class CGameResourceService {
		S2_PAD(0x58);
	public:
		CGameEntitySystem* pGameEntitySystem;
	};
	static_assert(offsetof(CGameResourceService, pGameEntitySystem) == 0x58);
}