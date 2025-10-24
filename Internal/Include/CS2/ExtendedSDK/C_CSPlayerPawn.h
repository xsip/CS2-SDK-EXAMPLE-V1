#include <SDK/client/C_CSPlayerPawn.hpp>
#include <SDK/modellib/RenderSkeletonBone_t.hpp>
#include <SDK/modellib/CHitBox.hpp>

#include <Math/Matrix.h>
#include <utility>
#include <map>
struct Vector;
namespace CS2 {
	enum Bones: int;
	namespace client {
		class C_CSPlayerPawnExtended : public C_CSPlayerPawn {
		private:
		public:
			Matrix2x4_t* GetBoneMatrices();
			Matrix2x4_t GetMatrixForBone(Bones boneIdx);
		};
	}
}