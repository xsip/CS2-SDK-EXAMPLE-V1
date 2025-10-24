#pragma once
#include <PCH/Internal.h>
#include <Memory/PatternScan.h>
#include <CS2/Interfaces/CGameResourceService.h>
namespace CS2 {

	class CGameResourceService;
	class CGameEntitySystem;

	class CInterfaceManager {
	private:
		template <typename T>
		using CreateInterfaceFn = T * (__thiscall*)(const char* interfaceName, int unknown);

	public:

		inline static CGameResourceService* pGameResourceService = nullptr;

		template <typename T>
		inline static T* CreateInterface(std::string module, std::string interfaceName) {
			auto fn = reinterpret_cast<CInterfaceManager::CreateInterfaceFn<T>>(GetProcAddress(GetModuleHandle(module.c_str()), "CreateInterface"));
			return fn(interfaceName.c_str(), NULL);
		}

		inline static void Initialize() {
			pGameResourceService = CInterfaceManager::CreateInterface<CGameResourceService>("engine2.dll", "GameResourceServiceClientV001");
			LogAll();
		}

		inline static CGameEntitySystem* GetGameEntitySystem() {
			return pGameResourceService->pGameEntitySystem;
		}


		inline static void LogAll() {
			printf("CGameResourceService: 0x%p\n", pGameResourceService);
			printf("\tCGameEntitySystem: 0x%p\n", pGameResourceService->pGameEntitySystem);
		}
	};

	using I = CInterfaceManager;

}