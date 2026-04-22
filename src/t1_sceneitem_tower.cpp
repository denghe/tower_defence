#include "pch.h"
#include "t1_.h"

namespace Test1 {

	XY Tower::GetShootPos() const {
		return pos + XY{ 0, -100.f };
	}

	void Tower::Init(Scene* scene_, XY pos_) {
		typeId = cTypeId;
		scene = scene_;
		pos = pos_;
		y = pos.y;
		radius = cItemRadius * 2.f;
		scale = 2.f;
		radians = {};

		// 初始化数据面板
		healthMaxDefault = 100.f;
		PropsInit();
		// 测试下暴击效果
		criticalDamagePreset = 3.f;
		criticalChancePreset = 0.2f;	
		PropsCalc();
	}

	void Tower::Update() {
		if (scene->time >= nextShootTime) {
			// 尝试攻击射程内最近怪
			auto searchRange = scene->mapPixelSize.x * 0.5f;
			// 从找到第一个开始判断后续 range 值如果变化就不是同一批了. 在同一批中选最近
			float minMag2{}, currentBatchRange{};
			Zombie* tar{};
			auto g = scene->physZombies.pointer;
			auto cri = g->PosToCRIndex(pos);
			g->ForeachByRange(cri.y, cri.x, searchRange, gg.sgrdd, [&](PhysSystem::Node& node, float range)->bool {
				auto d = pos - node.cache.pos;
				auto mag2 = d.x * d.x + d.y * d.y;
				// todo: 精确射程检测?
				if (!tar) {
					minMag2 = mag2;
					currentBatchRange = range;
					tar = (Zombie*)node.value;
				}
				else {
					if (currentBatchRange != range) return true;
					if (mag2 < minMag2) {
						minMag2 = mag2;
						tar = (Zombie*)node.value;
					}
				}
				return false;
			});
			if (tar) {
				nextShootTime = scene->time + cShootInterval;
				scene->towerArrows.Emplace().Emplace()->Init(this, tar);
			}
			else {
				nextShootTime = scene->time + cSearchInterval;
			}
		}
	}

	void Tower::Draw() {
		// todo: 根据血量切破损图
		gg.Quad().DrawFrame(gg.pics.td_tower1_[0], scene->cam.ToGLPos(pos)
			, scale * scene->cam.scale, radians);
	}

	void Tower::DrawLight() {
		gg.Quad().DrawFrame(gg.pics.c64_light, scene->cam.ToGLPos(pos)
			, scene->mapPixelSize.y / 32.f * scene->cam.scale, 0, 0.5f);
	}

	void Tower::DrawShadow() {
		gg.Quad().DrawFrame(gg.pics.c64_shadow, scene->cam.ToGLPos(pos)
			, radius / 32.f * scene->cam.scale, 0, 1.f, {77,77,77,77});
	}

	void Tower::Dispose() {
		assert(scene);
		assert(!disposing);
		assert(indexAtContainer != -1);

		// 设置标记
		disposing = true;

		// 从容器中移除对象( 释放内存 )
		scene->tower.Reset();
	}

}
