#include "Skydome.h"

void Skydome::Initialize(Model* model, Camera* camera) {
	modelPlayer_ = model;
    camera_ = camera;
	worldTransform_.Initialize();
}

void Skydome::Update() {}

void Skydome::Draw() {
	modelPlayer_->Draw(worldTransform_, *camera_);
}
