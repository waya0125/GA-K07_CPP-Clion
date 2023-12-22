//
// Created by waya on 2023/07/14.
// Updated on 2023/10/20.
//

#ifndef UTILS_CLASS
#define UTILS_CLASS

#pragma once
#include <cmath>
#include <iostream>
#include <random>
#include "Vector.h"
using namespace std;

// ##### �����_���Ȓl��ԋp����֐� #####
// �Q�l���� : http://vivi.dyndns.org/tech/cpp/random.html
// ����     : min, max
// �߂�l   : min�ȏ�max�ȉ��̃����_���Ȓl
// ����     : random�֐����g�p���邽�߁Arandom���C���N���[�h����K�v������
[[maybe_unused]]
int random(int min, int max) {
    random_device rnd;     // �񌈒�I�ȗ���������𐶐�
    mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
    uniform_int_distribution<> rand100(min, max); // �͈͎w��̗���
    // �����_���Ȓl��ԋp����
    return rand100(mt);
}

// ##### �x�N�g���̉��Z #####
// �Q�l���� : �Ȃ�
// ����     : V1, V2
// �߂�l   : ���Z����Vector2
// ����     : �Ȃ�
[[maybe_unused]]
Vector2 addVector(const Vector2& V1, const Vector2& V2) {
    // ���Z�����x�N�g�����v�Z
    Vector2 Result = {
            V1.x + V2.x,
            V1.y + V2.y
    };
    return Result;
}

// ##### �x�N�g���̌��Z #####
// �Q�l���� : �Ȃ�
// ����     : V1, V2
// �߂�l   : ���Z����Vector2
// ����     : �Ȃ�
[[maybe_unused]]
Vector2 subVector(const Vector2& V1, const Vector2& V2) {
    // ���Z�����x�N�g�����v�Z
    Vector2 Result = {
            V1.x - V2.x,
            V1.y - V2.y
    };
    return Result;
}

// ##### �x�N�g���̏�Z #####
// �Q�l���� : �Ȃ�
// ����     : V1, V2
// �߂�l   : ��Z�����x�N�g��
// ����     : �Ȃ�
[[maybe_unused]]
Vector2 mulVector(const Vector2& V1, const Vector2& V2) {
    // ��Z�����x�N�g�����v�Z
    Vector2 Result = {
            V1.x * V2.x,
            V1.y * V2.y
    };
    return Result;
}

// ##### �x�N�g���̏��Z #####
// �Q�l���� : �Ȃ�
// ����     : V1, V2
// �߂�l   : ���Z�����x�N�g��
// ����     : �Ȃ�
[[maybe_unused]]
Vector2 divVector(const Vector2& V1, const Vector2& V2) {
    // ���Z�����x�N�g�����v�Z
    Vector2 Result = {
            V1.x / V2.x,
            V1.y / V2.y
    };
    return Result;
}

// ##### �O�όv�Z�֐� #####
// �Q�l���� : �Q�[���A���S���Y�� Z07 7�y�[�W�ڎ���
// ����     : x1, y1, x2, y2
// �߂�l   : �O�όv�Z���ꂽfloat�l
// ����     : �Ȃ�
[[maybe_unused]]
float crossProduct(const Vector2& V1, const Vector2& V2) {
    return V1.x * V2.y - V1.y * V2.x;
}

// ##### ���όv�Z�֐� #####
// �Q�l���� : �Q�[���A���S���Y�� Z07 12�y�[�W�ڎ���
// ����     : Vector2 V1, Vector2 V2
// �߂�l   : ���όv�Z���ꂽfloat�l
// ����     : �Ȃ�
[[maybe_unused]]
float dotProduct(const Vector2& V1, const Vector2& V2) {
    return V1.x * V2.x + V1.y * V2.y;
}

// ##### ���΃x�N�^�[�v�Z�֐� #####
// �Q�l���� : �Q�[���A���S���Y�� Z07 7�y�[�W�ڎ���
// ����     : x1, y1, x2, y2
// �߂�l   : ���΃x�N�^�[
// ����     : �Ȃ�
[[maybe_unused]]
Vector2 relative(const Vector2& V1, const Vector2& V2) {
    // 2�̉~�̒��S���W�̍������v�Z�i���΃x�N�g���j
    return {V1.x - V1.y, V2.x - V2.y}; // �ړI�̒n�_ - ���݂̒n�_
}

// ##### 2�̉~�̒��S���W(Vector)�̋������v�Z����֐� #####
// �Q�l���� : https://www.geisya.or.jp/~mwm48961/math/distance1j.htm
// ����     : Vector2 V1, Vector2 V2
// �߂�l   : 2�̉~�̒��S���W�̋���
// ����     : sqrt�֐����g�p���邽�߁Amath.h or cmath���C���N���[�h����K�v������
[[maybe_unused]]
float getVectorDistance(const Vector2& V1, const Vector2& V2) {
    // 2�̉~�̒��S���W�̍������v�Z�i���΃x�N�g���j
    Vector2 diff = subVector(V1, V2); // �ړI�̒n�_ - ���݂̒n�_
    // 2�̉~�̒��S���W�̋������v�Z
    return sqrtf(powf(diff.x, 2) + powf(diff.y, 2));
}

// ##### 2�̉~�̒��S���W(Vector)�̋������v�Z���ĕ����ɂ���ĕԂ��l��ς���֐� #####
// �Q�l���� : �Ȃ�
// ����     : Vector2 V1, Vector2 V2
// �߂�l   : 2�̃|�C���g�Ԃ̋���(float)
// ����     : sqrt�֐����g�p���邽�߁Amath.h or cmath���C���N���[�h����K�v������
[[maybe_unused]]
float getVectorDistanceSign(const Vector2& V1, const Vector2& V2) {
    // 2�̉~�̒��S���W�̍������v�Z�i���΃x�N�g���j
    Vector2 diff = subVector(V1, V2); // �ړI�̒n�_ - ���݂̒n�_
    // 2�̉~�̒��S���W�̋������v�Z
    return sqrtf(powf(diff.x, 2) + powf(diff.y, 2)) * (diff.x < 0.0F ? 1.0F : -1.0F);
}

// ##### ���΃x�N�^�[�̒������v�Z����֐� #####
// �Q�l���� : �Ȃ�
// ����     : Vector2 V1
// �߂�l   : ���΃x�N�^�[�̒���
// ����     : sqrt�֐����g�p���邽�߁Amath.h or cmath���C���N���[�h����K�v������
[[maybe_unused]]
float getVectorLength(const Vector2& V1) {
    // ���΃x�N�g���̌v�Z
    Vector2 relativeVector = mulVector(V1, V1);
    // ���΃x�N�g���̒������v�Z
    return sqrtf(relativeVector.x + relativeVector.y);
}

// ##### ���΃x�N�^�[���K�� #####
// �Q�l���� : �Q�[���A���S���Y�� Z07 7�y�[�W�ڎ���
// ����     : V1
// �߂�l   : ���Ή����ꂽVector2
// ����     : �Ȃ�
[[maybe_unused]]
static Vector2 normalized(const Vector2& V1) {
    // ���K���������΃x�N�g�����v�Z
    Vector2 Result = {
            V1.x / sqrtf((V1.x * V1.x) + (V1.y * V1.y)),
            V1.y / sqrtf((V1.x * V1.x) + (V1.y * V1.y))
    };
    return Result;
}

// ##### ���ςƊO�ς��v�Z���ē_�Ɠ_�̊Ԃ�������true��Ԃ� #####
// �Q�l���� : �Ȃ�
// ����     : Vector2 ���݂̍��W, Vector2 �n�_A, Vector2 �n�_B
// �߂�l   : �_�Ɠ_�̊Ԃ�������true�A�����łȂ��ꍇ��false
// ����     : �Ȃ�
[[maybe_unused]]
bool pointBetween(const Vector2& posV, const Vector2& V1, const Vector2& V2) {
    // �_�Ɠ_�̊Ԃ��ǂ����𔻒肷��
    // 2�̉~�̒��S���W�̍������v�Z�i���΃x�N�g���j
    // �ړI�̒n�_ - ���݂̒n�_
    Vector2 Vs1 = subVector(V2, V1);     // �����̃x�N�g��
    Vector2 Vs2 = subVector(posV, V1);   // �_�Ɛ����̎n�_�̃x�N�g��
    Vector2 Vs3 = subVector(V1, V2);     // �����̃x�N�g��
    Vector2 Vs4 = subVector(posV, V2);   // �_�Ɛ����̏I�_�̃x�N�g��
    float   Vd1 = dotProduct(Vs1, Vs2);  // ����
    float   Vd2 = dotProduct(Vs3, Vs4);  // ����
    Vector2 Vn  = normalized(Vs1);       // ���K��
    float   Vc  = crossProduct(Vn, Vs2); // �O��

    // �_�Ɠ_�̊ԂɐN�����Ă�����true��Ԃ�
    if (Vd1 > 0 && Vd2 > 0 && Vc >= 1) {
        return true;
    }

    return false;
}

// ���菈�������ʉ�
[[maybe_unused]]
Vector2 findDistance(const Vector2& V1, const Vector2& V2) {
    // ���΃x�N�g���𐳋K��
    Vector2 relativeVector = {
        (V1.x - V2.x) / getVectorDistance (V1, V2),
        (V1.y - V2.y) / getVectorDistance (V1, V2)
    };

    // �������́i���́j�̐i�s�����x�N�g����ԋp
    return { relativeVector.y, -relativeVector.x };
}

// �����蔻��
[[maybe_unused]]
bool hitCheck(const Vector2& V1, const float& V1R, const Vector2& V2, const float& V2R) {
    // 2�̉~�̒��S���W�̋������v�Z
    float distance = getVectorDistance(V1, V2);
    // 2�̉~�̔��a�̘a���v�Z
    float sumR = V1R + V2R;
    // 2�̉~�̒��S���W�̋�����2�̉~�̔��a�̘a��菬����������
    if (distance < sumR) {
        // �������Ă���
        return true;
    }
    // �������Ă��Ȃ�
    return false;
}

#endif //UTILS_CLASS