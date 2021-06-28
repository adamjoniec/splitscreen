#include <list>
#include <windows.h>

std::list<HWND> findWindows(std::string partOfTitle);

void adjustWindows(std::list<HWND> windows, bool alwaysOnTop);

void sleepSecond();
