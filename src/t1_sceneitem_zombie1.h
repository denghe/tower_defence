#pragma once
#include "t1_scene.h"

namespace Test1 {

	// 缓慢向塔移动僵尸，会近战攻击
	struct Zombie1 : Zombie {
		static constexpr int32_t cTypeId{ 4 };

		static constexpr float cMoveSpeed{ 200.f };

		// 攻击有效距离( 超出半径和 的部分 容差 )
		static constexpr float cAttackDistance{ 20.f };
		// 角度先顺时针旋转 10 度 再逆时针旋转 30 度
		static constexpr xx::FromTo<float> cAttackRadians{ -10.f / 180.f * gPI, 30.f / 180.f * gPI };
		// 角度旋转用时
		static constexpr xx::FromTo<float> cAttackDuration{ 0.5f, 0.2f };
		// 角度每帧步进值
		static constexpr xx::FromTo<float> cAttackRadiansFrameStep{ 
			cAttackRadians.from / (cAttackDuration.from * gg.cFps),
			cAttackRadians.to / (cAttackDuration.to * gg.cFps)
		};
		// 角度恢复到 0 度用时
		static constexpr float cAttackRestoreDuration{ 0.5f };
		// 角度恢复到 0 度 每帧步进值
		static constexpr float cAttackRestoreRadiansFrameStep{
			-cAttackRadians.to / (cAttackRestoreDuration * gg.cFps) };

		static constexpr float cIdleDuration{ 0.5f };
		static constexpr float cIdleScaleXRange{ 0.15f };
		static constexpr float cIdleStep{ 2.f / (gg.cFps * cIdleDuration) };

		// 呼吸效果( 周期变化 scale ). 用 _1
		int32_t _1{};
		float a1{};
		void Idle();

		// 近战攻击( 先转5度再转-30度 还原 )
		int32_t _2{};
		float a2{};
		void Attack();

		void Init(Scene* scene_, XY pos_);
		void Update() override;
	};

}
