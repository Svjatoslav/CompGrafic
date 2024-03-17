#pragma once

#include <d3d11.h>
#include <dxgi.h>
#include <directxmath.h>
#include <string>
#include "camera.h"
#include "input.h"
#include "utils.h"
#include "cubeMap.h"
#include "texture.h"


struct Vertex {
	float x, y, z;
	float u, v;
};

struct WorldMatrixBuffer {
	XMMATRIX mWorldMatrix;
};

struct SceneMatrixBuffer {
	XMMATRIX mViewProjectionMatrix;
};

class Render {
private:
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pBackBufferRTV = nullptr;
	ID3D11Buffer* m_pIndexBuffer = nullptr;
	ID3D11Buffer* m_pVertexBuffer = nullptr;

	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;

	ID3D11InputLayout* m_pInputLayout = nullptr;

	ID3D11Buffer* m_pWorldMatrixBuffer = nullptr;
	ID3D11Buffer* m_pSceneMatrixBuffer = nullptr;
	ID3D11RasterizerState* m_pRasterizerState = nullptr;
	ID3D11SamplerState* m_pSampler = nullptr;

	UINT m_width = 1280;
	UINT m_height = 720;

	Camera* m_pCamera = nullptr;
	Input* m_pInput = nullptr;

	CubeMap* m_pCubeMap = nullptr;
	std::vector<Texture> m_textureArray;

	float m_forwardSpeed = 0.0f;
	float m_backwardSpeed = 0.0f;
	float m_leftSpeed = 0.0f;
	float m_rightSpeed = 0.0f;
	float m_frameMove = 0.001f;
	XMFLOAT3 m_cubePos = XMFLOAT3(0.0f, 0.0f, 0.0f);

	HRESULT setupBackBuffer();
	HRESULT initScene();
	void inputMovement();
	void MoveForward(bool keydown);
	void MoveBackward(bool keydown);
	void MoveLeft(bool keydown);
	void MoveRight(bool keydown);

public:
	bool render();
	bool deviceInit(HINSTANCE hinst, HWND hWnd, Camera* pCamera, Input* pInput);
	bool getState();
	void deviceCleanup();
	bool winResize(UINT width, UINT height);
};