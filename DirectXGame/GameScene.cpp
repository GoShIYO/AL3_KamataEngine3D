#include "GameScene.h"
#include"MathFunc.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	delete modelPlayer_;
	delete modelBlock_;
	delete player_;
	delete debugCamera_;
	delete skydome_;
	delete modelSkydome_;
	for (auto& worldTransformLine : worldTransformBlocks_) {
		for (auto worldTransformBlock : worldTransformLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {
	// DirectXCommonインスタンス取得
	dxCommon_ = DirectXCommon::GetInstance();
	// Inputインスタンス取得
	input_ = Input::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("block.png"); 

	//カメラの初期化
    camera_.Initialize();
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth,WinApp::kWindowHeight);
	
	InitializePlayer();
	InitializeBlock();
	InitializeSkydome();
}

void GameScene::Update() {
#ifdef _DEBUG
	//ImGuiDebug();
#endif // _DEBUG

	// プレイヤーの更新
	player_->Update();
	// ブロックの更新
	UpdateBlock();


	// カメラの更新
	UpdateCamera();

}

void GameScene::Draw() {
	DrawModel();
}

void GameScene::DrawModel() {
	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon_->GetCommandList());

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	for (auto& worldTransformLine : worldTransformBlocks_) {
		for (auto worldTransformBlock : worldTransformLine) {
			if (!worldTransformBlock) {
				continue;
			}
			modelBlock_->Draw(*worldTransformBlock, camera_, textureHandle_);
		}
	}
	player_->Draw();
	skydome_->Draw();
	// 3Dモデル描画後処理
	Model::PostDraw();
}
	
#ifdef _DEBUG
void GameScene::InitializePlayer() {
	// プレイヤーモデルの生成
	modelPlayer_ = Model::CreateFromOBJ("player",true);
	// プレイヤーの生成
	player_ = new Player();
	player_->Initialize(modelPlayer_,&camera_);

}
void GameScene::InitializeBlock() {
	modelBlock_ = Model::Create();
	// 要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	// ブロック1個分の横幅
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;
	const float kWallWidth = kBlockWidth * kNumBlockHorizontal;
	const float kWallHeight = kBlockHeight * kNumBlockVirtical;
	// 要素数を変更する
	worldTransformBlocks_.resize(kNumBlockVirtical);

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}
	// ブロックの生成
	for (uint32_t y = 0; y < kNumBlockVirtical; ++y) {
		for (uint32_t x = 0; x < kNumBlockHorizontal; ++x) {
			if ((x % 2 ) == (y % 2)) {
				worldTransformBlocks_[y][x] = new WorldTransform();
				worldTransformBlocks_[y][x]->Initialize();
				// ブロックを中央に調整する
				worldTransformBlocks_[y][x]->translation_.x = kBlockWidth * x - kWallWidth / 2.0f;
				worldTransformBlocks_[y][x]->translation_.y = kBlockHeight * y - kWallHeight / 2.0f;
			} else {
				worldTransformBlocks_[y][x] = nullptr;
			}
		}
	}
}

void GameScene::InitializeSkydome() { 
	// モデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true); 
	// 天球を作成
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, &camera_);
}

void GameScene::UpdateBlock() {
	// ブロックの更新
	for (auto& worldTransformLine : worldTransformBlocks_) {
		for (auto worldTransformBlock : worldTransformLine) {
			if (!worldTransformBlock) {
				continue;
			}
			worldTransformBlock->matWorld_ = 
				MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
				
			worldTransformBlock->TransferMatrix();
		}
	}

}
void GameScene::UpdateCamera() {
#ifdef _DEBUG
	// デバッグカメラの有効/無効
	if (input_->TriggerKey(DIK_Z)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif // _DEBUG
	// カメラの更新
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else {
		camera_.UpdateMatrix();
	}
}
void GameScene::ImGuiDebug() { 

	ImGui::ShowDemoWindow();

}
#endif