# DummyDataGenerator

반도체 재고 관리 프로그램의 데이터베이스에 무작위 더미 데이터를 삽입하는 C++ 콘솔 애플리케이션입니다.

## 연관 프로젝트

- **반도체 재고 관리 프로그램 (DataPersistence-KDH)**: https://github.com/dhkang8828/DataPersistence-KDH
  - 위 프로젝트에서 생성한 `inventory.db`를 대상으로 더미 데이터를 삽입합니다.

## 개요

DataPersistence-KDH 프로젝트의 `inventory` 테이블에 100건의 무작위 반도체 부품 데이터를 자동 생성하여 삽입합니다.

### 삽입 대상 테이블

| 컬럼 | 타입 | 설명 |
|------|------|------|
| part_number | TEXT | 품번 (`DUM-0001` ~ `DUM-0100`) |
| part_name | TEXT | 부품명 (10종 타입 × 다양한 스펙 랜덤 조합) |
| quantity | INTEGER | 수량 (1 ~ 9999 랜덤) |
| unit_price | REAL | 단가 (100.0 ~ 99999.0 랜덤) |

### 생성 부품 종류

`DRAM`, `NAND Flash`, `NOR Flash`, `AP Chip`, `MCU`, `FPGA`, `GPU`, `CPU`, `Power IC`, `Sensor IC`

## 프로젝트 구조

```
Project1/
├── main.cpp               # 진입점 (DB 경로, 삽입 건수 설정)
├── DummyGenerator.h       # 더미 데이터 생성기 클래스 선언
├── DummyGenerator.cpp     # 랜덤 데이터 생성 및 SQLite INSERT 구현
└── sqlite/
    ├── sqlite3.h          # SQLite3 헤더
    └── sqlite3.c          # SQLite3 amalgamation 소스
```

## 개발 환경

| 항목 | 내용 |
|------|------|
| 언어 | C++20 |
| IDE | Visual Studio 2022 |
| 플랫폼 | Windows 10 (x64 / Win32) |
| 빌드 도구 | MSBuild (v145 toolset) |
| DB | SQLite3 |

## 사전 조건

실행 전 DataPersistence-KDH 프로젝트를 먼저 실행해 `inventory.db` 파일이 생성되어 있어야 합니다.

DB 경로 (`main.cpp` 내 `DB_PATH` 상수):
```
C:\Reviewer\Day03-Project\DataPersistence\DP\inventory.db
```

## 빌드 방법

**Visual Studio 2022**

1. `Project1.slnx` 솔루션 파일을 엽니다.
2. 빌드 구성 선택 (`Debug` / `Release`, `x64` / `Win32`).
3. **빌드 > 솔루션 빌드** (`Ctrl+Shift+B`)

**MSBuild CLI**

```bash
MSBuild.exe Project1.slnx /p:Configuration=Release /p:Platform=x64
```

## 실행 방법

```bash
x64\Release\Project1.exe
```

실행 시 `DUM-0001` ~ `DUM-0100` 형식의 품번으로 100건이 삽입되며, 기존 `SEM-` 데이터와 충돌하지 않습니다.
