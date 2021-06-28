#include "arguments.h"

#include <stdexcept>

using namespace std;

Arguments parseArguments(int argc, char** argv) {
    Arguments parsed;

    bool parseTimeout = false;
    bool parseTitle = false;
    for (int i=1; i<argc; ++i) {
        string argument = string(argv[i]);

        if (argument == MINIMIZE_AT_START_LONG || argument == MINIMIZE_AT_START_SHORT) {
            parsed.minimizeAtStart = true;
        } else if (argument == VERTICAL_LONG || argument == VERTICAL_SHORT) {
            parsed.vertical = true;
        } else if (argument == HORIZONTAL_LONG || argument == HORIZONTAL_SHORT) {
            parsed.vertical = false;
        } else if (argument == ALWAYS_ON_TOP_LONG || argument == ALWAYS_ON_TOP_SHORT) {
            parsed.alwaysOnTop = true;
        } else if (argument == TIMEOUT_SECONDS_LONG || argument == TIMEOUT_SECONDS_SHORT) {
            parseTimeout = true;
        } else if (argument == WINDOW_TITLE_LONG || argument == WINDOW_TITLE_SHORT) {
            parseTitle = true;
        } else if (parseTimeout) {
            parseTimeout = false;
            try {
                parsed.timeoutSeconds = stoi(argument);
            } catch (invalid_argument const&) {}
        } else if (parseTitle) {
            parseTitle = false;
            parsed.windowTitle = argument;
        }
    }

    return parsed;
}
