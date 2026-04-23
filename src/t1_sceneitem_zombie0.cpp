#include "pch.h"
#include "t1_.h"

namespace Test1 {

	void Zombie0a::Init(Scene* scene_, XY pos_) {
		// 超出地图边界，硬拉?
		auto s = scene_->mapPixelSize - cCellPixelSize;
		if (pos_.x >= s.x) 
			pos_.x = s.x;
		else if (pos_.x < cCellPixelSize)
			pos_.x = cCellPixelSize;
		if (pos_.y >= s.y) 
			pos_.y = s.y;
		else if (pos_.y < cCellPixelSize)
			pos_.y = cCellPixelSize;

		typeId = cTypeId;
		scene = scene_;
		pos = pos_;
		y = pos_.y;
		radius = cItemRadius;
		scale = 1.f;
		radians = {};
		flipX = pos_.x > scene->tower->pos.x;
		frame = gg.pics.td_zombie_[0];

		indexAtContainer = scene->zombies.len - 1;
		assert(scene->zombies[indexAtContainer].pointer == this);

		scene->physZombies->Add(this);

		// 初始化数据面板
		healthMaxDefault = 100.f;
		PropsInit();
		PropsCalc();
	}

	void Zombie0a::JumpUpAndScale() {
		XX_BEGIN(_1);
		while (true) {
			for (a1 = -1.f; a1 < 1.f; a1 += cJumpStep) {
				offsetY = -(1.f - a1 * a1) * cJumpHeight;
				scaleX = 1.f - (1.f - a1 * a1) * cJumpScaleXRange;
				XX_YIELD(_1);
			}
		}
		XX_END(_1);
	}

	void Zombie0a::Update() {
		// 驱动怪身上挂的 dots. 如果导致已 Dispose 就直接 return ( 指针已野 )
		if (DotsUpdate(this)) return;

		// 跳. offsetY 和 scaleX 都会发生周期变化
		JumpUpAndScale();
	}

	/**********************************************************************/
	/**********************************************************************/

	void Zombie0b::Init(Scene* scene_, XY pos_) {
		Zombie0a::Init(scene_, pos_);
		typeId = cTypeId;
	}

	void Zombie0b::Update() {
		// 驱动怪身上挂的 dots. 如果导致已 Dispose 就直接 return ( 指针已野 )
		if (DotsUpdate(this)) return;

		// 跳. offsetY 和 scaleX 都会发生周期变化
		JumpUpAndScale();

		// 选个随机方向移动一段距离
		static constexpr float cMoveSpeed{ 500.f };
		XX_BEGIN(_2);
		while (true) {
			{
				auto r = gg.rnd.NextRadians<float>();
				moveDirection.x = std::cosf(r) * cMoveSpeed;
				moveDirection.y = std::sinf(r) * cMoveSpeed;
				numLeftSteps = gg.cFps * cJumpDuration;
			}
			for (; numLeftSteps > 0; --numLeftSteps) {
				scene->physZombies->At(this).accel += moveDirection;
				XX_YIELD(_2);
			}
		}
		XX_END(_2);
	}
}
