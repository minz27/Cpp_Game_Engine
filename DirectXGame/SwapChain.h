#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	//Initialise the SwapCHain for a window
	bool init(HWND hwnd, UINT width, UINT height);

	bool present(bool vsync);

	//Release the swap chain
	bool release();
private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
private:
	friend class DeviceContext;
};

