#include <iostream>
#include <windows.h>
#include "DummyGenerator.h"

static const int   DUMMY_COUNT = 100;
static const char* DB_PATH     = "C:\\Reviewer\\Day03-Project\\DataPersistence\\DP\\inventory.db";

int main() {
    SetConsoleOutputCP(CP_UTF8);
    try {
        std::cout << "[DummyDataGenerator] " << DUMMY_COUNT << "건 삽입 시작\n";
        DummyGenerator gen(DB_PATH);
        gen.generate(DUMMY_COUNT);
    }
    catch (const std::exception& e) {
        std::cerr << "[오류] " << e.what() << "\n";
        return 1;
    }
    return 0;
}
