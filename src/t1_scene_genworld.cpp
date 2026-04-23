#include "pch.h"
#include "t1_.h"

namespace Test1 {

	void Scene::GenWorld() {
		// 　：怪活动区域
		// 塔：玩家箭塔位置
		// 进：怪生成区
		// 树：树木
#if 1
		std::u32string_view mapText = UR"(
树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树
树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树
树树树树树树树树树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树树树树树树树树树
树树树树树树树树树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树树树树树树树树树
树树树树树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树树树树树
树树树树树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树树树树树
树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树
树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树
树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树
树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树
树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树
树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树
树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树
树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树
树进进　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　进进树
树进进　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　进进树
树进进　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　塔　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　进进树
树进进　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　进进树
树进进　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　进进树
树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树
树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树
树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树
树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树
树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树
树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树
树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树
树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树
树树树树树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树树树树树
树树树树树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树树树树树
树树树树树树树树树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树树树树树树树树树
树树树树树树树树树树树树树树树树　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　树树树树树树树树树树树树树树树树
树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树
树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树树
)";
#else
		std::u32string_view mapText = UR"(
树树树树树树树树树树树树树树树树树树树树树树树树树树树树树
树树树树树树树树树树树树树树树树树树树树树树树树树树树树树
树树树树树　　　　　　　　　　　　　　　　　　　树树树树树
树树树树树　　　　　　　　　　　　　　　　　　　树树树树树
树树树树　　　　　　　　　　　　　　　　　　　　　树树树树
树树树　　　　　　　　　　　　　　　　　　　　　　　树树树
树进进　　　　　　　　　　　　　　　　　　　　　　　进进树
树进进　　　　　　　　　　　塔　　　　　　　　　　　进进树
树进进　　　　　　　　　　　　　　　　　　　　　　　进进树
树树树　　　　　　　　　　　　　　　　　　　　　　　树树树
树树树树　　　　　　　　　　　　　　　　　　　　　树树树树
树树树树树　　　　　　　　　　　　　　　　　　　树树树树树
树树树树树　　　　　　　　　　　　　　　　　　　树树树树树
树树树树树树树树树树树树树树树树树树树树树树树树树树树树树
树树树树树树树树树树树树树树树树树树树树树树树树树树树树树
)";
#endif

		// 移除首行空换行
		while (true) {
			assert(!mapText.empty());
			if (auto c = mapText[0]; c == U'\r' || c == U'\n') {
				mapText = mapText.substr(1, mapText.size() - 1);
				continue;
			}
			break;
		}

		// 移除尾行空换行
		while (true) {
			assert(!mapText.empty());
			if (auto c = mapText.back(); c == U'\r' || c == U'\n') {
				mapText = mapText.substr(0, mapText.size() - 1);
				continue;
			}
			break;
		}

		// 计算总宽度
		int32_t mapWidth{};
		for (int i = 0, e = (int)mapText.size(); i < e; ++i) {
			if (auto c = mapText[i]; c == U'\r' || c == U'\n')
				break;
			++mapWidth;
		}

		// 计算总高度
		int32_t mapHeight{ 1 };
		int32_t x{};
		for (int i = 0, e = (int)mapText.size(); i < e; ++i) {
			switch (auto c = mapText[i]) {
			case U'\r':
				continue;
			case U'\n':
				assert(x == mapWidth);	// 确保每一行长度一致
				x = 0;
				++mapHeight;
				continue;
			}
			++x;
		}

		// 预处理，规范数据内容，扫文本 翻译成对象类型编号二维数组
		mapData.Resize<true, 0>(mapWidth * mapHeight);	// 默认填 0 代表空格
		x = 0;
		int32_t y{};
		for (int i = 0, e = (int)mapText.size(); i < e; ++i) {
			switch (auto c = mapText[i]) {
			case U'\r': continue;
			case U'\n':
				x = 0;
				++y;
				continue;
			case U'树':
			case U'进':
			case U'塔':
				mapData[y * mapWidth + x] = c; break;
			}
			++x;
		}

		mapSize = { mapWidth, mapHeight };
		mapPixelSize = mapSize * cCellPixelSize;
		cam.Init(gg.scale, gg.designSize.y / mapPixelSize.y, mapPixelSize / 2);
		gridTrees.Init(cCellPixelSize, mapHeight, mapWidth);
		static constexpr auto cellSize = cCellPixelSize;
		physZombies.Emplace()->Init(this
			, std::ceilf(mapPixelSize.y / cellSize)
			, std::ceilf(mapPixelSize.x / cellSize)
			, cellSize, 5000, 15);
		floorMaskTex.Emplace()->Make(mapPixelSize);

		assert(gridTrees.pixelSize.x >= mapPixelSize.x);
		assert(gridTrees.pixelSize.y >= mapPixelSize.y);
		assert(physZombies->pixelSize.x >= mapPixelSize.x);
		assert(physZombies->pixelSize.y >= mapPixelSize.y);
		sortContainer.Resize<true>((int32_t)physZombies->pixelSize.y);

		// 逐行扫内容并 各种预生成 / 填充
		for (int32_t y = 0; y < mapHeight; y++) {
			for (x = 0; x < mapWidth; x++) {
				auto i = y * mapWidth + x;
				switch (mapData[i]) {
				case U'树':
					trees.Emplace().Emplace()->Init(this, XY{ x, y } * cCellPixelSize + cCellPixelHalfSize);
					break;
				case U'塔':
					tower.Emplace()->Init(this, XY{ x, y } * cCellPixelSize + cCellPixelHalfSize);
					break;
				case U'进':
					enterPoss.Emplace(x, y);
					break;
				default:
					spacePoss.Emplace(x, y);
				}
			}
		}

	}

}
