#pragma once
#include <imgui/imgui.h>
class RenderObject {
public:
	virtual void Render(ImVec2 displaySize) {
	};
};