#include <iostream>
#include <string>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

std::string getPathEnv() {
    const char* pathEnv = std::getenv("PATH");
    return pathEnv ? std::string(pathEnv) : std::string();
}

void addPathEnv(const std::string& newPath) {
    std::string currentPath = getPathEnv();

    // 分隔符在Windows和Unix系统上不同
    std::string delimiter = (_WIN32) ? ";" : ":";

    // 添加新路径
    if (currentPath.empty()) {
        currentPath = newPath;
    } else {
        currentPath += delimiter + newPath;
    }

    // 设置新的PATH环境变量
    #ifdef _WIN32
    SetEnvironmentVariable("PATH", currentPath.c_str());
    #else
    setenv("PATH", currentPath.c_str(), 1); // 1表示替换现有的环境变量
    #endif

    std::cout << "Updated PATH: " << currentPath << std::endl;
}

void testEnvironment() {
    std::cout << "Testing modified PATH by executing 'echo' command..." << std::endl;
    system("croc -h");

}

int main() {
    std::string newPath = "D:\\apps\\croc"; // Windows下的新路径
    // std::string newPath = "/usr/local/my_new_path"; // Linux下的新路径

    std::cout << "Current PATH: " << getPathEnv() << std::endl;
    addPathEnv(newPath);

    // 测试新的PATH
    testEnvironment();

    return 0;
}
