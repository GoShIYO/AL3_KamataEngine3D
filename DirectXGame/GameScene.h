#pragma once
#include"KamataEngine.h"


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
	KamataEngine::Audio* audio_ = nullptr;
    KamataEngine::Input* input_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	//モデル
    KamataEngine::Model* model_ = nullptr;
	//ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// カメラ
	KamataEngine::Camera camera_;
	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	// サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
    uint32_t voiceHandle_ = 0;

	float inputFloat3[3] = {0, 0, 0};

private:
	// 更新処理//
#ifdef _DEBUG
	void ImGuiDebug();
#endif
private:
	// 描画処理//

	void DrawSprite();
	void DrawModel();
	void DrawDebugLine3D();
};
