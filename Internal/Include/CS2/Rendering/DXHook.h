#pragma once
#include <HookHelper/HookHelper.h>
#include <D3DX11.h>
#include <dxgi.h>
namespace CS2 {
	class CS2DX11Hook {
	public:
		void Initialize();
		void Shutdown();
	};
	extern CS2DX11Hook* cs2Dx11Hook;
}