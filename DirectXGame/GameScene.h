#pragma once
#include"KamataEngine.h"
#include"Player.h"
#include "Skydome.h"
#include<vector>

class GameScene {
public:	
    GameScene() = default;
    ~GameScene();
	// 初期化
	void Initialize();
	
	// 更新
	void Update();
	
	// 描画
    void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
    KamataEngine::Input* input_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// モデル
    KamataEngine::Model* modelPlayer_ = nullptr;
	// ブロックモデル
	KamataEngine::Model* modelBlock_ = nullptr;
	//ブロックのworldTransform	
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	// カメラ
	KamataEngine::Camera camera_;
	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	// プレイヤー
	Player* player_ = nullptr;
	// デバッグカメラフラグ
	bool isDebugCameraActive_ = false;
	// 天球
	Skydome* skydome_ = nullptr;
	// 天球モデル
	KamataEngine::Model* modelSkydome_ = nullptr;


private:
	// プレイヤー初期化
	void InitializePlayer();
	//ブロック初期化
	void InitializeBlock();
	//天球初期化
	void InitializeSkydome();
	
	// 更新処理//
	void UpdateBlock();

	void UpdateCamera();
#ifdef _DEBUG
	void ImGuiDebug();
#endif
private:
	// 描画処理//

	void DrawModel();
};
