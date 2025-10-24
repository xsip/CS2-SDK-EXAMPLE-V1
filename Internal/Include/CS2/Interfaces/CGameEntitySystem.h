#pragma once

#include <cstddef>
#include <Memory/PatternScan.h>

#define GET_ENTITY_FN_PATTERN "4C 8D 49 10 81 FA"
namespace CS2 {
	class CGameEntitySystem {
	private:
		using GetEntityByIdDef = uintptr_t(*)(CGameEntitySystem* pGameEntitySystem, int idx);
	public:

		template <typename T>
		T* GetEntityByIndex(int idx) {
			static GetEntityByIdDef fn = nullptr;
			if (!fn) {
				fn = reinterpret_cast<GetEntityByIdDef>(PatternScan::Single("client.dll", GET_ENTITY_FN_PATTERN));
			}
			return reinterpret_cast<T*>(fn(this, idx));
		}
	};
}