#ifndef GA_04_CPP_CLION_CIRCLE_H
#define GA_04_CPP_CLION_CIRCLE_H

//## ���ɉ����Đݒ�
#pragma once
#include "DxLib.h"
#include "Vector.h"

/// <summary>##### �~�N���X #####</summary><br>
/// # �ł��邱��<br>
/// <param>Circle(Vector2 pos, float r)</param>: Circle�\���̂̃C���X�^���X���쐬<br>
/// <param>ONTOUCHCOLOR</param>: �|�[���Ƀv���C���[���G��Ă���ꍇ�̃T�[�N���̐F<br>
/// <param>UNTOUCHCOLOR</param>: �|�[���Ƀv���C���[���G��Ă��Ȃ��ꍇ�̃T�[�N���̐F<br>
/// <param>PI</param>: �~����<br>
/// <param>float radial</param>: ���a��ݒ�E�擾<br>
/// <param>float Distance</param>: �ړ�������ݒ�E�擾<br>
/// <param>float angularVelocity</param>: �p���x��ݒ�E�擾<br>
/// <param>float cumulativeAngle</param>: �ݐϊp�x��ݒ�E�擾<br>
/// <param>Vector2 posNow(float x, float y)</param>: ���W��ݒ�E�擾<br>
/// <param>Vector2 posPrevious(float x, float y)</param>: �O��̍��W��ݒ�E�擾<br>
/// <param>Vector2 posVectorEnd(float x, float y)</param>: �x�N�g���̏I�_���W��ݒ�E�擾<br>
/// �Q�l���� : �Ȃ�<br>
/// ����     : �Ȃ�
class CircleManager {
public:
    //bool hit = false;           // �ڐG���Ă��邩�ǂ���
    float radial;               // ���a
    float distance = 0;         // �ړ�����
    float angularVelocity = 0;  // �p���x
    float cumulativeAngle = 0;  // �ݐϊp�x
    Vector2 posNow;             // ���W
    Vector2 posPrevious;        // �O��̍��W
    Vector2 posVectorEnd;       // �x�N�g���̏I�_���W

    // �R���X�g���N�^�ƃf�X�g���N�^
    CircleManager(Vector2 pos, float r) : posNow(pos), radial(r) {
        cout << "calling constructor." << endl;
    }
    ~CircleManager() {
        cout << "calling destructor." << endl;
    }

    [[nodiscard]]
    inline float R() const {
        return radial;
    }
    inline float R(float d) {
        return this->radial = d;
    }

    void Rolling();
};

void CircleManager::Rolling() {}

#endif //GA_04_CPP_CLION_CIRCLE_H