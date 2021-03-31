#include <iostream>
#include <Windows.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "[Fetch] Please enter $(OutDir) and path to misc as argv." << std::endl;
        return 1;
    }

    std::string outDir(argv[1]);
    std::string miscDir(argv[2]);
    std::cout << "[Fetch] Fetching build items.." << std::endl;

    CreateDirectoryA((outDir + "data").c_str(), NULL);
    std::cout << "Copy " << miscDir + "\\install.bat" << " to " << outDir + "install.bat" << std::endl;
    CopyFileA((miscDir + "\\install.bat").c_str(), (outDir + "install.bat").c_str(), TRUE);

    std::cout << "[Fetch] Finsihed." << std::endl;
    return 0;
}