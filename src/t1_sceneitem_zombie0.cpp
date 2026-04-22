#include "pch.h"
#include "t1_.h"

namespace Test1 {


	void Zombie::DrawHPBar() {
		// 显示触发条件：带属性, 非满血
		if (health == healthMax) return;
		auto percent = (float)health / healthMax;
		auto& f = gg.pics.td_zombie_[0];
		XY siz{ 100 * scale, 15 };
		auto p = pos + XY{ -siz.x * 0.5f, (f.uvRect.h * f.anchor.y + 1) * scale };
		siz *= scene->cam.scale;
		if (siz.x < 10) siz.x = 10;
		if (siz.y < 4) siz.y = 4;
		gg.HPBar().Alloc()->Fill(scene->cam.ToGLPos(p), siz, xx::RGBA8_Black, xx::RGBA8_White, xx::RGBA8_Red, percent);
	}

	void Zombie::DrawLight() {
		gg.Quad().DrawFrame(gg.pics.c64_light, scene->cam.ToGLPos(pos)
			, (radius * (6.f / 64.f)) * scene->cam.scale, 0, 0.5f);
	}

	void Zombie::DrawShadow() {
		gg.Quad().DrawFrame(gg.pics.c64_shadow, scene->cam.ToGLPos(pos)
			, (radius * (1.f / 40.f)) * scene->cam.scale, 0, 1.f, { 77,77,77,77 });
	}

	void Zombie::Draw() {
		XY s{ scale * scene->cam.scale };
		s.x *= scaleX;
		if (flipX) s.x = -s.x;
		float cp{ 1 };
		if (scene->time < whiteColorEndTime) cp = 10000.f;
		XY p{ pos.x, pos.y + offsetY };
		gg.Quad().DrawFrame(frame, scene->cam.ToGLPos(p), s, radians, cp);
	}

	void Zombie::Dispose() {
		assert(scene);
		assert(!disposing);
		assert(indexAtContainer != -1);
		auto& container = scene->zombies;
		assert(container[indexAtContainer].pointer == this);

		// 设置标记
		disposing = true;

		// 进一步释放资源
		scene->physZombies->Remove(this);

		// 调用回调函数
		CallDisposeCallbacks();

		// 从容器中移除对象( 释放内存 )
		auto i = indexAtContainer;
		container.Back()->indexAtContainer = i;
		indexAtContainer = -1;
		container.SwapRemoveAt(i);
	}

	std::pair<float, int> Zombie::Hurt(float attackValue_) {
		auto r = PropsDoHurt(gg.rnd, attackValue_);
		if (r.second == 0) {
			// 变白
			whiteColorEndTime = scene->time + cWhiteColorDuration;
		}
		else if (r.second == 2) {
			// 爆炸特效
			scene->exploders.Emplace().Emplace()->Init(this);
			// 自杀
			Dispose();
		}
		return r;
	}

	/**********************************************************************/
	/**********************************************************************/

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
		dodgePreset = dodgeFactor;	// 测试下闪避效果。 1/2 概率挨打
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
		// todo: 万一卡怪? 整个长超时自杀?

		// 驱动怪身上挂的 dots. 如果导致已 Dispose 就直接 return ( 指针已野 )
		if (DotsUpdate(this)) return;

		// 跳. offsetY 和 scaleX 都会发生周期变化
		JumpUpAndScale();

		/*
		// 向 tower 移动
		static constexpr float cMoveSpeed{ 200.f };
		auto tar = scene->tower->pos;
		auto d = tar - pos;
		auto mag2 = d.x * d.x + d.y * d.y;
		if (mag2 > 0.001f) {
			auto norm = d / std::sqrtf(mag2);
			scene->physZombies->At(this).accel += norm * cMoveSpeed;
		}
		*/

	}

	/**********************************************************************/
	/**********************************************************************/

	void Zombie0b::Init(Scene* scene_, XY pos_) {
		Zombie0a::Init(scene_, pos_);
		typeId = cTypeId;
	}

	void Zombie0b::Update() {
		// todo: 万一卡怪? 整个长超时自杀?

		// 驱动怪身上挂的 dots. 如果导致已 Dispose 就直接 return ( 指针已野 )
		if (DotsUpdate(this)) return;

		// 跳. offsetY 和 scaleX 都会发生周期变化
		JumpUpAndScale();

		// 选个随机方向移动一段距离
		static constexpr float cMoveSpeed{ 500.f };
		XX_BEGIN(_3);
		while (true) {
			{
				auto r = gg.rnd.NextRadians<float>();
				moveDirection.x = std::cosf(r) * cMoveSpeed;
				moveDirection.y = std::sinf(r) * cMoveSpeed;
				numLeftSteps = gg.cFps * cJumpDuration;
			}
			for (; numLeftSteps > 0; --numLeftSteps) {
				scene->physZombies->At(this).accel += moveDirection;
				XX_YIELD(_3);
			}
		}
		XX_END(_3);
	}
}
