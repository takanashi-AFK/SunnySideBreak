#pragma once
#include <vector>
#include <map>
#include <string>
#include <d3d11.h>
using namespace std;
	struct Cull_Setting {
		D3D11_CULL_MODE cullSetting;
		D3D11_FILL_MODE fillSetting;
		bool clockWise;
	};

namespace ShaderManager
{
	vector<D3D11_INPUT_ELEMENT_DESC> SetVertexInputLayout();
	Cull_Setting AddRasterizer(D3D11_CULL_MODE _cull, D3D11_FILL_MODE _fill,bool _clockWise);
	bool AddShader(string _shaderName);
	extern vector<string> shaderKinds_;//‚±‚Ì”•ªD3D::InitShader‚ğ‰ñ‚·
};

