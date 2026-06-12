#include "DummyGenerator.h"
#include <iostream>
#include <stdexcept>
#include <random>
#include <sstream>
#include <iomanip>
#include <vector>

static const std::vector<std::pair<std::string, std::vector<std::string>>> PART_CATALOG = {
    { "DRAM",       { "4GB DDR4", "8GB DDR4", "16GB DDR5", "32GB DDR5" } },
    { "NAND Flash", { "128GB", "256GB", "512GB", "1TB" }                 },
    { "NOR Flash",  { "16MB", "32MB", "64MB" }                           },
    { "AP Chip",    { "A15", "A16", "A17", "Snapdragon 8 Gen3" }         },
    { "MCU",        { "STM32F4", "STM32H7", "ESP32", "ATmega328" }       },
    { "FPGA",       { "Artix-7", "Kintex-7", "Virtex-7" }               },
    { "GPU",        { "RTX 4080", "RX 7900", "Arc A770" }                },
    { "CPU",        { "i9-13900K", "Ryzen 9 7950X", "M2 Ultra" }         },
    { "Power IC",   { "LDO 3.3V", "Buck 5V", "Boost 12V" }              },
    { "Sensor IC",  { "Temp", "Pressure", "Gyro" }                       },
};

DummyGenerator::DummyGenerator(const std::string& dbPath) : db_(nullptr) {
    if (sqlite3_open(dbPath.c_str(), &db_) != SQLITE_OK)
        throw std::runtime_error("DB 열기 실패: " + std::string(sqlite3_errmsg(db_)));
    std::cout << "[DB] 연결 성공: " << dbPath << "\n";
}

DummyGenerator::~DummyGenerator() {
    if (db_) sqlite3_close(db_);
}

void DummyGenerator::generate(int count) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int>    qtyDist(1, 9999);
    std::uniform_real_distribution<double> priceDist(100.0, 99999.0);
    std::uniform_int_distribution<int>    catalogDist(0, (int)PART_CATALOG.size() - 1);

    int inserted = 0;
    for (int i = 1; i <= count; ++i) {
        std::ostringstream pn;
        pn << "DUM-" << std::setw(4) << std::setfill('0') << i;

        int ci = catalogDist(rng);
        const auto& [type, specs] = PART_CATALOG[ci];
        std::uniform_int_distribution<int> specDist(0, (int)specs.size() - 1);
        std::string partName = type + " " + specs[specDist(rng)];

        try {
            insertRecord(pn.str(), partName, qtyDist(rng), priceDist(rng));
            std::cout << "  [" << i << "/" << count << "] " << pn.str() << " | " << partName << "\n";
            ++inserted;
        }
        catch (const std::exception& e) {
            std::cerr << "  [SKIP] " << pn.str() << ": " << e.what() << "\n";
        }
    }
    std::cout << "[완료] " << inserted << "건 삽입 완료\n";
}

void DummyGenerator::insertRecord(const std::string& partNumber, const std::string& partName,
                                   int quantity, double unitPrice) {
    const char* sql =
        "INSERT INTO inventory (part_number, part_name, quantity, unit_price) "
        "VALUES (?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db_));

    sqlite3_bind_text  (stmt, 1, partNumber.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text  (stmt, 2, partName.c_str(),   -1, SQLITE_TRANSIENT);
    sqlite3_bind_int   (stmt, 3, quantity);
    sqlite3_bind_double(stmt, 4, unitPrice);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE)
        throw std::runtime_error(sqlite3_errmsg(db_));
}
