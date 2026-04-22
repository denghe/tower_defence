#pragma once
#include "t1_scene.h"

namespace Test1 {

	struct Zombie : SceneProps12DotItem {
		xx::Frame frame;
	};

	struct Zombie0 : Zombie {
		static constexpr int32_t cTypeId{ 4 };

		// 每次挨打变白的时长
		static constexpr float cWhiteColorDuration{ 0.1f };

		// 挨打变白结束时间点
		float whiteColorEndTime{};

		void Init(Scene* scene_, XY pos_);
		void Update() override;
		void Draw() override;
		void DrawHPBar() override;
		void DrawLight() override;
		void DrawShadow() override;
		void Dispose() override;

		// 令怪物受伤( 可能会死 ).
		// 返回 实际受伤血量 & 状态: 0 正常 1 被闪避 2 死亡( 对象已 Dispose )
		std::pair<float, int> Hurt(float attackValue_) override;
	};
}
