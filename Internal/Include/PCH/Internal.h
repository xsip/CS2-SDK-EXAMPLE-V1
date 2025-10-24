#include <Windows.h>
#include <string>
#include <stdexcept>

#include <minhook/include/MinHook.h>

#ifndef S2_PAD
#define S2_PAD_INSERT(x, y) x ## y
#define S2_PAD_DEFINE(x, y) S2_PAD_INSERT(x, y)
#define S2_PAD(size) char S2_PAD_DEFINE(padding_, __LINE__)[size]
#endif

#include <SDK/GlobalTypes.hpp>

#include <Source2/Types/CUtlVector.h>