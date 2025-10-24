#include <PCH/Internal.h>
#include <Rendering/Renderer.h>
#include <Rendering/RenderObject.h>
#include <imgui/imgui.h>

void Renderer::RenderWatermark(ImVec2 displaySize) {
	auto pDrawList = ImGui::GetBackgroundDrawList();
	pDrawList->AddText(ImVec2(5, 5), ImColor(255, 255, 255, 230), "xsip's PureLiquid Internal v0.1");
}

void Renderer::Render(ImVec2 displaySize) {
	RenderWatermark(displaySize);
	for (auto& renderObject : renderObjects) {
		renderObject->Render(displaySize);
	}
}