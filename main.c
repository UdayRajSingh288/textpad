#include <windows.h>


static LRESULT CALLBACK window_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam){
	static HWND hedit;

	switch (umsg) {
		case WM_CREATE:
			hedit = CreateWindowEx(
				0,
				"EDIT",
				NULL,
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 
				0, 0, 0, 0,
				hwnd,
				NULL,
				((LPCREATESTRUCT)lparam)->hInstance,
				NULL
			);
			break;

		case WM_SIZE:
			if (hedit) {
				RECT rc_client;
				GetClientRect(hwnd, &rc_client);
				SetWindowPos(hedit, NULL, 0, 0, rc_client.right, rc_client.bottom, SWP_NOZORDER);
			}
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		default:
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	return 0;
}


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprev_instance, LPSTR lp_cmdline, int ncmd_show){
	const char CLASS_NAME[] = "Textpad";

	WNDCLASS wc = {};
	wc.lpfnWndProc = window_proc;
	wc.hInstance = hinstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(ICON));
	wc.hIconSm = LoadIcon(hinstance, MAKEINTRESOURCE(ICON));

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		"Textpad",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinstance,
		NULL
	);
	if (NULL == hwnd){
		return EXIT_SUCCESS;
	}
	ShowWindow(hwnd, ncmd_show);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return EXIT_SUCCESS;
}