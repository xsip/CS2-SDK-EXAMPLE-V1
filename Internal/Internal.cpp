#include <PCH/Internal.h>
#include <fstream>
#include <CS2/Interfaces/Include.h>
#include <SDK/client/CCSPlayerController.hpp>
#include <SDK/client/C_CSPlayerPawn.hpp>
#include <Steam/GameOverlayRenderer.h>
#include <Rendering/Renderer.h>
#include <Utils/Utils.h>
#include <CS2/Hooks/Client/GetMatrixForView.h>
#include <CS2/Rendering/RenderObjects/EspRenderObject.h>

ViewMatrix_t Globals::viewMatrix;

auto pRenderer = new Renderer({});

DWORD TestingThread(HMODULE hModule) {


    steam::GameOverlayRenderer::HookDX(pRenderer);


    CS2::I::Initialize();

    CS2::Hooks::Client::hkGetMatrixForView->Enable(true);
    pRenderer->AddRenderObject(new CS2::EspRenderObject());

    while (!GetAsyncKeyState(VK_DELETE)) {
        if (GetAsyncKeyState(VK_LSHIFT) & 1) {
            auto pGameEntitySystem = CS2::I::GetGameEntitySystem();
            auto localController = pGameEntitySystem->GetEntityByIndex<CS2::client::CCSPlayerController>(1);
            auto localPawn = pGameEntitySystem->GetEntityByIndex < CS2::client::C_CSPlayerPawn>(localController->m_hPawn.GetEntryIndex());
            printf("Health: %i\n", localPawn->m_iHealth);
        }
    }

    ::Utils::RemoveConsoleWindow();

    steam::GameOverlayRenderer::DisablePresentHook();
    steam::GameOverlayRenderer::RemovePresentHook();
    
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    
    FreeLibrary(hModule);

    return 0;
}

void Setup(HMODULE hModule) {

    DisableThreadLibraryCalls(hModule);
    
    ::Utils::AddConsoleWindowIfNeeded("xsip's cs2 sdk example");

    printf("Base loaded.\n");

    MH_Initialize();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {

    switch (reason) {
    case DLL_PROCESS_ATTACH:
        Setup(hModule);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TestingThread, hModule, 0, 0);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }

}