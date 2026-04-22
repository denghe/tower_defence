#pragma once
#include "pch.h"
#include <xx_frame.h>

struct _pics {
	xx::Frame td_arrow;
	xx::Frame td_ring;
	std::array<xx::Frame, 1> td_grass_;
	std::array<xx::Frame, 4> td_tower1_;
	std::array<xx::Frame, 1> td_tree_;
	std::array<xx::Frame, 9> td_zombie_;

	xx::Shared<xx::GLTexture> Load(std::string picFN_, bool generateMipmap_ = true);
};
