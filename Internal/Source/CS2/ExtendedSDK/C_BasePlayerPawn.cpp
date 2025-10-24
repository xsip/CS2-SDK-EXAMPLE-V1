#include <PCH/Internal.h>
#include <SDK/client/C_BasePlayerPawn.hpp>
#include <SDK/client/CSkeletonInstance.hpp>
#include <SDK/modellib/RenderSkeletonBone_t.hpp>

#include <Offsets/client/CSkeletonInstance.hpp>
#include <CS2/ExtendedSDK/C_CSPlayerPawn.h>
#include <CS2/Enums/Bones.h>
#include <utility>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Memory/PatternScan.h>

namespace CS2 {
    namespace client {

        Matrix2x4_t C_CSPlayerPawnExtended::GetMatrixForBone(Bones boneIdx) {
            return this->GetBoneMatrices()[boneIdx];
        }


        Matrix2x4_t* C_CSPlayerPawnExtended::GetBoneMatrices() {

            if (!this->m_pGameSceneNode)
                return nullptr;

            CSkeletonInstance* pSkeleton = reinterpret_cast<CSkeletonInstance*>(this->m_pGameSceneNode);
            if (!pSkeleton)
                return nullptr;

            auto pAddr = reinterpret_cast<uintptr_t>(&pSkeleton->m_modelState) + 0x80;
            Matrix2x4_t* pBoneMatrices = *reinterpret_cast<Matrix2x4_t**>(pAddr);

            return pBoneMatrices;
        }
    }
}