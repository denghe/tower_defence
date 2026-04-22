#pragma once
#include "t1_scene.h"

namespace Test1 {

	// 僵尸基类
	struct Zombie : SceneProps12DotItem {
		// 当前贴图. 需要在 init 中赋值
		xx::Frame frame;

		// 每次挨打变白的时长
		static constexpr float cWhiteColorDuration{ 0.1f };

		// 挨打变白结束时间点
		float whiteColorEndTime{};
		float offsetY{}, scaleX{};

		void DrawHPBar() override;
		void DrawLight() override;
		void DrawShadow() override;
		void Draw() override;

		// 令怪物受伤( 可能会死 ).
		// 返回 实际受伤血量 & 状态: 0 正常 1 被闪避 2 死亡( 对象已 Dispose )
		std::pair<float, int> Hurt(float attackValue_) override;

		void Dispose() override;
	};

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
		int32_t _3{}, numLeftSteps{};
		XY moveDirection{};
		void Init(Scene* scene_, XY pos_);
		void Update() override;
	};
}
