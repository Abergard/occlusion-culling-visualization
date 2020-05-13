#include <iostream>

// #include "VlWin32Ocv.hpp"
#include "VlGlfwOcv.hpp"

ScreenSize getScreenSize(const int argc, const char* argv[])
try
{
    // if (argc != 3)
    //     return getFullScreenSize();

    return ScreenSize{std::stoi(argv[1]), std::stoi(argv[2])};
}
catch (const std::exception& ex)
{
    std::cerr << "Cannot read arguments: " << ex.what() << "\n";
    exit(-1);
}

int main(const int argc, const char* argv[])
{
    start(getScreenSize(argc, argv));
}
