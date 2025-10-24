#pragma once
namespace VTable {
	template <typename T, int index, typename ...Args>
	static constexpr T Call(void* pThis, Args... args) noexcept
	{
		return reinterpret_cast<T(*)(void*, Args...)> (reinterpret_cast<void***>(pThis)[0][index])(pThis, args...);
	}

	template <int index>
	static constexpr uintptr_t GetFunction(void* pThis) noexcept
	{
		return reinterpret_cast<uintptr_t> (reinterpret_cast<void***>(pThis)[0][index]);
	}

	static uintptr_t Get(void* pThis) noexcept
	{
		return reinterpret_cast<uintptr_t>(reinterpret_cast<void***>(pThis)[0]);
	}
}