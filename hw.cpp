#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main() {
    std::cout << "Content:type: text/html" << std::endl << std::endl;
    std::cout << "<html><body>" << std::endl;
    std::cout << "<h1>Hello</h1>" << std::endl;
    std::cout << exec("free") << std::endl;
    std::cout << "</body></html>" << std::endl;
    return 0;
}