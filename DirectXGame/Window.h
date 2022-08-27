#pragma once
#include <Windows.h>

class Window {
public:
	//Initialise the Window
	bool init();
	bool broadcast();
	//Release the Window
	bool release();
	bool isRun();
	//EVENTS
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();
protected:
	HWND m_hwnd;
	bool m_is_run;
};