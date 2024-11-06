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

    // �ָ�����Windows��Unixϵͳ�ϲ�ͬ
    std::string delimiter = (_WIN32) ? ";" : ":";

    // �����·��
    if (currentPath.empty()) {
        currentPath = newPath;
    } else {
        currentPath += delimiter + newPath;
    }

    // �����µ�PATH��������
    #ifdef _WIN32
    SetEnvironmentVariable("PATH", currentPath.c_str());
    #else
    setenv("PATH", currentPath.c_str(), 1); // 1��ʾ�滻���еĻ�������
    #endif

    std::cout << "Updated PATH: " << currentPath << std::endl;
}

void testEnvironment() {
    std::cout << "Testing modified PATH by executing 'echo' command..." << std::endl;
    system("croc -h");

}

int main() {
    std::string newPath = "D:\\apps\\croc"; // Windows�µ���·��
    // std::string newPath = "/usr/local/my_new_path"; // Linux�µ���·��

    std::cout << "Current PATH: " << getPathEnv() << std::endl;
    addPathEnv(newPath);

    // �����µ�PATH
    testEnvironment();

    return 0;
}
