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
		// for 跳
		float offsetY{};
		// for 呼吸
		float scaleX{}, scaleY{ 1 };

		void DrawHPBar() override;
		void DrawLight() override;
		void DrawShadow() override;
		void Draw() override;

		// 令怪物受伤( 可能会死 ).
		// 返回 实际受伤血量 & 状态: 0 正常 1 被闪避 2 死亡( 对象已 Dispose )
		std::pair<float, int> Hurt(float attackValue_) override;

		void Dispose() override;
	};

}
