#pragma once
#include<map>
#include"Window.h"
#include<string>
class WindowManager
{

public:
	//window�N���X�̃C���X�^���X���i�[����map(�E�B���h�E���A�C���X�^���X)
	std::map<std::string,Window*> windowInstanceContainer;

	//�V���O���g���ɂ��邽��(WindowManager��1�ȏア��Ȃ�����)GetInstance()
	static WindowManager& GetInstance();

	//map�̒��ɓ����Ă��邷�ׂĂ�window��Initialize���ĂԊ֐� InitializeAll()�K��
	bool InitializeAllWindow(HINSTANCE _hInstance,int _nCmdShow);

	//Map�̒��ɓ����Ă��邷�ׂĂ�window��Releace���ĂԊ֐�	  ReleaceAll()�I��
	bool ReleaseAllWindow();

	//Map�ɃE�B���h�E���ƃC���X�^���X���i�[���邽�߂̊֐�	AddInstance()�I��
	bool AddInstance(std::string _windowName,Window* _windowInstance);

	void MessageLoop();

};

