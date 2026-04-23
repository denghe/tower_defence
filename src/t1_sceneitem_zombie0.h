#pragma once
#include "t1_scene.h"

namespace Test1 {

	// 原地跳僵尸
	struct Zombie0a : Zombie {
		static constexpr int32_t cTypeId{ 4 };
		static constexpr float cJumpDuration{ 1.5f };		// 滞空时长
		static constexpr float cJumpHeight{ 100.f };		// 像素
		static constexpr float cJumpScaleXRange{ 0.2f };	// scale x 变化幅度
		static constexpr float cJumpStep{ 2.f / (gg.cFps * cJumpDuration) };

		int32_t _1{};
		float a1{};
		void JumpUpAndScale();

		void Init(Scene* scene_, XY pos_);
		void Update() override;
	};

	// 移动跳僵尸
	struct Zombie0b : Zombie0a {
		static constexpr int32_t cTypeId{ 3 };
		int32_t _2{}, numLeftSteps{};
		XY moveDirection{};
		void Init(Scene* scene_, XY pos_);
		void Update() override;
	};
}
