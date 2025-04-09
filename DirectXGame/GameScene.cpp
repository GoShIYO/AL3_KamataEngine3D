#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {
	// DirectXCommonインスタンス取得
	dxCommon_ = DirectXCommon::GetInstance();
	// Audioインスタンス取得
	audio_ = Audio::GetInstance();
	// Inputインスタンス取得
	input_ = Input::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png"); 
	//スプライトインスタンスの生成
	sprite_ = Sprite::Create(textureHandle_, { 100, 50 });
	//3Dモデルの生成
	model_ = Model::Create();
	//WorldTransformの初期化
	worldTransform_.Initialize();
	//カメラの初期化
    camera_.Initialize();
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	//サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("fanfare.wav");
	//音声再生
	voiceHandle_ = audio_->PlayWave(soundDataHandle_,true);
	//ライン描画が参照するカメラを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetCamera(&debugCamera_->GetCamera());
	//軸表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());
}

void GameScene::Update() {
#ifdef _DEBUG
	ImGuiDebug();
#endif // _DEBUG
	debugCamera_->Update();
	
	//スプライト現在の座標を取得
	Vector2 position = sprite_->GetPosition();
	// 座標を{2,1}移動
	position.x += 2.0f;
	position.y += 1.0f;
	// 移動した座標をスプライトに反映
	sprite_->SetPosition(position);
	if (input_->TriggerKey(DIK_SPACE)) {
		if (audio_->IsPlaying(voiceHandle_)) {
			audio_->StopWave(voiceHandle_);		
		}
	}
}

void GameScene::Draw() { 
	DrawSprite(); 
	DrawModel();
	DrawDebugLine3D();
}

void GameScene::DrawSprite() {
	// スプライト描画前処理
	sprite_->PreDraw(dxCommon_->GetCommandList());

	sprite_->Draw();

	// スプライト描画後処理
	sprite_->PostDraw();
}

void GameScene::DrawModel() {
	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon_->GetCommandList());

	model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);
	
	// 3Dモデル描画後処理
	Model::PostDraw();
}

void GameScene::DrawDebugLine3D() { 
	const float gridSize = 1.0f;
	const float gridCount = 10.0f;

	float length = gridSize * gridCount;
	// X軸方向のグリッド線（Z固定）
	for (float x = -gridCount; x <= gridCount; x += 1.0f) {
		PrimitiveDrawer::GetInstance()->DrawLine3d({x, 0, -length}, {x, 0, length}, {1.0f, 0.0f, 0.0f, 1.0f});
	}
	// Z軸方向のグリッド線（X固定）
	for (float z = -gridCount; z <= gridCount; z += 1.0f) {
		PrimitiveDrawer::GetInstance()->DrawLine3d({-length, 0, z}, {length, 0, z}, {0.0f, 0.0f, 1.0f, 1.0f});
	}
}
	
#ifdef _DEBUG
void GameScene::ImGuiDebug() { 
    ImGui::Begin("Debug1");
	ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31); 
	//入力ボックス
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	//float3スライダー
	ImGui::DragFloat3("DragFloat3", inputFloat3, 0.0f,1.0f);
	ImGui::End();

	ImGui::ShowDemoWindow();
}
#endif