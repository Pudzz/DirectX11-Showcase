#pragma once
#include "DX11.h"

struct Vertex
{
	Vertex() :pos(), texCoord(), normal(), tangent(), weight(0.0f), ID(-1) {}
	Vertex(float x, float y, float z,
		float u, float v,
		float nx, float ny, float nz,
		float tx, float ty, float tz)
		: pos(x, y, z), texCoord(u, v), normal(nx, ny, nz), tangent(tz, ty, tz), weight(0.0f), ID(-1) { }

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 texCoord;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 tangent;

	// Weight for each vertex
	// Is used for weighting the vertices to a skeleton
	float weight;

	// Index for which bone in a skeleton this vertex should be weighted by
	int ID;
};


class Model
{
public:
	Model();
	~Model();

	void InitializeCube(ID3D11Device* device, LPCWSTR textureFilename);

	void Shutdown();
	void Render(ID3D11DeviceContext* context);
	int GetVertexCount();
	int GetIndexCount();


	void SetWorldMatrix(DirectX::XMMATRIX world) { this->world = world; }
	DirectX::XMMATRIX GetWorldMatrix() { return this->world; }

private:
	void ShutdownBuffers();
	//void ReleaseTexture();
	void CreateCube(ID3D11Device* device);
	//bool CreateQuad(ID3D11Device*);

private:
	HRESULT hr;
	ID3D11Buffer* vertexBuffer, * indexBuffer;
	int vertexCount, indexCount;
	DirectX::XMMATRIX world;
};