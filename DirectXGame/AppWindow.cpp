#include "AppWindow.h"
#include "Windows.h"

//Data structure to store vertex coordinates
struct vec3 {
	float x, y, z;
};

//Data structure to store vertices
struct vertex {
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

//Data Structure for constant buffer
_declspec(align(16))
struct constant {
	unsigned int m_time;
};


void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//Create list of vertices of triangle
	vertex list[] = {
		//Position            New Position          Color   New Color
		{-0.5f, -0.5f, 0.0f, -0.15f, -0.35f, 0.2f,  1,0,0,   1,0,1},
		{-0.5f, 0.5f, 0.0f,  -0.72f, 0.45f, -0.1f,  0,1,1,   1,1,0},
		{0.5f, -0.5f, 0.0f,  0.5f, 0.13f, 0.52f,    0,0,1,   1,0,0},
		{0.5f, 0.5f, 0.0f,   0.0f, -0.14f, -0.72f,  1,1,0,   0,1,1},
		
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_time = 0;
	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.3, 0.3, 0.3, 1);
	
	//Set viewport of render target in which we are drawing
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	//create new struct of type constant to store time elapsed
	constant cc;
	cc.m_time = ::GetTickCount(); //Time elapsed since system started
	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	//bind constant buffer to graphics pipeline for each shader type
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//Use vertex shader
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	//Use Pixel shader
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}
