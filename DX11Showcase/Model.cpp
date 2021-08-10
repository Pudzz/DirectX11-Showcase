#include "Model.h"
Model::Model()
{
}

Model::~Model()
{
}

void Model::InitializeCube(ID3D11Device* device, LPCWSTR textureFilename)
{
    CreateCube(device);

    //result = LoadTexture(device, textureFilename);
    //if (!result)
    //   return false;

    //return true;
}

void Model::Shutdown()
{
}

void Model::Render(ID3D11DeviceContext* context)
{
    unsigned int stride;
    unsigned int offset;

    stride = sizeof(Vertex);
    offset = 0;

    context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

int Model::GetVertexCount()
{
    return vertexCount;
}

int Model::GetIndexCount()
{
    return indexCount;
}

void Model::ShutdownBuffers()
{
}

void Model::CreateCube(ID3D11Device* device)
{
    // Create own vertexbuffer and indices
    Vertex cube[] = {

        // Front Face
        Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f),
        Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f,-1.0f,  1.0f, -1.0f, -1.0f, 1.0f, -1.0f),
        Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f, 1.0f, 1.0f, -1.0f),
        Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f),

        // Back Face
        Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f),
        Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f),
        Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f,-1.0f,  1.0f, 1.0f, -1.0f, 1.0f, 1.0f),

        // Top Face
        Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f),
        Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f,-1.0f, 1.0f,  1.0f, -1.0f, 1.0f, 1.0f),
        Vertex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f),

        // Bottom Face
        Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f),
        Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f),
        Vertex(1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, -1.0f,  1.0f, 1.0f, -1.0f, 1.0f),
        Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,-1.0f, -1.0f,  1.0f, -1.0f, -1.0f, 1.0f),

        // Left Face
        Vertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,-1.0f, -1.0f,  1.0f, -1.0f, -1.0f, 1.0f),
        Vertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f,-1.0f,  1.0f,  1.0f, -1.0f, 1.0f, 1.0f),
        Vertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f,-1.0f,  1.0f, -1.0f, -1.0f, 1.0f, -1.0f),
        Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f),

        // Right Face
        Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f),
        Vertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  1.0f, -1.0f, 1.0f, 1.0f, -1.0f),
        Vertex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  1.0f, 1.0f, -1.0f, 1.0f),
    };

    DWORD cubeIndices[]{
        // Front Face
        0,  1,  2,
        0,  2,  3,

        // Back Face
        4,  5,  6,
        4,  6,  7,

        // Top Face
        8,  9, 10,
        8, 10, 11,

        // Bottom Face
        12, 13, 14,
        12, 14, 15,

        // Left Face
        16, 17, 18,
        16, 18, 19,

        // Right Face
        20, 21, 22,
        20, 22, 23
    };

    indexCount = ARRAYSIZE(cubeIndices);
    vertexCount = ARRAYSIZE(cube);

    // Vertexbuffer description for cube
    D3D11_BUFFER_DESC bufferDesc;
    ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.CPUAccessFlags = 0u;
    bufferDesc.MiscFlags = 0u;
    bufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
    bufferDesc.StructureByteStride = sizeof(Vertex);

    D3D11_SUBRESOURCE_DATA resourceData;
    ZeroMemory(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));
    resourceData.pSysMem = cube;

    // Create vertexbuffer for cube
    hr = device->CreateBuffer(&bufferDesc, &resourceData, &vertexBuffer);
    if (FAILED(hr)) {
        MessageBox(0, L"Failed to 'CreateBuffer' for VertexBuffer_Cube.", L"Graphics scene Initialization Message", MB_ICONERROR);
    }

    // Indexbuffer description for cube
    ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.CPUAccessFlags = 0u;
    bufferDesc.MiscFlags = 0u;
    bufferDesc.ByteWidth = sizeof(DWORD) * indexCount;
    bufferDesc.StructureByteStride = sizeof(DWORD);

    ZeroMemory(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));
    resourceData.pSysMem = cubeIndices;

    // Create indexbuffer for cube
    hr = device->CreateBuffer(&bufferDesc, &resourceData, &indexBuffer);
    if (FAILED(hr)) {
        MessageBox(0, L"Failed to 'CreateBuffer' for IndexBuffer_Cube.", L"Graphics scene Initialization Message", MB_ICONERROR);
    }
}
