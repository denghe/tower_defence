#include "pch.h"
#include <xx_gamebase.h>
#include "_pics.h"

xx::Shared<xx::GLTexture> _pics::Load(std::string picFN_, bool generateMipmap_) {
	auto t = xx::GameBase::instance->LoadTexture(picFN_);
	if(generateMipmap_) t->TryGenerateMipmap();

	this->td_arrow = { t, 930, 9, 32, 128, { 0.46875, 0.84375 } };
	this->td_ring = { t, 9, 393, 128, 128, { 0.5, 0.5 } };
	this->td_grass_[0] = { t, 9, 9, 459, 256, { 0.5, 0.5 } };
	this->td_tower1_[0] = { t, 755, 147, 128, 187, { 0.5, 0.12 } };
	this->td_tower1_[1] = { t, 755, 344, 128, 187, { 0.5, 0.12 } };
	this->td_tower1_[2] = { t, 9, 561, 128, 187, { 0.5, 0.12 } };
	this->td_tower1_[3] = { t, 9, 758, 128, 187, { 0.5, 0.12 } };
	this->td_tree_[0] = { t, 617, 147, 128, 236, { 0.5, 0.084746 } };
	this->td_zombie_[0] = { t, 478, 9, 151, 128, { 0.390728, 0.039062 } };
	this->td_zombie_[1] = { t, 282, 275, 105, 128, { 0.457143, 0.03125 } };
	this->td_zombie_[2] = { t, 893, 423, 110, 128, { 0.454545, 0.039062 } };
	this->td_zombie_[3] = { t, 478, 147, 129, 128, { 0.410853, 0.039062 } };
	this->td_zombie_[4] = { t, 893, 285, 118, 128, { 0.313559, 0.039062 } };
	this->td_zombie_[5] = { t, 786, 9, 134, 128, { 0.477612, 0.039062 } };
	this->td_zombie_[6] = { t, 893, 147, 121, 128, { 0.495868, 0.03125 } };
	this->td_zombie_[7] = { t, 639, 9, 137, 128, { 0.343066, 0.03125 } };
	this->td_zombie_[8] = { t, 147, 275, 125, 128, { 0.448, 0.039062 } };
	return t;
};
