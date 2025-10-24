#pragma once
#include <type_traits>
/// swap value of @a'left' to @a'right' and @a'right' to @a'left', alternative of 'std::swap'
namespace CRT {

	// indicate that an object may be "moved from", i.e. allowing the efficient transfer of resources to another object, alternative of 'std::move'
	template <class T>
	[[nodiscard]] constexpr std::remove_reference_t<T>&& Move(T&& argument) noexcept
	{
		return static_cast<std::remove_reference_t<T>&&>(argument);
	}
	template <typename T>
		requires (std::is_move_constructible_v<T>&& std::is_move_assignable_v<T>)
	constexpr void Swap(T& left, T& right) noexcept(std::is_nothrow_move_constructible_v<T>&& std::is_nothrow_move_assignable_v<T>)
	{
		T temporary = Move(left);
		left = Move(right);
		right = Move(temporary);
	}

}