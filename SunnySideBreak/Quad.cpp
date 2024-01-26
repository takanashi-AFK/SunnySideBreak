#include "Quad.h"

Quad::Quad():pVertexBuffer_(nullptr)
{
}

Quad::~Quad()
{
}

void Quad::Initialize()
{
	D3D* pD3D = &D3D::GetInstance();
	// 頂点情報
	XMVECTOR vertices[] =
	{
		XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),	// 四角形の頂点（左上）
		XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	// 四角形の頂点（右上）
		XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	// 四角形の頂点（右下）
		XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	// 四角形の頂点（左下）		
	};
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	pD3D->GetDevice()->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	//インデックス情報
	int index[] = { 0,2,3, 0,1,2 };

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	pD3D->GetDevice()->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	pD3D->GetDevice()->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
}

void Quad::Draw()
{
	D3D* pD3D = &D3D::GetInstance();
	Camera* pCam = &Camera::GetInstance();

	//コンスタントバッファに渡す情報
	CONSTANT_BUFFER cb;
	D3D11_MAPPED_SUBRESOURCE pdata;
///////////////////ここ直してくれ///////////////////////
	cb.matWVP = XMMatrixTranspose(pCam->GetViewMatrix() * pCam->GetProjectionMatrix());
///////////////////////////////////////////////////////
	pD3D->GetContext()->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	pD3D->GetContext()->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(XMVECTOR);
	UINT offset = 0;
	pD3D->GetContext()->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	pD3D->GetContext()->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	pD3D->GetContext()->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	pD3D->GetContext()->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用
	pD3D->GetContext()->DrawIndexed(6, 0, 0);
}

void Quad::Release()
{
}
