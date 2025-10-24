#include <PCH/Internal.h>
#include <Steam/GameOverlayRenderer.h>
#include <Memory/PatternScan.h>
#include <Memory/VTableHelper.h>
#include <D3DX11.h>
#include <dxgi.h>
#include <HookHelper/HookHelper.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/backends/imgui_impl_dx11.h>
#include <Rendering/Renderer.h>
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace steam {

	HWND window = NULL;
	WNDPROC oWndProc;
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* mainRenderTargetView;
	ImVec2 DisplaySize = ImVec2(0, 0);
	bool initialized = false;
	bool showMenu = false;
	bool init = false;

	void InitImGui()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		// io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(pDevice, pContext);
	}

	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
			return true;

		}
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	}

	HRESULT __stdcall PresentDetour(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		if (!init)
		{

			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
			{
				pDevice->GetImmediateContext(&pContext);
				DXGI_SWAP_CHAIN_DESC sd;
				pSwapChain->GetDesc(&sd);
				window = sd.OutputWindow;
				ID3D11Texture2D* pBackBuffer;
				pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
				pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
				pBackBuffer->Release();
				oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
				InitImGui();
				init = true;
			}

			else
				return ::steam::GameOverlayRenderer::hkPresentGeneric->GetOriginal()(pSwapChain, SyncInterval, Flags);
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

		io.MouseDrawCursor = showMenu;
		io.WantCaptureKeyboard = showMenu;
		io.WantCaptureMouse = showMenu;
		// ImGui::GetIO().MouseDrawCursor = teleportMenuOpen;
		RECT rect;
		::GetClientRect(window, &rect);
		DisplaySize = ImVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));
		::steam::GameOverlayRenderer::GetRenderer()->Render(DisplaySize);
		ImGui::Render();

		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		return ::steam::GameOverlayRenderer::hkPresentGeneric->GetOriginal()(pSwapChain, SyncInterval, Flags);
	}


	GameOverlaySwapChainData* GameOverlayRenderer::GetSwapChainData() {

		auto pInstruction = reinterpret_cast<uintptr_t>(PatternScan::Single("gameoverlayrenderer64.dll", "48 8B 0D ?? ?? ?? ?? 48 05"));

		auto pAddr = PatternScan::InstructionValue(pInstruction, 0x3, 0x7);
		auto data = *reinterpret_cast<GameOverlaySwapChainData**>(pAddr);
		return data;
	}



	IDXGISwapChain* GameOverlaySwapChainData::GetSwapChain() {
		return *reinterpret_cast<IDXGISwapChain**>(this + 0x148);
	}

	IDXGISwapChain* GameOverlayRenderer::GetSwapChain() {
		return GetSwapChainData()->GetSwapChain();
	}

	void GameOverlayRenderer::HookDX(Renderer* pRenderer)
	{
		steam::GameOverlayRenderer::SetRenderer(pRenderer);
		steam::GameOverlayRenderer::CreatePresentHook();
		steam::GameOverlayRenderer::EnablePresentHook();
	}

	bool GameOverlayRenderer::CreatePresentHook()
	{
		auto pSwapChain = GetSwapChain();
		auto presentFn = VTable::GetFunction<8>(pSwapChain);

		hkPresentGeneric = new Hook::Generic<Present>(reinterpret_cast<void*>(presentFn), PresentDetour, "PresentHook");
		hkPresentGeneric->Create();
		return false;
	}

	bool GameOverlayRenderer::EnablePresentHook()
	{
		hkPresentGeneric->Enable();
		return true;
	}

	bool GameOverlayRenderer::DisablePresentHook()
	{
		hkPresentGeneric->Disable();
		return true;
	}

	bool GameOverlayRenderer::RemovePresentHook()
	{
		hkPresentGeneric->Remove();
		return true;
	}


	HWND GameOverlaySwapChainData::GetRendererHwnd()
	{
		using GetHwndDef = HWND(__fastcall*)(GameOverlaySwapChainData*);
		auto getHwndFn = reinterpret_cast<GetHwndDef>(PatternScan::Single("gameoverlayrenderer64.dll", "48 83 EC ?? 48 8B 89 ?? ?? ?? ?? 48 85 C9 74 24 48 8B 01 48 8D 54 24 ?? FF 50 ?? 85 C0 78 15 48 8B 44 24 ?? 48 85 C0 48 0F 44 05 ?? ?? ?? ?? 48 83 C4 ?? C3 33 C0 48 83 C4 ?? C3"));
		return getHwndFn(this);
	}

	HWND GameOverlayRenderer::GetHwnd() {
		return GetSwapChainData()->GetRendererHwnd();
	}

}