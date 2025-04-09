#pragma once
#include"KamataEngine.h"
#include"Player.h"

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
    KamataEngine::Model* model_ = nullptr;
	// カメラ
	KamataEngine::Camera camera_;
	// プレイヤー
	Player* player_ = nullptr;

private:
	// 更新処理//
#ifdef _DEBUG
	void ImGuiDebug();
#endif
private:
	// 描画処理//

	void DrawModel();
};
