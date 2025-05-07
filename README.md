# Менеджер компьютерного клуба

Программа для управления работой компьютерного клуба с учётом:
- Учёт времени за столами
- Обработка событий
- Расчёт выручки и статистики

## Требования
- Компилятор: GCC ≥9.3 / Clang ≥10 / MinGW ≥8.1
- CMake ≥3.16
- Стандарт C++20

## Быстрый старт
Перейдите в корневую директорию проекта

### Для Linux:
```
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
./ComputerClub input.txt
```

### Для Windows:
```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
ComputerClub.exe input.txt
```
