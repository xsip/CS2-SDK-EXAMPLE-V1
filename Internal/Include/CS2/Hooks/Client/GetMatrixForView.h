#pragma once
#include <HookHelper/HookHelper.h>
struct ViewMatrix_t;
namespace CS2 {

	class CRenderGameSystem;
	class CViewRender;

	namespace Hooks {
		namespace Client {
			using GetMatrixForViewDef = ViewMatrix_t * (__fastcall*)(CRenderGameSystem* pRenderGameSystem, CViewRender* pViewRender, ViewMatrix_t* pOutWorldToView, ViewMatrix_t* pOutViewToProjection, ViewMatrix_t* pOutWorldToProjection, ViewMatrix_t* pOutWorldToPixels);
			extern ::Hook::Generic<GetMatrixForViewDef>* hkGetMatrixForView;
		}
	}
}