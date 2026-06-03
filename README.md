
# Dynamic Stack Library

Библиотека для работы со стеком (LIFO) на динамическом массиве.

## Функции
- Push/Pop/Peek
- Автоматическое расширение буфера
- Валидация аргументов
- Интеграция с Python через ctypes

## Сборка

### Компиляция
gcc -std=c11 -Wall -Wextra -Wpedantic -shared -Iinclude -o build/stack_lib.dll src/stack_lib.c
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude -o build/stack_demo.exe demo/main.c src/stack_lib.c

### Результат работы демо-программы

=== Stack Library Demo ===
Pushing: 10, 20, 30
Peek: 30
Popping sequence: 30 20 10
Final size: 0

### Тесты
=== C Tests ===
Passed: 213 | Failed: 0
