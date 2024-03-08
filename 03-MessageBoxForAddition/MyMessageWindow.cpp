#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;

	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
			TEXT("SUG:MyFirstWindow-MessageBox"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			hInstance,
			NULL);
	
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int num1, num2, num3;
	TCHAR str[255];
	
	switch(iMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_CREATE:
			num1 = 300;
			num2 = 200;
			num3 = num1 + num2;
			wsprintf(str, TEXT("Addition of %d and %d is %d"), num1, num2, num3);
			MessageBox(hwnd, str, TEXT("Addition"), MB_OK);
			break;		
		
		default:
			break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}
