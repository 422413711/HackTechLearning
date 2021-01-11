#include "ScreenCapture.h"

BOOL ScreenCapture()
{
	//����
	HWND hDesktopWnd = NULL;
	HDC hdc = NULL;
	HDC mdc = NULL;
	int dwScreenWidth = 0;
	int dwScreenHeight = 0;
	HBITMAP bmp = NULL;
	HBITMAP holdbmp = NULL;
	//��ȡ���洰�ھ��
	hDesktopWnd = ::GetDesktopWindow();
	//��ȡ����DC
	hdc = ::GetDC(hDesktopWnd);
	//��������DC
	mdc = ::CreateCompatibleDC(hdc);
	//��ȡ��Ļ���
	dwScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	dwScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);
	//��������λͼ
	bmp = ::CreateCompatibleBitmap(hdc, dwScreenWidth, dwScreenHeight);
	//ѡ��λͼ
	holdbmp = (HBITMAP)::SelectObject(mdc, bmp);
	//���������ݻ��Ƶ�λͼ
	::BitBlt(mdc, 0, 0, dwScreenWidth, dwScreenHeight, hdc, 0, 0, SRCCOPY);

	//�������
	PaintMouse(mdc);

	//����ΪͼƬ
	SaveBmp(bmp);
	//�ͷ���Դ
	::DeleteObject(hDesktopWnd);
	::DeleteDC(hdc);
	::DeleteDC(mdc);
	::DeleteObject(bmp);
	::DeleteObject(holdbmp);
	return TRUE;
}

BOOL PaintMouse(HDC hdc)
{
	HDC bufdc = NULL;
	CURSORINFO cursorInfo = { 0 };
	ICONINFO iconInfo = { 0 };
	HBITMAP bmpOldMask = NULL;

	bufdc = ::CreateCompatibleDC(hdc);
	::RtlZeroMemory(&iconInfo, sizeof(iconInfo));
	cursorInfo.cbSize = sizeof(cursorInfo);
	// ��ȡ�����Ϣ
	::GetCursorInfo(&cursorInfo);
	// ��ȡ���ͼ����Ϣ
	::GetIconInfo(cursorInfo.hCursor, &iconInfo);
	// ���� �׵׺����(AND)
	bmpOldMask = (HBITMAP)::SelectObject(bufdc, iconInfo.hbmMask);
	::BitBlt(hdc, cursorInfo.ptScreenPos.x, cursorInfo.ptScreenPos.y, 20, 20,
		bufdc, 0, 0, SRCAND);
	// ���� �ڵײ�ɫ���(OR)
	::SelectObject(bufdc, iconInfo.hbmColor);
	::BitBlt(hdc, cursorInfo.ptScreenPos.x, cursorInfo.ptScreenPos.y, 20, 20,
		bufdc, 0, 0, SRCPAINT);

	// �ͷ���Դ
	::SelectObject(bufdc, bmpOldMask);
	::DeleteObject(iconInfo.hbmColor);
	::DeleteObject(iconInfo.hbmMask);
	::DeleteDC(bufdc);
	return TRUE;
}
