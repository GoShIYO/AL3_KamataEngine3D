#pragma once
#include"KamataEngine.h"

using namespace KamataEngine;
/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:
	Player() {};
	~Player() = default;
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	/// <param name="camera">カメラ</param>
	void Initialize(Model* model,Camera* camera);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	WorldTransform worldTransform_;
	Model* modelPlayer_ = nullptr;
	Camera* camera_ = nullptr;
};
