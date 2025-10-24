#pragma once
#include <HookHelper/HookHelper.h>

class IDXGISwapChain;
class Renderer;
namespace steam {

	class GameOverlaySwapChainData {
	public:
		IDXGISwapChain* GetSwapChain();
		HWND GetRendererHwnd();
	};

	class GameOverlayRenderer {
	private:
		inline static Renderer* m_pRenderer = nullptr;
		static GameOverlaySwapChainData* GetSwapChainData();
		typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
		typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
	public:
		inline static Hook::Generic<Present>* hkPresentGeneric;
		static IDXGISwapChain* GetSwapChain();
		static HWND GetHwnd();

		static void SetRenderer(Renderer* pRenderer) { m_pRenderer = pRenderer; };
		static Renderer* GetRenderer() { return m_pRenderer; };
		static void HookDX(Renderer* pRenderer);
		static bool CreatePresentHook();
		static bool EnablePresentHook();
		static bool DisablePresentHook();
		static bool RemovePresentHook();
	};
}