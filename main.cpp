#include <vector>
#include "container.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Providing name and rootfs path is mandatory!!" << std::endl;
    }
    std::string a = "a";
    std::string b = "b";
    std::pair<std::string, std::string> p(a, b);
    MappedPaths mp(1);
    mp.push_back(p);
    Container container(argv[1], argv[2], mp);

    std::string c = "/bin/bash";
    std::string d = "-c";
    std::string e = "ls";
    std::vector<std::string> cmd = {c, d, e};
    container.start(cmd);
    return EXIT_SUCCESS;
}