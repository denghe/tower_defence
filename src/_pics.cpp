#include "pch.h"
#include <xx_gamebase.h>
#include "_pics.h"

xx::Shared<xx::GLTexture> _pics::Load(std::string picFN_, bool generateMipmap_) {
	auto t = xx::GameBase::instance->LoadTexture(picFN_);
	if(generateMipmap_) t->TryGenerateMipmap();

	this->c64_light = { t, 930, 9, 64, 64, { 0.5, 0.5 } };
	this->c64_shadow = { t, 930, 83, 64, 32, { 0.5, 0.5 } };
	this->cursor_default = { t, 9, 541, 12, 19, { 0, 1 } };
	this->td_arrow = { t, 31, 531, 128, 32, { 0.84375, 0.53125 } };
	this->td_ring = { t, 9, 393, 128, 128, { 0.5, 0.5 } };
	this->explosion_1_[0] = { t, 930, 125, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[1] = { t, 972, 125, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[2] = { t, 9, 975, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[3] = { t, 51, 975, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[4] = { t, 93, 975, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[5] = { t, 135, 975, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[6] = { t, 9, 285, 32, 32, { 0.5, 0.5 } };
	this->explosion_1_[7] = { t, 9, 327, 32, 32, { 0.5, 0.5 } };
	this->td_grass_[0] = { t, 9, 9, 459, 256, { 0.5, 0.5 } };
	this->td_tower1_[0] = { t, 755, 147, 128, 187, { 0.5, 0.32 } };
	this->td_tower1_[1] = { t, 755, 344, 128, 187, { 0.5, 0.32 } };
	this->td_tower1_[2] = { t, 9, 581, 128, 187, { 0.5, 0.32 } };
	this->td_tower1_[3] = { t, 9, 778, 128, 187, { 0.5, 0.32 } };
	this->td_tree_[0] = { t, 617, 147, 128, 236, { 0.5, 0.084746 } };
	this->td_zombie_[0] = { t, 478, 9, 151, 128, { 0.390728, 0.039062 } };
	this->td_zombie_[1] = { t, 282, 275, 105, 128, { 0.457143, 0.03125 } };
	this->td_zombie_[2] = { t, 893, 443, 110, 128, { 0.454545, 0.039062 } };
	this->td_zombie_[3] = { t, 478, 147, 129, 128, { 0.410853, 0.039062 } };
	this->td_zombie_[4] = { t, 893, 305, 118, 128, { 0.313559, 0.039062 } };
	this->td_zombie_[5] = { t, 786, 9, 134, 128, { 0.477612, 0.039062 } };
	this->td_zombie_[6] = { t, 893, 167, 121, 128, { 0.495868, 0.03125 } };
	this->td_zombie_[7] = { t, 639, 9, 137, 128, { 0.343066, 0.03125 } };
	this->td_zombie_[8] = { t, 147, 393, 125, 128, { 0.448, 0.039062 } };
	return t;
};
