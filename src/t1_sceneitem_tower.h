#pragma once
#include "t1_scene.h"

namespace Test1 {

	struct Tower : SceneProps12DotItem {
		static constexpr int32_t cTypeId{ 7 };

		// 搜索时间间隔( 模拟反应时间 同时省点 cpu )
		static constexpr float cSearchInterval{ 0.2f };

		// 射击时间间隔
		static constexpr float cShootInterval{ 0.2f };

		// 下次射击时间
		float nextShootTime{};

		// 每次挨打变白的时长
		static constexpr float cWhiteColorDuration{ 0.1f };

		// 受伤后变白的持续时间
		float whiteColorEndTime{};

		// 返回射箭起始坐标( 和 pivot 不等价 )
		XY GetShootPos() const;

		// 令 tower 受伤( 可能会死 )
		// 返回 实际受伤血量 & 状态: 0 正常 1 被闪避 2 死亡( 对象已 Dispose )
		std::pair<float, int> Hurt(float attackValue_) override;

		void Init(Scene* scene_, XY pos_);
		void Update() override;
		void Draw() override;
		void DrawLight() override;
		void DrawShadow() override;
		void Dispose() override;
	};

}
