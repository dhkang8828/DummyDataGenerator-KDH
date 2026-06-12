# DummyDataGenerator

반도체 재고 관리 프로그램의 데이터베이스에 무작위 더미 데이터를 삽입하는 C++ 콘솔 애플리케이션입니다.

## 연관 프로젝트

- **반도체 재고 관리 프로그램 (DataPersistence-KDH)**: https://github.com/dhkang8828/DataPersistence-KDH
  - 위 프로젝트에서 생성한 DB를 대상으로 더미 데이터를 생성 및 삽입합니다.

## 개요

DataPersistence-KDH 프로젝트에서 구축한 반도체 재고 관리 DB의 각 테이블에 테스트 및 개발 목적의 무작위 더미 데이터를 자동으로 생성하여 삽입합니다.

## 개발 환경

| 항목 | 내용 |
|------|------|
| 언어 | C++20 |
| IDE | Visual Studio 2022 |
| 플랫폼 | Windows 10 (x64 / Win32) |
| 빌드 도구 | MSBuild (v145 toolset) |

## 빌드 방법

1. Visual Studio 2022에서 `Project1.slnx` 솔루션 파일을 엽니다.
2. 상단 메뉴에서 빌드 구성을 선택합니다 (`Debug` / `Release`, `x64` / `Win32`).
3. **빌드 > 솔루션 빌드** (`Ctrl+Shift+B`) 를 실행합니다.

또는 MSBuild CLI를 사용합니다:

```bash
msbuild Project1.slnx /p:Configuration=Release /p:Platform=x64
```

## 사용 방법

빌드 후 생성된 실행 파일을 실행하면 DataPersistence-KDH 프로젝트의 DB에 더미 데이터가 삽입됩니다.

```bash
./x64/Release/Project1.exe
```

> 실행 전 DataPersistence-KDH 프로젝트의 DB가 정상적으로 생성되어 있어야 합니다.
