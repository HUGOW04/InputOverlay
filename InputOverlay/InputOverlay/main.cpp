#include <Windows.h>

#define buttonW 1
#define buttonA 2
#define buttonS 3
#define buttonD 4
#define buttonSpace 5
#define buttonLShift 6
#define buttonLCTRL 7
#define buttonQ 8
#define buttonE 9
#define buttonMouseL 10
#define buttonMouseR 11

HHOOK g_hook = NULL;
HHOOK g_mouseHook = NULL;
HWND hwnd = NULL;
HINSTANCE hInstance;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION && (wParam == WM_LBUTTONDOWN || wParam == WM_LBUTTONUP))
    {
        SendMessage(GetDlgItem(hwnd, buttonMouseL), BM_SETSTATE, wParam == WM_LBUTTONDOWN ? 1 : 0, 0);
    }
    else if (nCode == HC_ACTION && (wParam == WM_RBUTTONDOWN || wParam == WM_RBUTTONUP))
    {
        SendMessage(GetDlgItem(hwnd, buttonMouseR), BM_SETSTATE, wParam == WM_RBUTTONDOWN ? 1 : 0, 0);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_KEYUP))
	{
		KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

		switch (p->vkCode)
		{
		case 'W':
			SendMessage(GetDlgItem(hwnd, buttonW), BM_SETSTATE, wParam == WM_KEYDOWN ? 1 : 0, 0);
			break;
		case 'S':
			SendMessage(GetDlgItem(hwnd, buttonS), BM_SETSTATE, wParam == WM_KEYDOWN ? 1 : 0, 0);
			break;
		case 'A':
			SendMessage(GetDlgItem(hwnd, buttonA), BM_SETSTATE, wParam == WM_KEYDOWN ? 1 : 0, 0);
			break;
		case 'D':
			SendMessage(GetDlgItem(hwnd, buttonD), BM_SETSTATE, wParam == WM_KEYDOWN ? 1 : 0, 0);
			break;
        case 'Q':
            SendMessage(GetDlgItem(hwnd, buttonQ), BM_SETSTATE, wParam == WM_KEYDOWN ? 1 : 0, 0);
            break;
        case 'E':
            SendMessage(GetDlgItem(hwnd, buttonE), BM_SETSTATE, wParam == WM_KEYDOWN ? 1 : 0, 0);
            break;
        case VK_LSHIFT:
            SendMessage(GetDlgItem(hwnd, buttonLShift), BM_SETSTATE, wParam == WM_KEYDOWN ? 1 : 0, 0);
            break;
        case VK_LCONTROL:
            SendMessage(GetDlgItem(hwnd, buttonLCTRL), BM_SETSTATE, wParam == WM_KEYDOWN ? 1 : 0, 0);
            break;
		case VK_SPACE:
			SendMessage(GetDlgItem(hwnd, buttonSpace), BM_SETSTATE, wParam == WM_KEYDOWN ? 1 : 0, 0);
			break;
		}
	}
	return CallNextHookEx(g_hook, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // Register the window class
    const char* CLASS_NAME = "MyWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST,// Optional window styles
        CLASS_NAME,                     // Window class
        "",                             // Window text
        WS_POPUP,                       // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Position
        500, 500,                       // Size
        NULL,                           // Parent window    
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }



    // Install the hook
    g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInstance, 0);
    g_mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInstance, 0);
    if (g_hook == NULL)
    {
        return 0;
    }

    if (hwnd == NULL)
    {
        return 0;
    }

    // Set window to be always on top
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    // Show window
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);
    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static bool isButtonDown = false;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
    case WM_CLOSE:
        UnhookWindowsHookEx(g_hook);
        UnhookWindowsHookEx(g_mouseHook);
        DestroyWindow(hwnd);
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'W':
			SendMessage(GetDlgItem(hwnd, buttonW), BM_SETSTATE, 1, 0);
			break;
		case 'S':
			SendMessage(GetDlgItem(hwnd, buttonS), BM_SETSTATE, 1, 0);
			break;
		case 'A':
			SendMessage(GetDlgItem(hwnd, buttonA), BM_SETSTATE, 1, 0);
			break;
		case 'D':
			SendMessage(GetDlgItem(hwnd, buttonD), BM_SETSTATE, 1, 0);
			break;
        case 'Q':
            SendMessage(GetDlgItem(hwnd, buttonQ), BM_SETSTATE, 1, 0);
            break;
        case 'E':
            SendMessage(GetDlgItem(hwnd, buttonE), BM_SETSTATE, 1, 0);
            break;
        case VK_LSHIFT:
            SendMessage(GetDlgItem(hwnd, buttonLShift), BM_SETSTATE, 1, 0);
            break;
        case VK_LCONTROL:
            SendMessage(GetDlgItem(hwnd, buttonLCTRL), BM_SETSTATE, 1, 0);
            break;
		case VK_SPACE:
			SendMessage(GetDlgItem(hwnd, buttonSpace), BM_SETSTATE, 1, 0);
			break;
        case VK_LBUTTON:
            SendMessage(GetDlgItem(hwnd, buttonMouseL), BM_SETSTATE, 1, 0);
            break;
        case VK_RBUTTON:
            SendMessage(GetDlgItem(hwnd, buttonMouseR), BM_SETSTATE, 1, 0);
            break;
		}
        break;

	case WM_KEYUP:
		switch (wParam)
		{
		case 'W':
			SendMessage(GetDlgItem(hwnd, buttonW), BM_SETSTATE, 0, 0);
			break;
		case 'S':
			SendMessage(GetDlgItem(hwnd, buttonS), BM_SETSTATE, 0, 0);
			break;
		case 'A':
			SendMessage(GetDlgItem(hwnd, buttonA), BM_SETSTATE, 0, 0);
			break;
		case 'D':
			SendMessage(GetDlgItem(hwnd, buttonD), BM_SETSTATE, 0, 0);
			break;
        case 'Q':
            SendMessage(GetDlgItem(hwnd, buttonQ), BM_SETSTATE, 0, 0);
            break;
        case 'E':
            SendMessage(GetDlgItem(hwnd, buttonE), BM_SETSTATE, 0, 0);
            break;
        case VK_LSHIFT:
            SendMessage(GetDlgItem(hwnd, buttonLShift), BM_SETSTATE, 0, 0);
            break;
        case VK_LCONTROL:
            SendMessage(GetDlgItem(hwnd, buttonLCTRL), BM_SETSTATE, 0, 0);
            break;
		case VK_SPACE:
			SendMessage(GetDlgItem(hwnd, buttonSpace), BM_SETSTATE, 0, 0);
			break;
        case 0x01:
            SendMessage(GetDlgItem(hwnd, buttonMouseL), BM_SETSTATE, 0, 0);
            break;
        case VK_RBUTTON:
            SendMessage(GetDlgItem(hwnd, buttonMouseR), BM_SETSTATE, 0, 0);
            break;
		}
		break;
	case WM_CREATE:
        SetLayeredWindowAttributes(hwnd, 0, 128, LWA_COLORKEY | LWA_ALPHA); // set the window to be 50% transparent and use white as the transparent color
        // Create the buttons
        HWND btnW = CreateWindowEx(
            0,              // Optional window styles
            "BUTTON",       // Button class
            "W",            // Button text
            WS_CHILD | WS_VISIBLE,  // Button style
            150, 100, 50, 50, // Position and size
            hwnd,           // Parent window
            (HMENU)buttonW, // Button ID
            hInstance,      // Instance handle
            NULL            // No additional data
        );

        HWND btnS = CreateWindowEx(
           0,                               // Optional window styles
            "BUTTON",                       // Button class
            "S",                            // Button text
            WS_CHILD | WS_VISIBLE,          // Button style
            150, 150, 50, 50,               // Position and size
            hwnd,                           // Parent window
            (HMENU)buttonS,                           // Menu
            hInstance,                      // Instance handle
            NULL                            // Additional application data
        );

        HWND btnA = CreateWindowEx(
            0,                              // Optional window styles
            "BUTTON",                       // Button class
            "A",                            // Button text
            WS_CHILD | WS_VISIBLE,          // Button style
            100, 150, 50, 50,                // Position and size
            hwnd,                           // Parent window
            (HMENU)buttonA,                           // Menu
            hInstance,                      // Instance handle
            NULL                            // Additional application data
        );

        HWND btnD = CreateWindowEx(
            0,                              // Optional window styles
            "BUTTON",                       // Button class
            "D",                            // Button text
            WS_CHILD | WS_VISIBLE,          // Button style
            200, 150, 50, 50,               // Position and size
            hwnd,                           // Parent window
            (HMENU)buttonD,                           // Menu
            hInstance,                      // Instance handle
            NULL                            // Additional application data
        );
        HWND btnShift = CreateWindowEx(
            0,                              // Optional window styles
            "BUTTON",                       // Button class
            "Shift",                            // Button text
            WS_CHILD | WS_VISIBLE,          // Button style
            50, 100, 50, 75,               // Position and size
            hwnd,                           // Parent window
            (HMENU)buttonLShift,                           // Menu
            hInstance,                      // Instance handle
            NULL                            // Additional application data
        );
        HWND btnQ = CreateWindowEx(
            0,              // Optional window styles
            "BUTTON",       // Button class
            "Q",            // Button text
            WS_CHILD | WS_VISIBLE,  // Button style
            100, 100, 50, 50, // Position and size
            hwnd,           // Parent window
            (HMENU)buttonQ, // Button ID
            hInstance,      // Instance handle
            NULL            // No additional data
        );
        HWND btnE = CreateWindowEx(
            0,              // Optional window styles
            "BUTTON",       // Button class
            "E",            // Button text
            WS_CHILD | WS_VISIBLE,  // Button style
            200, 100, 50, 50, // Position and size
            hwnd,           // Parent window
            (HMENU)buttonE, // Button ID
            hInstance,      // Instance handle
            NULL            // No additional data
        );
        HWND btnLCTRL = CreateWindowEx(
            0,                              // Optional window styles
            "BUTTON",                       // Button class
            "CTRL",                            // Button text
            WS_CHILD | WS_VISIBLE,          // Button style
            50, 175, 50, 75,               // Position and size
            hwnd,                           // Parent window
            (HMENU)buttonLCTRL,                           // Menu
            hInstance,                      // Instance handle
            NULL                            // Additional application data
        );
        HWND btnSpace = CreateWindowEx(
            0,                              // Optional window styles
            "BUTTON",                       // Button class
            "SPACE",                        // Button text
            WS_CHILD | WS_VISIBLE,          // Button style
            100, 200, 150, 50,              // Position and size
            hwnd,                           // Parent window
            (HMENU)buttonSpace,                           // Menu
            hInstance,                      // Instance handle
            NULL                            // Additional application data
        );
        HWND baseMouse = CreateWindowEx(
            0,                              // Optional window styles
            "STATIC",                       // Button class
            "",                        // Button text
            WS_CHILD | WS_VISIBLE,          // Button style
            300, 165, 100, 85,              // Position and size
            hwnd,                           // Parent window
            NULL,                           // Menu
            hInstance,                      // Instance handle
            NULL                            // Additional application data
        );
        HWND mouseRbtn = CreateWindowEx(
            0,                              // Optional window styles
            "BUTTON",                       // Button class
            "",                        // Button text
            WS_CHILD | WS_VISIBLE,          // Button style
            350, 100, 48, 60,              // Position and size
            hwnd,                           // Parent window
            (HMENU)buttonMouseR,                           // Menu
            hInstance,                      // Instance handle
            NULL                            // Additional application data
        );
        HWND mouseLbtn = CreateWindowEx(
            0,                              // Optional window styles
            "BUTTON",                       // Button class
            "",                        // Button text
            WS_CHILD | WS_VISIBLE,          // Button style
            300, 100, 48, 60,              // Position and size
            hwnd,                           // Parent window
            (HMENU)buttonMouseL,                           // Menu
            hInstance,                      // Instance handle
            NULL                            // Additional application data
        );
        break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}