#pragma once
//�C���N���[�h
#include <Windows.h>
#include "../Window/Window.h"
#include"../Window/WindowManager.h"
#include"../Draw/D3D.h"
#include"../Other/Global.h"
#include "Quad.h"
#include "ImGuiManager.h"
#include "Camera.h"

class Application
{
public:
	Application() ;

	/// <summary>
	/// �e��A�v���P�[�V�����̏���������
	/// ���݂�D3D�AWindow�̏������ƕ\�����s��
	/// </summary>
	/// <param name="_hInstance">WinMain��args�Ŏ����hInstance</param>
	/// <param name="_nCmdShow">Winmain��args�Ŏ����_nCmdShow</param>
	/// <returns></returns>
	bool Initialize(HINSTANCE _hInstance, int _nCmdShow);

	/// <summary>
	/// ���b�Z�[�W���[�v���s���֐�
	/// </summary>
	void Run();

	/// <summary>
	/// �e�A�v���P�[�V�����̉������
	/// </summary>
	void Release();

	/// <summary>
	/// �V���O���g���p�̃C���X�^���X���擾����֐�
	/// </summary>
	/// <returns>Application�̃C���X�^���X</returns>
	static Application& GetInstance();
private:
	
};

