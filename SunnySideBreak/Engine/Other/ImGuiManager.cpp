#include "ImGuiManager.h"

ImGuiManager& ImGuiManager::GetInstance()
{
    static ImGuiManager instance;
    return instance;

}

bool ImGuiManager::Initialize(HWND _hWnd)
{
    D3D* pD3D = &D3D::GetInstance();
    IMGUI_CHECKVERSION();	//ImGui�����o�[�W�������m�F
    ImGui::CreateContext();	//�R���e�L�X�g���쐬
    ImGuiIO& io = ImGui::GetIO();	//�K�v�ȃf�[�^���擾
    ImGui::StyleColorsDark();	//�J���[�����ɐݒ�

    //ImGui��������
    if (!ImGui_ImplWin32_Init(_hWnd))return false;
    if (!ImGui_ImplDX11_Init(pD3D->GetDevice(), pD3D->GetContext()))return false;
    return true;
}
bool ImGuiManager::Feature()
{
    ImGui::Begin("Hello, world!");//ImGui�̏������J�n
    {
        //���̒��ɂ������������L�q
        //�`�悳���{�^������������...
        if (ImGui::Button("button")) {
            PostQuitMessage(0);	//�v���O�����I��
        }
    }
    
    return true;
}

bool ImGuiManager::UpDate()
{
    //ImGui�̍X�V����
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    return true;
}

bool ImGuiManager::Draw()
{
    ImGui::End();//ImGui�̏������I��
    //ImGui�̕`�揈��
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return true;
}


bool ImGuiManager::Release()
{
    //ImGui�̊J������
    ImGui_ImplDX11_Shutdown();
    ImGui::DestroyContext();

    return true;
}
