#include <vector>
#include "container.hpp"

int main(int argc, char* argv[]) {
    std::string a = "a";
    std::string b = "b";
    std::pair<std::string, std::string> p(a, b);
    MappedPaths mp(1);
    mp.push_back(p);
    Container container("wow", mp);

    std::string c = "/bin/bash";
    std::string d = "-c";
    std::string e = "echo Hallo!";
    std::vector<std::string> cmd = {c, d, e};
    container.start(cmd);
    return EXIT_SUCCESS;
}