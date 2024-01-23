#include "ShaderManager.h"
namespace ShaderManager {
	vector<string> shaderKinds_;//���̐���D3D::InitShader����

}

vector<D3D11_INPUT_ELEMENT_DESC> ShaderManager::SetVertexInputLayout()
{
	vector<D3D11_INPUT_ELEMENT_DESC> layout = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�ʒu
	};
	return layout;
}

Cull_Setting ShaderManager::AddRasterizer(D3D11_CULL_MODE _cull, D3D11_FILL_MODE _fill, bool _clockWise)
{
	Cull_Setting cs{};

	cs.cullSetting = _cull;
	cs.fillSetting = _fill;
	cs.clockWise = _clockWise;
	return cs;
}

bool ShaderManager::AddShader(string _shaderName)
{
	shaderKinds_.push_back(_shaderName);
	return true;
}
