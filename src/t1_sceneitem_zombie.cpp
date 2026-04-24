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
		if (siz.x < 20) siz.x = 20;
		if (siz.y < 6) siz.y = 6;
		gg.HPBar().Alloc()->Fill(scene->cam.ToGLPos(p), siz, xx::RGBA8_Black, xx::RGBA8_White, xx::RGBA8_Red, percent);
	}

	void Zombie::DrawLight() {
		gg.Quad().DrawFrame(gg.pics.c64_light, scene->cam.ToGLPos(pos)
			, (radius * (6.f / 64.f)) * scene->cam.scale, 0, 0.5f);
	}

	void Zombie::DrawShadow() {
		gg.Quad().DrawFrame(gg.pics.c64_shadow, scene->cam.ToGLPos(pos)
			, (radius * (1.f / 45.f)) * scene->cam.scale, 0, 1.f, { 99,99,99,99 });
	}

	void Zombie::Draw() {
		XY s{ scale * scene->cam.scale };
		s.x *= scaleX;
		s.y *= scaleY;
		auto r = radians;
		if (flipX) {
			s.x = -s.x;
			r = -r;
		}
		float cp{ 1 };
		if (scene->time < whiteColorEndTime) cp = 10000.f;
		XY p{ pos.x, pos.y + offsetY };
		gg.Quad().DrawFrame(frame, scene->cam.ToGLPos(p), s, r, cp);
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

}
