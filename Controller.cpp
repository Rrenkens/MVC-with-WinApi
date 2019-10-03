// Laba.cpp : Определяет точку входа для приложения.
//

#include "Controller.h"
#include "framework.h"
#include "Stack.h"
#include "Resource.h"
#include "Visitor.h"
#include "View.h"


#define MAX_LOADSTRING 100
const size_t MAX_SIZE = 20;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Controller::InitDialog(HINSTANCE hInstance, int nCmdShow) {
	HWND hDlg = CreateDialog(hInstance,
		MAKEINTRESOURCE(IDD_DIALOG1),
		NULL,
		Controller::MessageParser);
	if (hDlg == NULL) {
		throw std::runtime_error("Window Creation Failed!");
	}

	ShowWindow(hDlg, nCmdShow);
	UpdateWindow(hDlg);
}

WPARAM Controller::Start(){
	MSG message;
	while (GetMessage(&message, NULL, 0, 0) > 0) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}

INT_PTR CALLBACK Controller::MessageParser(
	HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_INITDIALOG: {
		SetFocus(GetDlgItem(hDlg, IDC_Enter));
		break;
	}
	case WM_COMMAND: {
		bool need_repaint = false;
		switch (LOWORD(wParam)) {
		case IDC_PushStack: {
			ProcessPush(hDlg, Model::GetStack());
			need_repaint = true;
			break;
		}
		case IDC_PushCrowd: {
			ProcessPush(hDlg, Model::GetCrowd());
			need_repaint = true;
			break;
		}
		case IDC_PopCrowd: {
			ProcessPop(hDlg, Model::GetCrowd());
			need_repaint = true;
			break;
		}
		case IDC_PopStack: {
			ProcessPop(hDlg, Model::GetStack());
			need_repaint = true;
			break;
		}
		case IDC_CreateRandomElement: {
			ProcessGetRandomElement(hDlg);
			need_repaint = true;
			break;
		}
		case IDC_Delete: {
			ProcessDelete(hDlg);
			need_repaint = true;
			break;
		}
		case WM_CLOSE: {
			DestroyWindow(hDlg);
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		}
		if (need_repaint) {
			InvalidateRect(hDlg, NULL, TRUE);
			UpdateWindow(hDlg);
			SetFocus(GetDlgItem(hDlg, IDC_Enter));
		}
		break;
	}
	
	case WM_PAINT: {
		View::Update(hDlg);
		break;
	}
	}

	return (INT_PTR)FALSE;
}

void Controller::ProcessPush(
	HWND hDlg, Container<Model::Type_>* container) {
	TCHAR stream[MAX_SIZE];
	GetWindowText(GetDlgItem(hDlg, IDC_Enter), stream, MAX_SIZE);
	if (stream[0] == '\0') {
		return;
	}
	SetWindowText(GetDlgItem(hDlg, IDC_Enter), "");

	std::istringstream in(stream);
	Model::Type_ value;
	getline(in, value);
	container->Accept(&PushVisitor<Model::Type_>(value));
}

void Controller::ProcessPop(
	HWND hDlg, Container<Model::Type_>* container) {
	container->Accept(&PopVisitor<Model::Type_>());
}

void Controller::ProcessGetRandomElement(HWND hDlg) {
	SetWindowText(GetDlgItem(hDlg, IDC_Enter),
		Constants::GetRandomPeople().c_str());
}

void Controller::ProcessDelete(HWND hDLg) {
	while (Model::GetCrowdSize() > 0) {
		ProcessPop(hDLg, Model::GetCrowd());
	}
	while (Model::GetStackSize() > 0) {
		ProcessPop(hDLg, Model::GetStack());
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	Controller::InitDialog(hInstance, nCmdShow);
	return Controller::Start();
}