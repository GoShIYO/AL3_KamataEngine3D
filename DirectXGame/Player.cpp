#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, Camera* camera) {
	assert(model);
	worldTransform_.Initialize();
	modelPlayer_ = model;
	camera_ = camera;
}

void Player::Update() { 
	worldTransform_.TransferMatrix(); 
}

void Player::Draw() { 
	modelPlayer_->Draw(worldTransform_, *camera_); 
}