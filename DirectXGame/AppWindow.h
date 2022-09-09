#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow: public Window
{
public:
	void updateQuadPosition();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;
	VertexShader* m_vs;
	PixelShader* m_ps;
private:
	//time point when previous frame was rendered
	float m_old_delta;
	//time point when current frame is rendered
	float m_new_delta;
	//differene between new_delta and old_delta
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
};

