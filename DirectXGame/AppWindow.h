#pragma once
#include "Window.h"
#include "GraphicsEngine.h"

class AppWindow: public Window
{
public:
	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
};

