// 以下の行がないとコンパイルが通りません
#pragma comment(linker, "/subsystem:windows")

//## 環境に応じて設定
using namespace std; // std名前空間を使用
#include "DxLib.h"   // DXライブラリ
#include "Vector.h"  // ベクトルクラス
#include "Circle.h"  // 円クラス
#include "Utils.h"   // ユーティリティ (秘伝のタレ)
#include "Option.h"  // その他設定

// プログラムの最初はWinMainで始める
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### 初期設定 #####//
    ChangeWindowMode(TRUE); // ウィンドウモード設定
    SetGraphMode(WIDTH, HEIGHT, 32); // 画面サイズ設定
    SetWaitVSyncFlag(TRUE); // 垂直同期を有効にする

    // DXライブラリ初期化処理
    if(DxLib_Init() == -1) {
        return -1; // エラーが起きたら直ちに終了
    }

    // 円の初期化
    // 0: 原点, 1: 始点, 2: 末端
    CircleManager circle[3] {
        CircleManager(Vector2(WIDTH / 2.0F, HEIGHT / 2.0F), 15),
        CircleManager(Vector2(WIDTH / 2.0F + 70.0F,  HEIGHT / 2.0F + 30.0F), 15),
        CircleManager(Vector2(WIDTH / 2.0F + 100.0F, HEIGHT / 2.0F + 45.0F), 15)
    };

    //##### メインループ（描画処理） #####//
    while(ProcessMessage() == 0) {
        ClearDrawScreen(); // 画面の更新

        printfDx("Hello World!\n\n");

        //#### 移動処理 ####//
        // Up or W
        if(CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W)) {
            circle[2].posNow.y -= 5;
        }
        // Left or A
        if(CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A)) {
            circle[2].posNow.x -= 5;
        }
        // Down or S
        if(CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S)) {
            circle[2].posNow.y += 5;
        }
        // Right or D
        if(CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) {
            circle[2].posNow.x += 5;
        }

        //#### 逆運動学 ####//
        // 末端の補正と関節計算に使用する変数の取得
        Vector2 startAndEndArmPos = {
            circle[2].posNow.x - circle[0].posNow.x,
            circle[2].posNow.y - circle[0].posNow.y
        };
        float startAndEndLength = sqrtf(
            startAndEndArmPos.x * startAndEndArmPos.x + startAndEndArmPos.y * startAndEndArmPos.y
        );
        Vector2 startAndEndLengthVector = {
            startAndEndArmPos.x / startAndEndLength,
            startAndEndArmPos.y / startAndEndLength
        };

        //#### 余弦定理 ####//
        // 余弦定理を使用して関節位置を計算する
        if (startAndEndLength > firstArmLength + secondArmLength) {
            // 末端の座標を補正する
            circle[2].posNow.x = circle[0].posNow.x + startAndEndLengthVector.x * (firstArmLength + secondArmLength);
            circle[2].posNow.y = circle[0].posNow.y + startAndEndLengthVector.y * (firstArmLength + secondArmLength);
        };

        // 第一関節の角度を計算する
        float cosA = (firstArmLength * firstArmLength + startAndEndLength * startAndEndLength - secondArmLength * secondArmLength) / (2.0F * firstArmLength * startAndEndLength);
        //circle 0から1に対する単位ベクターを取得
        Vector2 startAndEndArmPosUnit = {
            startAndEndArmPos.x / startAndEndLength,
            startAndEndArmPos.y / startAndEndLength
        };
        // CosAとSinAを用いてV1をV2に回転
        Vector2 jointPos = {
            circle[0].posNow.x + firstArmLength * (startAndEndArmPosUnit.x * cosA - startAndEndArmPosUnit.y * sqrtf(1.0F - cosA * cosA)),
            circle[0].posNow.y + firstArmLength * (startAndEndArmPosUnit.x * sqrtf(1.0F - cosA * cosA) + startAndEndArmPosUnit.y * cosA)
        };
        // circle 0の座標にV2'を足してV3を作る
        circle[1].posNow = jointPos;

        // もし末端が中心に行ったら、第一関節の位置を補正する
        if (startAndEndLength < firstArmLength - secondArmLength) {
            circle[1].posNow.x = circle[0].posNow.x + startAndEndLengthVector.x * firstArmLength;
            circle[1].posNow.y = circle[0].posNow.y + startAndEndLengthVector.y * firstArmLength;
        }
        // また同様に端っこに行ったら、第一関節の位置を補正する
        if (startAndEndLength > firstArmLength + secondArmLength) {
            circle[1].posNow.x = circle[0].posNow.x + startAndEndLengthVector.x * firstArmLength;
            circle[1].posNow.y = circle[0].posNow.y + startAndEndLengthVector.y * firstArmLength;
        }

        //#### 描画処理 ####//
        // 円の描画
        for(int i = 0; i < COUNTOF(circle); i++) {
            DrawCircle(circle[i].posNow.x, circle[i].posNow.y, circle[i].radial, white, TRUE);

            // ついでにその数値も描画しておく
            printfDx("circle[%d].posNow.x = %.2f\n", i, circle[i].posNow.x);
            printfDx("circle[%d].posNow.y = %.2f\n", i, circle[i].posNow.y);
        }
        // 始点と中間点の座標間を結ぶ線を描画
        DrawLine(circle[0].posNow.x, circle[0].posNow.y, circle[1].posNow.x, circle[1].posNow.y, white);
        // 中間点と終点の座標間を結ぶ線を描画
        DrawLine(circle[1].posNow.x, circle[1].posNow.y, circle[2].posNow.x, circle[2].posNow.y, white);

        // 画面の更新（必須）
        ScreenFlip(); // 画面を反転させる処理
        clsDx();      // デバッグログ画面をクリアする処理
    }

    DxLib_End(); // DX Libraryの使用を終了する処理
    return 0;    // ソフトを正常終了
}
