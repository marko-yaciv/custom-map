#include "Application.h"

int main()
{
    Application app;
    try
    {
        app.initWindow();
        app.start();
    }
    catch (const char* ex)
    {
        std::cout << ex << std::endl;
        return -1;
    }
    return 0;
}
