#pragma once
#include <Rendering/RenderObject.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <vector>
#include <imgui/imgui.h>

namespace CS2 {
    class CBoneNode;
    class EspRenderObject : public RenderObject {
    public:
        EspRenderObject() {
            printf("Esp constructed...\n");
        };
        void Render(ImVec2 DisplaySize/*, ImVec2 cursorPos, bool bMouseReleased*/) override;
    private:
        void DrawHealthBar(ImDrawList*, float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, bool Horizontal);
    };
}