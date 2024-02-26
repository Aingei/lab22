#include <windows.h>
#include <stdio.h>

char input1[100];
char input2[100];
char t[100];
int getstat1, getstat2;
double x, y, sum;
HWND textfield, button, textbox1, textbox2, buttonplus, buttonminus, buttonmultiply, buttondivide;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	HWND textfield, Text_Box1, Text_Box2, Button;

	switch (Message)
	{

	case WM_CREATE:
	{
		textfield = CreateWindow("STATIC", "    Please input two numbers",
								 WS_VISIBLE | WS_CHILD | WS_BORDER,
								 20, 20, 200, 25,
								 hwnd, NULL, NULL, NULL);
		textbox1 = CreateWindow("EDIT", "",
								WS_BORDER | WS_CHILD | WS_VISIBLE,
								40, 50, 160, 25,
								hwnd, NULL, NULL, NULL);
		textbox2 = CreateWindow("EDIT", "",
								WS_BORDER | WS_CHILD | WS_VISIBLE,
								40, 80, 160, 25,
								hwnd, NULL, NULL, NULL);
		buttonplus = CreateWindow("button", "+",
								  WS_BORDER | WS_CHILD | WS_VISIBLE,
								  65, 110, 25, 25,
								  hwnd, (HMENU)1, NULL, NULL);
		buttonminus = CreateWindow("button", "-",
								   WS_BORDER | WS_CHILD | WS_VISIBLE,
								   95, 110, 25, 25,
								   hwnd, (HMENU)2, NULL, NULL);
		buttonmultiply = CreateWindow("button", "*",
									  WS_BORDER | WS_CHILD | WS_VISIBLE,
									  125, 110, 25, 25,
									  hwnd, (HMENU)3, NULL, NULL);
		buttondivide = CreateWindow("button", "/",
									WS_BORDER | WS_CHILD | WS_VISIBLE,
									155, 110, 25, 25,
									hwnd, (HMENU)4, NULL, NULL);
		break;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 1:
			getstat1 = 0;
			getstat1 = GetWindowText(textbox1, &input1[0], 100);
			x = atof(input1);
			getstat2 = 0;
			getstat2 = GetWindowText(textbox2, &input2[0], 100);
			y = atof(input2);
			sum = x + y;
			sprintf(t, "%f", sum);
			::MessageBox(hwnd, t, "Result", MB_OK);
			break;
		case 2:
			getstat1 = 0;
			getstat1 = GetWindowText(textbox1, &input1[0], 100);
			x = atof(input1);
			getstat2 = 0;
			getstat2 = GetWindowText(textbox2, &input2[0], 100);
			y = atof(input2);
			sum = x - y;
			sprintf(t, "%f", sum);
			::MessageBox(hwnd, t, "Result", MB_OK);
			break;
		case 3:
			getstat1 = 0;
			getstat1 = GetWindowText(textbox1, &input1[0], 100);
			x = atof(input1);
			getstat2 = 0;
			getstat2 = GetWindowText(textbox2, &input2[0], 100);
			y = atof(input2);
			sum = x * y;
			sprintf(t, "%f", sum);
			::MessageBox(hwnd, t, "Result", MB_OK);
			break;
		case 4:
			getstat1 = 0;
			getstat1 = GetWindowText(textbox1, &input1[0], 100);
			x = atof(input1);
			getstat2 = 0;
			getstat2 = GetWindowText(textbox2, &input2[0], 100);
			y = atof(input2);
			sum = x / y;
			sprintf(t, "%f", sum);
			::MessageBox(hwnd, t, "Result", MB_OK);
			break;
		}
		break;
	}
	/* Upon destruction, tell the main thread to stop */
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	/* All other messages (a lot of them) are processed using default procedures */
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd;	   /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg;	   /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc; /* This is where we will send messages to */
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(234, 21, 137));
	wc.lpszClassName = "WindowClass";
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	  /* Load a standard icon */
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "My Calculator", WS_VISIBLE | WS_SYSMENU,
						  CW_USEDEFAULT, /* x */
						  CW_USEDEFAULT, /* y */
						  250,			 /* width */
						  200,			 /* height */
						  NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{							/* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg);	/* Send it to WndProc */
	}
	return msg.wParam;
}
