#pragma once 


namespace PatternScan {
	uint8_t* Single(const char* module_name, const char* signature) noexcept;
	std::vector<uint8_t*> Multi(const char* module_name, const char* signature) noexcept;
	uintptr_t InstructionValue(uintptr_t pOffset, uintptr_t pInstructionSize, uintptr_t pOffsetLength) noexcept;
	std::uint8_t* ResolveRelativeAddress(std::uint8_t* nAddressBytes, std::uint32_t nRVAOffset, std::uint32_t nRIPOffset);

	template <typename T = std::uint8_t>
	inline T* GetAbsoluteAddress(T* pRelativeAddress, int nPreOffset = 0x0, int nPostOffset = 0x0)
	{
		pRelativeAddress += nPreOffset;
		pRelativeAddress += sizeof(std::int32_t) + *reinterpret_cast<std::int32_t*>(pRelativeAddress);
		pRelativeAddress += nPostOffset;
		return pRelativeAddress;
	}
};