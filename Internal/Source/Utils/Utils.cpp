#include <PCH/Internal.h>
#include <Utils/Utils.h>	

bool m_bConsoleInitialized = false;

void Utils::AddConsoleWindowIfNeeded(std::string szConsoleName) {
	if (m_bConsoleInitialized)
		return;
	m_bConsoleInitialized = true;
	AllocConsole();
	FILE* Dummy;
	freopen_s(&Dummy, "CONOUT$", "w", stdout);
	freopen_s(&Dummy, "CONIN$", "r", stdin);
	SetConsoleTitle(szConsoleName.c_str());
}
void Utils::RemoveConsoleWindow() {
	FreeConsole();
}