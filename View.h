#pragma once

#include "Container.h"
#include "Controller.h"
#include "Model.h"
#include "Stack.h"

class View {
public:
	static void Update(HWND);
private:
	static void PrintData(HWND, HDC, Container<Model::Type_>*, RECT, bool);
};