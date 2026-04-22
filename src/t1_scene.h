#pragma once
#include "t1_sceneitem.h"
#include <xx_grid2d_circle.h>

namespace Test1 {

	using SceneBase = Global::SceneBase;
	struct Scene : SceneBase {
		// 地图逻辑格子尺寸
		XYi mapSize{};
		// 地图总像素尺寸
		XY mapPixelSize{};
		// 地图布局数据( 值为 类型::cTypeId )
		xx::List<int32_t> mapData;

		// 空间索引 / 物理相关
		xx::Grid2dCircle<SceneItem*, GridCache> gridTrees;
		xx::Shared<PhysSystem> physZombies;
		// 所有树
		xx::List<xx::Shared<Tree>> trees;
		// 所有僵尸
		xx::List<xx::Shared<Zombie>> zombies;
		// 弓箭塔
		xx::Shared<Tower> tower;
		// 所有弓箭手的箭矢
		xx::List<xx::Shared<TowerArrow>> towerArrows;
		// 所有怪物爆炸特效
		xx::List<xx::Shared<Exploder>> exploders;
		// 所有伤害文字
		xx::EffectTextManager effectTexts;

		// 所有进怪点坐标
		xx::List<XYi> enterPoss;
		// 所有空地坐标( 用来初始放置随机位置的 zombie0 )
		xx::List<XYi> spacePoss;

		// for draw floorMaskTex, light ...
		xx::FrameBuffer frameBuffer;
		xx::Shared<xx::GLTexture> floorMaskTex;
		xx::List<FloorMask> floorMasks;

		// 地图生成
		void GenWorld();

		// 处理建筑重叠( 圆形判断，会挪移 pos 令重叠消失 )
		void HandleBuildingsCross(XY& pos_, float radius_);

		void Init() override;
		void Update() override;
		void FixedUpdate() override;
		void Draw() override;
		void OnResize(bool modeChanged_) override;
	};

}
