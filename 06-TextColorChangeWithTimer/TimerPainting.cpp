#include <windows.h>
#define ID_TIMER1	101


//Global Function Declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global Variable Declaraions

//Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Local Variable Declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");

	//code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	//handle
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	//Create Window in memory
	hwnd = CreateWindow(szAppName,
		TEXT("SUG: FirstAutomaticPainting"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//Display Window
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//code
	//variable declaration
	
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	HBRUSH hbrush;
	static int iPaintFlag = 0;

	switch (iMsg)
	{
		case WM_CREATE:
			SetTimer(hwnd, ID_TIMER1, 1000, NULL);
			break;

		case WM_TIMER:
			KillTimer(hwnd, ID_TIMER1);
			iPaintFlag++;

			if(iPaintFlag >= 8)
				iPaintFlag = 0;

			SetTimer(hwnd, ID_TIMER1, 1000, NULL);
			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, ID_TIMER1, 1000, NULL);
			break;

		case WM_PAINT:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);

			if(iPaintFlag == 1)
				hbrush = CreateSolidBrush(RGB(255, 0, 0));
			
			else if(iPaintFlag == 2)
				hbrush = CreateSolidBrush(RGB(0, 255, 0));
			
			else if(iPaintFlag == 3)
				hbrush = CreateSolidBrush(RGB(0, 0, 255));
			
			else if(iPaintFlag == 4)
				hbrush = CreateSolidBrush(RGB(0, 255, 255));
			
			else if(iPaintFlag == 5)
				hbrush = CreateSolidBrush(RGB(255, 0, 255));
			
			else if(iPaintFlag == 6)
				hbrush = CreateSolidBrush(RGB(255, 255, 0));
			
			else if(iPaintFlag == 7)
				hbrush = CreateSolidBrush(RGB(0, 0, 0));

			else if(iPaintFlag == 8)
				hbrush = CreateSolidBrush(RGB(255, 255, 255));

			else
				hbrush = CreateSolidBrush(RGB(0, 0, 0));

			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);
			DeleteObject(hbrush);
			EndPaint(hwnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
