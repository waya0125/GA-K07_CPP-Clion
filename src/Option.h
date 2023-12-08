#ifndef GA_04_CPP_CLION_OPTION_H
#define GA_04_CPP_CLION_OPTION_H

#define WIDTH 1280
#define HEIGHT 720
#define PI 3.14F
#define COUNTOF(array) (sizeof(array) / sizeof(array[0])) // 配列の要素数をカウントする. Powered by KOBAYASHI Atsuki.

//##### 色の設定 #####//
unsigned int white = GetColor(255,255,255);
unsigned int red = GetColor(255,0,0);
unsigned int black = GetColor(0,0,0);

//##### OLD FUNCTION #####//
int circleState = 0;

//##### LATEST FUNCTION #####//
float firstArmLength = 100.0F;     // 第一関節の長さ
float secondArmLength = 50.0F;     // 第二関節の長さ
float startAndEndLength = firstArmLength + secondArmLength; // 始点と終点の長さは第一関節と第二関節の長さの合計
Vector2 startArmPos = {0, 0}; // 始点の座標
Vector2 endArmPos = {100, 0};   // 終点の座標

#endif //GA_04_CPP_CLION_OPTION_H