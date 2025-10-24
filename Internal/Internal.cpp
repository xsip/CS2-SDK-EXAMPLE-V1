#include <PCH/Internal.h>
#include <fstream>
#include <SDK/client/CBasePlayerController.hpp>
#include <Steam/GameOverlayRenderer.h>
#include <Rendering/Renderer.h>
#include <Utils/Utils.h>

auto pRenderer = new Renderer({});
DWORD TestingThread(HMODULE hModule) {

    while (!GetAsyncKeyState(VK_DELETE)) {

    }

    ::Utils::RemoveConsoleWindow();

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

    steam::GameOverlayRenderer::HookDX(pRenderer);

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