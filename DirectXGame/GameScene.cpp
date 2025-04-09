#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	delete model_;
	delete player_;
}

void GameScene::Initialize() {
	// DirectXCommonインスタンス取得
	dxCommon_ = DirectXCommon::GetInstance();
	// Inputインスタンス取得
	input_ = Input::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png"); 
	//3Dモデルの生成
	model_ = Model::Create();
	//カメラの初期化
    camera_.Initialize();

	player_ = new Player();
	player_->Initialize(model_, textureHandle_, &camera_);
}

void GameScene::Update() {
#ifdef _DEBUG
	//ImGuiDebug();
#endif // _DEBUG
	
	player_->Update();
}

void GameScene::Draw() {
	DrawModel();
}

void GameScene::DrawModel() {
	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon_->GetCommandList());

	player_->Draw();

	// 3Dモデル描画後処理
	Model::PostDraw();
}
	
#ifdef _DEBUG
void GameScene::ImGuiDebug() { 

	ImGui::ShowDemoWindow();

}
#endif