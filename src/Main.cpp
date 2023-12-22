// �ȉ��̍s���Ȃ��ƃR���p�C�����ʂ�܂���
#pragma comment(linker, "/subsystem:windows")

//## ���ɉ����Đݒ�
using namespace std; // std���O��Ԃ��g�p
#include "DxLib.h"   // DX���C�u����
#include "Vector.h"  // �x�N�g���N���X
#include "Circle.h"  // �~�N���X
#include "Utils.h"   // ���[�e�B���e�B (��`�̃^��)
#include "Option.h"  // ���̑��ݒ�

// �v���O�����̍ŏ���WinMain�Ŏn�߂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### �����ݒ� #####//
    ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ݒ�
    SetGraphMode(WIDTH, HEIGHT, 32); // ��ʃT�C�Y�ݒ�
    SetWaitVSyncFlag(TRUE); // ����������L���ɂ���

    // DX���C�u��������������
    if(DxLib_Init() == -1) {
        return -1; // �G���[���N�����璼���ɏI��
    }

    // �~�̏�����
    // 0: ���_, 1: �n�_, 2: ���[
    CircleManager circle[3] {
        CircleManager(Vector2(WIDTH / 2.0F, HEIGHT / 2.0F), 15),
        CircleManager(Vector2(WIDTH / 2.0F + 70.0F,  HEIGHT / 2.0F + 30.0F), 15),
        CircleManager(Vector2(WIDTH / 2.0F + 100.0F, HEIGHT / 2.0F + 45.0F), 15)
    };

    //##### ���C�����[�v�i�`�揈���j #####//
    while(ProcessMessage() == 0) {
        ClearDrawScreen(); // ��ʂ̍X�V

        printfDx("Hello World!\n\n");

        //#### �ړ����� ####//
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

        //#### �t�^���w ####//
        // ���[�̕␳�Ɗ֐ߌv�Z�Ɏg�p����ϐ��̎擾
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

        //#### �]���藝 ####//
        // �]���藝���g�p���Ċ֐߈ʒu���v�Z����
        if (startAndEndLength > firstArmLength + secondArmLength) {
            // ���[�̍��W��␳����
            circle[2].posNow.x = circle[0].posNow.x + startAndEndLengthVector.x * (firstArmLength + secondArmLength);
            circle[2].posNow.y = circle[0].posNow.y + startAndEndLengthVector.y * (firstArmLength + secondArmLength);
        };

        // ���֐߂̊p�x���v�Z����
        float cosA = (firstArmLength * firstArmLength + startAndEndLength * startAndEndLength - secondArmLength * secondArmLength) / (2.0F * firstArmLength * startAndEndLength);
        //circle 0����1�ɑ΂���P�ʃx�N�^�[���擾
        Vector2 startAndEndArmPosUnit = {
            startAndEndArmPos.x / startAndEndLength,
            startAndEndArmPos.y / startAndEndLength
        };
        // CosA��SinA��p����V1��V2�ɉ�]
        Vector2 jointPos = {
            circle[0].posNow.x + firstArmLength * (startAndEndArmPosUnit.x * cosA - startAndEndArmPosUnit.y * sqrtf(1.0F - cosA * cosA)),
            circle[0].posNow.y + firstArmLength * (startAndEndArmPosUnit.x * sqrtf(1.0F - cosA * cosA) + startAndEndArmPosUnit.y * cosA)
        };
        // circle 0�̍��W��V2'�𑫂���V3�����
        circle[1].posNow = jointPos;

        // �������[�����S�ɍs������A���֐߂̈ʒu��␳����
        if (startAndEndLength < firstArmLength - secondArmLength) {
            circle[1].posNow.x = circle[0].posNow.x + startAndEndLengthVector.x * firstArmLength;
            circle[1].posNow.y = circle[0].posNow.y + startAndEndLengthVector.y * firstArmLength;
        }
        // �܂����l�ɒ[�����ɍs������A���֐߂̈ʒu��␳����
        if (startAndEndLength > firstArmLength + secondArmLength) {
            circle[1].posNow.x = circle[0].posNow.x + startAndEndLengthVector.x * firstArmLength;
            circle[1].posNow.y = circle[0].posNow.y + startAndEndLengthVector.y * firstArmLength;
        }

        //#### �`�揈�� ####//
        // �~�̕`��
        for(int i = 0; i < COUNTOF(circle); i++) {
            DrawCircle(circle[i].posNow.x, circle[i].posNow.y, circle[i].radial, white, TRUE);

            // ���łɂ��̐��l���`�悵�Ă���
            printfDx("circle[%d].posNow.x = %.2f\n", i, circle[i].posNow.x);
            printfDx("circle[%d].posNow.y = %.2f\n", i, circle[i].posNow.y);
        }
        // �n�_�ƒ��ԓ_�̍��W�Ԃ����Ԑ���`��
        DrawLine(circle[0].posNow.x, circle[0].posNow.y, circle[1].posNow.x, circle[1].posNow.y, white);
        // ���ԓ_�ƏI�_�̍��W�Ԃ����Ԑ���`��
        DrawLine(circle[1].posNow.x, circle[1].posNow.y, circle[2].posNow.x, circle[2].posNow.y, white);

        // ��ʂ̍X�V�i�K�{�j
        ScreenFlip(); // ��ʂ𔽓]�����鏈��
        clsDx();      // �f�o�b�O���O��ʂ��N���A���鏈��
    }

    DxLib_End(); // DX Library�̎g�p���I�����鏈��
    return 0;    // �\�t�g�𐳏�I��
}
