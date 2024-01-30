#pragma once
#include <string>

/// <summary>
/// ���̃t�@�C����include���邾���ŁA�e���ň�������global�ϐ��𗘗p�ł���悤�ɂȂ�B
/// �e�ϐ��̎���`�A�����cpp�ōs���Ă���B
/// ��X��.ini�t�@�C���I�ȃA���ŊO������ύX�\�ɂ������Ǝv���Ă���B
/// </summary>
extern float g_WindowWidth;
extern float g_WindowHeight;
extern int g_FrameRate;
extern const char* g_GameTitle;

#define SAFE_DELETE(target) if(target!= nullptr){delete target;target = nullptr;};
#define SAFE_RELEASE(target) if(target!= nullptr){target->Release();target = nullptr;};