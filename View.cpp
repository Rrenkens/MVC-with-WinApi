#include "view.h"
#include "Visitor.h"

void View::Update(HWND hDlg) {
	PAINTSTRUCT paint_struct;
	HDC hdc;
	hdc = BeginPaint(hDlg, &paint_struct);
	SetBkMode(hdc, TRANSPARENT);

	PrintData(hDlg, hdc, Model::GetStack(), { 10, 16, 160, 184}, true);
	PrintData(hDlg, hdc, Model::GetCrowd(), { 260, 16, 390, 184}, true);
	PrintData(hDlg, hdc, Model::GetStack(), { 203, 32, 240, 40}, false);
	PrintData(hDlg, hdc, Model::GetCrowd(), { 203, 73, 240, 83 }, false);

	EndPaint(hDlg, &paint_struct);
}

void View::PrintData(HWND hDlg, HDC hdc,
	Container<Model::Type_>* container, RECT rect, bool flag) {
	PrintVisitor<Model::Type_> visitor;
	container->Accept(&visitor);
	MapDialogRect(hDlg, &rect);
	if (flag) {
		DrawText(hdc,
			visitor.GetData().data(),
			visitor.GetDataSize(),
			&rect,
			DT_WORDBREAK);
	}
	else {
		size_t log_size = 1, size_ = visitor.GetSize();
		while (size_/=10) {
			log_size++;
		}
		DrawText(hdc,
			(std::to_string(visitor.GetSize()).c_str()),
			log_size,
			&rect,
			DT_WORDBREAK);
	}
}