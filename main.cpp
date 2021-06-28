#include <iostream>

#include "arguments.h"
#include "windowmanager.h"

using namespace std;

void printConfiguration(Arguments arguments) {
    cout << "\n " << MINIMIZE_AT_START_LONG << ", " << MINIMIZE_AT_START_SHORT << " (" <<
        (arguments.minimizeAtStart ? "true" : "false") << ")";
    /*cout << "\n " << VERTICAL_LONG << ", " << VERTICAL_SHORT << " (" <<
        (arguments.vertical ? "true" : "false") << ")";
    cout << "\n " << HORIZONTAL_LONG << ", " << HORIZONTAL_SHORT << " (" <<
        (!arguments.vertical ? "true" : "false") << ")";*/
    cout << "\n " << ALWAYS_ON_TOP_LONG << ", " << ALWAYS_ON_TOP_SHORT << " (" <<
        (arguments.alwaysOnTop ? "true" : "false") << ")";
    cout << "\n " << TIMEOUT_SECONDS_LONG << ", " << TIMEOUT_SECONDS_SHORT << " seconds ("
        << arguments.timeoutSeconds << ")";
    cout << "\n " << WINDOW_TITLE_LONG << ", " << WINDOW_TITLE_SHORT << " title (" << arguments.windowTitle << ")";
    cout << "\n";
}

int main(int argc, char** argv)
{
    SetWindowText(GetConsoleWindow(), "splitscreen");

    cout << "Split screen / couch co-op window adjuster. By default works with Minecraft (just launch "
        << " up to four instances of Minecraft and run this app for magic to happen). "
        << "For any other game/program use " << WINDOW_TITLE_LONG << ", " << WINDOW_TITLE_SHORT << " argument i.e."
        << "\n > splitscreen.exe " << WINDOW_TITLE_LONG << " GameTitle"
        << "\n\nUsing arguments (with defaults):";

    Arguments arguments = parseArguments(argc, argv);

    printConfiguration(arguments);

    if (arguments.minimizeAtStart) {
        ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
    }

    cout << "\nWaiting for " << arguments.windowTitle << " window(s) ...";

    unsigned long foundWindowsCount = 0;
    for (int seconds = 0; seconds < arguments.timeoutSeconds; ++seconds) {

        const list<HWND> foundWindows = findWindows(arguments.windowTitle);
        const bool noNewWindow = (foundWindowsCount == foundWindows.size()) || foundWindows.size() == 0;
        const bool exitAfterClosing = (foundWindowsCount > 0 && foundWindows.size() == 0);

        foundWindowsCount = foundWindows.size();

        if (exitAfterClosing) {
                cout << "\n\nAll " << arguments.windowTitle << "(s) windows/instances were closed. Closing splitscreen!";
            exit(0);
        }

        if (noNewWindow) {
            cout << '.';
            sleepSecond();
            continue;
        }

        cout << "\n\n   : found " << foundWindowsCount << " " << arguments.windowTitle << " window"
            << (foundWindowsCount > 1 ? "s" : "") << ", adjusting ... ";

        adjustWindows(foundWindows, arguments.alwaysOnTop);

        cout << "done \n";
        cout << "\n ... waiting for more " << arguments.windowTitle << " windows ...";

        sleepSecond();
    }

    cout << "\n\nTimeout! Closing splitscreen!\n";

    return 0;
}
