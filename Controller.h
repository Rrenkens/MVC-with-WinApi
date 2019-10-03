#pragma once

#include "container.h"
#include "model.h"
#include "resource.h"

#include <windows.h>

class Controller {
public:
	Controller() = default;
	~Controller() = default;
	static void InitDialog(HINSTANCE, int);
	static WPARAM Start();
	static INT_PTR CALLBACK MessageParser(HWND, UINT, WPARAM, LPARAM);

private:
	static void ProcessPush(HWND, Container<Model::Type_>*);
	static void ProcessPop(HWND, Container<Model::Type_>*);
	static void ProcessGetRandomElement(HWND);
	static void ProcessDelete(HWND);
};

