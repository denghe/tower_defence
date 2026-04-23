#include "pch.h"
#include "t1_.h"

namespace Test1 {

	void Zombie1::Init(Scene* scene_, XY pos_) {
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
		frame = gg.pics.td_zombie_[1];

		indexAtContainer = scene->zombies.len - 1;
		assert(scene->zombies[indexAtContainer].pointer == this);

		scene->physZombies->Add(this);

		// 初始化数据面板
		healthMaxDefault = 100.f;
		PropsInit();
		PropsCalc();
	}

	void Zombie1::Idle() {
		XX_BEGIN(_1);
		while (true) {
			for (a1 = -1.f; a1 < 1.f; a1 += cIdleStep) {
				scaleX = 1.f - (1.f - a1 * a1) * cIdleScaleXRange;
				scaleY = 2.f - scaleX;
				XX_YIELD(_1);
			}
		}
		XX_END(_1);
	}

	void Zombie1::Attack() {
		XX_BEGIN(_2);

		// 顺时针旋转
		for (radians = 0.f; radians > cAttackRadians.from; radians += cAttackRadiansFrameStep.from) {
			XX_YIELD(_2);
		}

		// 逆时针旋转
		for (radians = cAttackRadians.from; radians < cAttackRadians.to; radians += cAttackRadiansFrameStep.to) {
			XX_YIELD(_2);
		}

		// todo: 距离判断( 可能正在攻击过程中被挤开了 ) & 伤害 tower

		// 顺时针旋转
		for (radians = cAttackRadians.to; radians > 0.f; radians += cAttackRestoreRadiansFrameStep) {
			XX_YIELD(_2);
		}

		// 重置 Attack 协程状态
		_2 = 0;
		XX_END(_2);
	}

	void Zombie1::Update() {
		// 驱动怪身上挂的 dots. 如果导致已 Dispose 就直接 return ( 指针已野 )
		if (DotsUpdate(this)) return;

		if (_2) {
			// 如果当前正在做攻击动作，那就继续做完
			Attack();
		}
		else {
			// 算距离
			auto tar = scene->tower->pos;
			auto d = tar - pos;
			auto mag2 = d.x * d.x + d.y * d.y;
			auto r = radius + scene->tower->radius + cAttackDistance;
			if (mag2 > r * r) {
				// 如果距离 tower 太远，向 tower 移动
				auto norm = d / std::sqrtf(mag2);
				scene->physZombies->At(this).accel += norm * cMoveSpeed;
				Idle();
			}
			else {
				// 距离够就开始攻击
				assert(!_2);
				Attack();
			}
		}
	}

}
