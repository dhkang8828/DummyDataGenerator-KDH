#pragma once
#include <string>
#include "sqlite/sqlite3.h"

class DummyGenerator {
public:
    DummyGenerator(const std::string& dbPath);
    ~DummyGenerator();
    void generate(int count);

private:
    sqlite3* db_;
    void insertRecord(const std::string& partNumber, const std::string& partName,
                      int quantity, double unitPrice);
    std::string randomPartName(int seed);
};
