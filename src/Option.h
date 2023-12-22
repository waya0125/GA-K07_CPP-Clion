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

//##### 変数設定 #####//
float firstArmLength = 100.0F; // 第一関節の長さ
float secondArmLength = 50.0F; // 第二関節の長さ

#endif //GA_04_CPP_CLION_OPTION_H
