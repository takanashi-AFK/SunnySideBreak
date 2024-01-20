#pragma once
#include<map>
#include"Window.h"
#include"D3D.h"
#include<string>
/// <summary>
/// window�𕡐������ł���悤�ɂ��邽�߂ɊǗ�����N���X�B
/// main��Instance���쐬���AaddInstance���邱�ƂŃE�B���h�E��ǉ����邱�Ƃ��ł���B
/// </summary>
class WindowManager
{
public:

	//window�N���X�̃C���X�^���X���i�[����map(�E�B���h�E���A�C���X�^���X)
	std::map<std::string,Window*> windowInstanceContainer;

	//�V���O���g���ɂ��邽��(WindowManager��1�ȏア��Ȃ�����)GetInstance()
	static WindowManager& GetInstance();

	//map�̒��ɓ����Ă��邷�ׂĂ�window��Initialize���ĂԊ֐� InitializeAll()�K��
	bool InitializeAllWindow(HINSTANCE _hInstance,int _nCmdShow);

	//Map�̒��ɓ����Ă��邷�ׂĂ�window��Release���ĂԊ֐�	  ReleaseAll()�I��
	bool ReleaseAllWindow();

	//Map�ɃE�B���h�E���ƃC���X�^���X���i�[���邽�߂̊֐�	AddInstance()�I��
	bool AddInstance(std::string _windowName,Window* _windowInstance);

};

