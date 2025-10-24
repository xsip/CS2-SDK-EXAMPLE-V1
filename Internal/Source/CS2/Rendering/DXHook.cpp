#include <PCH/Internal.h>
#include <CS2/Rendering/DXHook.h>
#include <Memory/PatternScan.h>
#include <D3DX11.h>
#include <dxgi.h>
#include <Memory/VTableHelper.h>
#include <HookHelper/HookHelper.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/backends/imgui_impl_dx11.h>
#include <wrl/client.h>
#include <Steam/GameOverlayRenderer.h>
using Microsoft::WRL::ComPtr;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace CS2 {
	CS2DX11Hook* cs2Dx11Hook = new CS2DX11Hook();
	typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);


	Hook::Generic<Present>* hkPresentGeneric;
	Present oPresent;
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
		printf("WndProc is running!\n");
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
				return hkPresentGeneric->GetOriginal()(pSwapChain, SyncInterval, Flags);
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
		auto pDrawList = ImGui::GetBackgroundDrawList();
		ImGui::Render();

		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		return hkPresentGeneric->GetOriginal()(pSwapChain, SyncInterval, Flags);
	}

	void CS2DX11Hook::Initialize() {

		auto pSwapChain = ::steam::GameOverlayRenderer::GetSwapChain();
		auto presentFn = VTable::GetFunction<8>(pSwapChain);

		hkPresentGeneric = new Hook::Generic<Present>(reinterpret_cast<void*>(presentFn), PresentDetour, "PresentHook");
		hkPresentGeneric->Enable(true);

	}
	void CS2DX11Hook::Shutdown() {
		hkPresentGeneric->Disable();
		hkPresentGeneric->Remove();
	}
}
