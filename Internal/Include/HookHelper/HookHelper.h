#pragma once
#include <stdexcept>
#include <string>
#include <format>
#include <sstream>

#include <Memory/PatternScan.h>
#include <Utils/Utils.h>

#include <functional>

namespace Hook {

	class GenericBase {
	protected:
		// Static map shared across all Generic<T>
		static inline bool bMapInitialized = false;
		static inline std::unordered_map<void*, GenericBase*> s_map;
	};

	template<typename T>
	class Generic : public GenericBase {
	private:
		using FnSig = std::remove_pointer_t<T>;
		void* m_pFunctionToHook{};
		void* m_pDetour{};
		void* m_pOriginalFunction{};
		std::string m_szName{};
		bool m_bLog{};
		bool m_bIsInitialized{};
		bool m_bIsHooked{};

		std::function<std::remove_pointer_t<T>> m_fnDetour;

		std::string m_szModule;
		std::string m_szPattern;
	public:
		Generic(void* pFunctionToHook, T pDetour, std::string szName = "", bool log = false) :
			m_pFunctionToHook(pFunctionToHook),
			m_pDetour(reinterpret_cast<void*>(pDetour)),
			m_bLog(log),
			m_szName(szName) {
			::Utils::AddConsoleWindowIfNeeded();
		};
		Generic(void* pFunctionToHook, std::string szName = "", bool log = false) :
			m_pFunctionToHook(pFunctionToHook),
			m_bLog(log),
			m_szName(szName) {
			::Utils::AddConsoleWindowIfNeeded();
		};
		Generic(std::string szModule, std::string szPattern, T pDetour, std::string szName = "", bool log = false) :
			m_szModule(szModule),
			m_szPattern(szPattern),
			m_bLog(log),
			m_pDetour(reinterpret_cast<void*>(pDetour)),
			m_szName(szName) {
			::Utils::AddConsoleWindowIfNeeded();
		};

		inline void SetDetour(T pDetour) {
			m_pDetour = reinterpret_cast<void*>(pDetour);
		}

	
		inline bool Create() {
			if (!m_szPattern.empty() && !m_szModule.empty() && !m_pFunctionToHook) {
				m_pFunctionToHook = reinterpret_cast<void*>(PatternScan::Single(m_szModule.c_str(), m_szPattern.c_str()));
				if(m_bLog)
					printf("[Hook::%s] PatternScan -> 0x%p\n", m_szName.c_str(), m_pFunctionToHook);
			}

			if (m_bIsInitialized) return true;

			if (m_pFunctionToHook == nullptr || m_pDetour == nullptr)
				return false;


			auto status = MH_CreateHook(m_pFunctionToHook, m_pDetour, &m_pOriginalFunction);
			if (m_bLog)
				printf("[Hook::%s] MH_CreateHook(func=0x%p detour=0x%p) -> %d original=0x%p\n",
				m_szName.c_str(), m_pFunctionToHook, m_pDetour, status, m_pOriginalFunction);

			if (status != MH_OK)
				return false;

			m_bIsInitialized = true;
			return true;
		}

		inline bool Enable(bool bInitializeIfNot = false) {
			if (m_bIsHooked) return true;

			if (!m_bIsInitialized && bInitializeIfNot)
				if (!Create())
					return false;


			if (!m_bIsInitialized)
				return false;

			auto status = MH_EnableHook(m_pFunctionToHook);
			if (m_bLog)
				printf("[Hook::%s] MH_EnableHook(func=0x%p) -> %d\n", m_szName.c_str(), m_pFunctionToHook, status);

			if (status != MH_OK)
				return false;

			m_bIsHooked = true;
			return true;
		}


		inline bool Disable() {
			if (!m_bIsHooked || !m_bIsInitialized)
				return false;

			if (MH_DisableHook(m_pFunctionToHook) != MH_OK)
				return false;

			m_bIsHooked = false;
			return true;
		}

		inline bool Remove() {
			if (!m_bIsHooked || !m_bIsInitialized)
				return false;

			if (MH_RemoveHook(m_pFunctionToHook) != MH_OK)
				return false;


			m_bIsHooked = false;
			m_bIsInitialized = false;
			return true;
		}

		inline T GetOriginal() {
			if (m_bIsHooked) {
				return reinterpret_cast<T>(m_pOriginalFunction);
			}
			return reinterpret_cast<T>(m_pFunctionToHook);
		}
		static inline bool bMapInitialized{};
		static inline std::unordered_map<void*, Generic*> s_map;
	};
}