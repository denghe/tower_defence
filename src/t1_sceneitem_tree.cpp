#include "pch.h"
#include "t1_.h"

namespace Test1 {

	void Tree::Init(Scene* scene_, XY pos_) {
		typeId = cTypeId;
		scene = scene_;
		pos = pos_;
		y = pos.y;
		radius = cItemRadius;
		scale = 1.f;
		radians = {};

		indexAtContainer = scene_->trees.len - 1;
		assert(scene_->trees[indexAtContainer].pointer == this);

		scene_->gridTrees.Add(indexAtGrid, this);
	}

	void Tree::Draw() {
		gg.Quad().DrawFrame(gg.pics.td_tree_[0], scene->cam.ToGLPos(pos)
			, scale * scene->cam.scale, radians);
	}

	void Tree::Dispose() {
		assert(scene);
		assert(!disposing);
		assert(indexAtContainer != -1);
		auto& container = scene->trees;
		assert(container[indexAtContainer].pointer == this);

		// 设置标记
		disposing = true;

		// 进一步释放资源
		if (indexAtGrid > -1) {
			scene->gridTrees.Remove(indexAtGrid, this);
		}

		// 从容器中移除对象( 释放内存 )
		auto i = indexAtContainer;
		container.Back()->indexAtContainer = i;
		indexAtContainer = -1;
		container.SwapRemoveAt(i);
	}

}
