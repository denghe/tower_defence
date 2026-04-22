#include "pch.h"
#include "t1_.h"

namespace Test1 {

	void Scene::Init() {
		frameBuffer.Init();
		effectTexts.Init(&cam, 10000);
		ui.Emplace()->InitRoot(gg.scale * cUIScale);
		cursor.Emplace()->Init();
		cursor->frame = gg.pics.td_ring;
		GenWorld();

		for (int32_t i = 0; i < 200; i++) {
			auto cxy = gg.rnd.NextElement(spacePoss);
			XY offset{
				gg.rnd.Next<float>(cCellPixelSize),
				gg.rnd.Next<float>(cCellPixelSize)
			};
			zombies.Emplace().Emplace<Zombie0>()->Init(this, offset + cxy * cCellPixelSize);
		}
	}

}
