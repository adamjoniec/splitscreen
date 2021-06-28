#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <list>

#include "arguments.h"

using namespace std;

list<HWND> findWindows(string partOfTitle) {
    list<HWND> found;

    for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT))
    {
        if (!IsWindowVisible(hwnd))
            continue;

        int length = GetWindowTextLength(hwnd);
        if (length == 0)
            continue;

        char* titleBuffer = new char[length+1];
        GetWindowText(hwnd, titleBuffer, length+1);

        string title = string(titleBuffer);

        if (title.find(partOfTitle) == std::string::npos)
            continue;

        found.push_back(hwnd);
    }
    return found;
}

SIZE getScreenResolution(HWND hwnd) {
    HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO info;
    info.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(monitor, &info);
    int monitor_width = info.rcMonitor.right - info.rcMonitor.left;
    int monitor_height = info.rcMonitor.bottom - info.rcMonitor.top;

    SIZE screenResolution;
    screenResolution.cx = monitor_width;
    screenResolution.cy = monitor_height;

    return screenResolution;
}

void sleepSecond() {
    Sleep(1000);
}

void setWindowPositionWithTwoWindows(HWND window, SIZE screenSize, int windowNumber) {
    SetWindowPos(window, IGNORE,
                     screenSize.cx / 2 * windowNumber,
                     0,
                     screenSize.cx / 2,
                     screenSize.cy,
                     SWP_NOZORDER|SWP_SHOWWINDOW);
}

void setWindowPositionWithFourWindows(HWND window, SIZE screenSize, int pos) {
    // 0 | 1
    // 2 | 3
    int width = screenSize.cx / 2,
        height = screenSize.cy / 2;

    int x = width * (pos < 2 ? pos : pos - 2),
        y = height * (pos < 2 ? 0 : 1);

    SetWindowPos(window, IGNORE, x, y, width, height, SWP_NOZORDER|SWP_SHOWWINDOW);
}

void setWindowPositionWithThreeWindows(HWND window, SIZE screenSize, int windowNumber) {
    switch (windowNumber) {
    case 0:
        setWindowPositionWithTwoWindows(window, screenSize, 0);
        break;
    case 1:
        setWindowPositionWithFourWindows(window, screenSize, 1);
        break;
    case 2:
        setWindowPositionWithFourWindows(window, screenSize, 3);
        break;
    }
}

void adjustWindows(list<HWND> windows, bool alwaysOnTop) {
    list<HWND>::iterator windowsIterator = windows.begin();
    SIZE screenSize = getScreenResolution(*windowsIterator);

    const int windowsCount = windows.size();// > 2 ? 2 : windows.size();

    for(int i=0; i<windowsCount; i++){
        HWND window = *windowsIterator;
        SetWindowLong(window, GWL_STYLE, WS_POPUP|WS_VISIBLE|WS_SYSMENU);
        SetWindowPos(window, alwaysOnTop ? HWND_TOPMOST : HWND_TOP, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
        SetForegroundWindow(window);

        cout << (i+1) << " ... ";

        switch (windowsCount) {
        case 1:
            SetWindowPos(window, IGNORE, 0, 0, screenSize.cx, screenSize.cy, SWP_NOZORDER|SWP_SHOWWINDOW);
            sleepSecond();
            break;
        case 2:
            setWindowPositionWithTwoWindows(window, screenSize, i);
            break;
        case 3:
            setWindowPositionWithThreeWindows(window, screenSize, i);
            break;
        case 4:
            setWindowPositionWithFourWindows(window, screenSize, i);
            break;
        }

        sleepSecond();
        ++windowsIterator;
    }
}
