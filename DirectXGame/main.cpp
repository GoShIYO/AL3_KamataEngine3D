#include <Windows.h>
#include"KamataEngine.h"
#include"GameScene.h"
#include<memory>

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize(L"LE2A_20_リ_ショウコウ_AL3");

	// DirectXCommonのインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	// GameSceneのインスタンスの作成
	std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
    gameScene->Initialize();

    while (true) {
		if (KamataEngine::Update()) {
			break;
		}
		
		//ゲームシーンの更新
		gameScene->Update();
		
		//描画開始
		dxCommon->PreDraw();
		
		//ゲームシーンの描画
		gameScene->Draw();
		
		//描画終了
		dxCommon->PostDraw();
    	
	}
	KamataEngine::Finalize();

	return 0;
}
