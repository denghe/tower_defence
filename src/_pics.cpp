#include "pch.h"
#include <xx_gamebase.h>
#include "_pics.h"

xx::Shared<xx::GLTexture> _pics::Load(std::string picFN_, bool generateMipmap_) {
	auto t = xx::GameBase::instance->LoadTexture(picFN_);
	if(generateMipmap_) t->TryGenerateMipmap();

	this->c64_light = { t, 930, 9, 64, 64, { 0.5, 0.5 } };
	this->c64_shadow = { t, 930, 83, 64, 32, { 0.5, 0.5 } };
	this->cursor_default = { t, 893, 263, 12, 19, { 0, 1 } };
	this->td_arrow = { t, 930, 125, 32, 128, { 0.46875, 0.84375 } };
	this->td_ring = { t, 9, 393, 128, 128, { 0.5, 0.5 } };
	this->explosion_1_[0] = { t, 972, 125, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[1] = { t, 972, 167, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[2] = { t, 972, 209, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[3] = { t, 972, 251, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[4] = { t, 9, 963, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[5] = { t, 51, 963, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[6] = { t, 93, 963, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[7] = { t, 135, 963, 32, 32, { 0.5, 0.5 } };
	this->td_grass_[0] = { t, 9, 9, 459, 256, { 0.5, 0.5 } };
	this->td_tower1_[0] = { t, 755, 147, 128, 187, { 0.5, 0.12 } };
	this->td_tower1_[1] = { t, 755, 344, 128, 187, { 0.5, 0.12 } };
	this->td_tower1_[2] = { t, 9, 569, 128, 187, { 0.5, 0.12 } };
	this->td_tower1_[3] = { t, 9, 766, 128, 187, { 0.5, 0.12 } };
	this->td_tree_[0] = { t, 617, 147, 128, 236, { 0.5, 0.084746 } };
	this->td_zombie_[0] = { t, 478, 9, 151, 128, { 0.390728, 0.039062 } };
	this->td_zombie_[1] = { t, 432, 285, 105, 128, { 0.457143, 0.03125 } };
	this->td_zombie_[2] = { t, 312, 275, 110, 128, { 0.454545, 0.039062 } };
	this->td_zombie_[3] = { t, 478, 147, 129, 128, { 0.410853, 0.039062 } };
	this->td_zombie_[4] = { t, 893, 431, 118, 128, { 0.313559, 0.039062 } };
	this->td_zombie_[5] = { t, 786, 9, 134, 128, { 0.477612, 0.039062 } };
	this->td_zombie_[6] = { t, 893, 293, 121, 128, { 0.495868, 0.03125 } };
	this->td_zombie_[7] = { t, 639, 9, 137, 128, { 0.343066, 0.03125 } };
	this->td_zombie_[8] = { t, 177, 275, 125, 128, { 0.448, 0.039062 } };
	return t;
};
