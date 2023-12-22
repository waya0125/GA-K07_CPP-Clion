//
// Created by waya on 2023/06/10.
// Updated on 2023/10/20.
//
#ifndef VECTOR_H
#define VECTOR_H

//## ���ɉ����Đݒ�
#pragma once
using namespace std;
#include <cmath>
#include <iostream>

/// <summary>##### 2�����x�N�g���N���X #####</summary><br>
/// # �ł��邱��<br>
/// <param>Vector2(float x, float y)</param>: Vector2�\���̂̃C���X�^���X���쐬<br>
/// <param>float x, y: Vector2�\���̂̃C���X�^���X��x, y���W��ݒ�E�擾<br>
/// �Q�l���� : �Ȃ�<br>
/// ����     : �Ȃ�
class Vector2 {
public:
    // x, y�̒l��ێ�����ϐ�
    float x, y;

    // �R���X�g���N�^ & �f�X�g���N�^
    // �Ȃ��R���X�g���N�^��explicit������ƈÖق̌^�ϊ����ł��Ȃ��Ȃ邽�ߌ���͂��Ȃ��B
    Vector2(float x = 0, float y = 0) : x(x), y(y) {
        cout << "calling constructor." << endl;
    }
    ~Vector2() {
        cout << "calling destructor." << endl;
    }

    // x, y�̒l��ݒ肷��֐�
    [[nodiscard]]
    inline float X() const {
        return x;
    }
    inline float X(float d) {
        return this->x = d;
    }
    [[nodiscard]]
    inline float Y() const {
        return y;
    }
    inline float Y(float d) {
        return this->y = d;
    }
};

#endif //VECTOR_H