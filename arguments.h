#include <string>

#define MINIMIZE_AT_START_LONG "--minimize-at-start"
#define MINIMIZE_AT_START_SHORT "-M"

#define VERTICAL_LONG "--vertical"
#define VERTICAL_SHORT "-V"

#define HORIZONTAL_LONG "--horizontal"
#define HORIZONTAL_SHORT "-H"

#define TIMEOUT_SECONDS_LONG "--timeout-seconds"
#define TIMEOUT_SECONDS_SHORT "-T"

#define WINDOW_TITLE_LONG "--window-title"
#define WINDOW_TITLE_SHORT "-W"

#define ALWAYS_ON_TOP_LONG "--always-on-top"
#define ALWAYS_ON_TOP_SHORT "-A"

struct Arguments {
    bool minimizeAtStart = false;
    bool vertical = true;
    int timeoutSeconds = 60;
    std::string windowTitle = "Minecraft";
    bool alwaysOnTop = false;
};

void printConfiguration(Arguments arguments);

Arguments parseArguments(int argc, char** argv);
