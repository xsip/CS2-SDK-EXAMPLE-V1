#include <PCH/Internal.h>
#include <CS2/Rendering/RenderObjects/EspRenderObject.h>

#include <CS2/Enums/Bones.h>
#include <CS2/ExtendedSDK/C_CSPlayerPawn.h>
#include <SDK/client/CCSPlayerController.hpp>
#include <CS2/Interfaces/CGameEntitySystem.h>
#include <Source2/Types/CBaseHandle.h>
#include <Math/Vector.h>
#include <math/Matrix.h>
#include <CS2/Interfaces/Include.h>

#undef min;
#undef max;

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace CS2 {


	void EspRenderObject::Render(ImVec2 displaySize/*, ImVec2 cursorPos, bool bMouseReleased*/) {
		auto pBackgroundDrawList = ImGui::GetBackgroundDrawList();

		ViewMatrix_t ViewMatrix = Globals::viewMatrix;
		auto pGameEntitySystem = CS2::I::GetGameEntitySystem();
		auto localController = pGameEntitySystem->GetEntityByIndex<CS2::client::CCSPlayerController>(1);
		auto localPawn = pGameEntitySystem->GetEntityByIndex < CS2::client::C_CSPlayerPawnExtended>(localController->m_hPawn.GetEntryIndex());

		for (int i = 1; i < 65; i++) {
			auto pCtrler = pGameEntitySystem->GetEntityByIndex<CS2::client::CCSPlayerController>(i);
			bool bIsLocalPlayer = i == 1;

			if (bIsLocalPlayer)
				continue;

			if (!pCtrler)
				continue;

			auto pPawn = pGameEntitySystem->GetEntityByIndex<CS2::client::C_CSPlayerPawnExtended>(pCtrler->m_hPawn.GetEntryIndex());

			if (!pPawn)
				continue;

			if (pPawn->m_iHealth <= 1 || pPawn->m_iHealth > pPawn->m_iMaxHealth)
				continue;


			auto vBoneMatrices = pPawn->GetBoneMatrices();

			if (!vBoneMatrices)
				continue;

			auto vHeadBoneMatrix = vBoneMatrices[CS2::Bones::BONE_HEAD_0];


			auto vEnemyHead = vHeadBoneMatrix.GetOrigin();




			if (!vEnemyHead.IsValid() || vEnemyHead.IsZero())
				continue;



			auto vEnemyLAnkle = pPawn->m_vOldOrigin;

			if (!vEnemyHead.IsValid() || vEnemyHead.IsZero())
				continue;

			Vector headScreen;
			Vector ankleScreen;



			if (!vEnemyHead.ToScreen(ViewMatrix, displaySize.x, displaySize.y, headScreen) || !vEnemyLAnkle.ToScreen(ViewMatrix, displaySize.x, displaySize.y, ankleScreen))
				continue;


			float height = (ankleScreen.y - headScreen.y);
			float width = height / 1.75f;

			float x = ankleScreen.x - width / 2;

			pBackgroundDrawList->AddRect({ x, (headScreen.y - (height * 0.12f)) }, { x + width, headScreen.y + height }, ImColor(35, 35, 35, 200));
			DrawHealthBar(pBackgroundDrawList, pPawn->m_iMaxHealth, pPawn->m_iHealth, ImVec2(x - 10.0f, (headScreen.y - (height * 0.12f))), ImVec2(5.0f, height + (height * 0.12f)), false);
		}
	}


	void EspRenderObject::DrawHealthBar(ImDrawList* DrawList, float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, bool Horizontal)
	{
		float Proportion = CurrentHealth / MaxHealth;

		ImColor FirstStageColor = ImColor(96, 246, 113, 220);
		ImColor SecondStageColor = ImColor(247, 214, 103, 220);
		ImColor ThirdStageColor = ImColor(255, 95, 95, 220);
		ImColor BackGroundColor = ImColor(90, 90, 90, 220);
		ImColor Color;
		if (Proportion > 0.5)
			Color = FirstStageColor;
		else if (Proportion > 0.25)
			Color = SecondStageColor;
		else
			Color = ThirdStageColor;

		DrawList->AddRectFilled(Pos, { Pos.x + Size.x, Pos.y + Size.y }, BackGroundColor);

		if (Horizontal)
			DrawList->AddRectFilled(Pos, { Pos.x + Size.x * Proportion, Pos.y + Size.y }, Color);

		else
		{
			float healthHeight = Size.y * Proportion;
			DrawList->AddRectFilled({ Pos.x, Pos.y + Size.y - healthHeight }, { Pos.x + Size.x, Pos.y + Size.y }, Color);
		}

		ImColor BorderColor = ImColor(45, 45, 45, 220);
		DrawList->AddRect(Pos, { Pos.x + Size.x, Pos.y + Size.y }, BorderColor);
	}
}