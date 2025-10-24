#include <PCH/Internal.h>
#include <CS2/Hooks/Client/GetMatrixForView.h>
#include <HookHelper/HookHelper.h>
#include <Math/Matrix.h>
#include <Memory/PatternScan.h>
#include <CS2/Patterns/Client.h>
namespace CS2 {
	namespace Hooks {

		namespace Client {


			::Hook::Generic<GetMatrixForViewDef>* hkGetMatrixForView = new ::Hook::Generic<GetMatrixForViewDef>(
				CLIENT_DLL, GET_MATRIX_FOR_VIEW_PATTERN, +[](CRenderGameSystem* pRenderGameSystem,
					CViewRender* pViewRender,
					ViewMatrix_t* pOutWorldToView,
					ViewMatrix_t* pOutViewToProjection,
					ViewMatrix_t* pOutWorldToProjection,
					ViewMatrix_t* pOutWorldToPixels) -> ViewMatrix_t* {

						auto oFn = hkGetMatrixForView->GetOriginal();
						if (!oFn)
							return nullptr;

						ViewMatrix_t* matResult = oFn(
							pRenderGameSystem,
							pViewRender,
							pOutWorldToView,
							pOutViewToProjection,
							pOutWorldToProjection,
							pOutWorldToPixels
						);

						if (pOutWorldToProjection)
							Globals::viewMatrix = *pOutWorldToProjection;

						return matResult;
				}, "GetMatrixForView"
			);
		}
	}
}