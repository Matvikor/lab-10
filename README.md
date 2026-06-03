
# Dynamic Stack Library

Библиотека для работы со стеком (LIFO) на динамическом массиве.

## Функции
- Push/Pop/Peek
- Автоматическое расширение буфера
- Валидация аргументов
- Интеграция с Python через ctypes

## Сборка

### Компиляция<br>
gcc -std=c11 -Wall -Wextra -Wpedantic -shared -Iinclude -o build/stack_lib.dll src/stack_lib.c<br>
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude -o build/stack_demo.exe demo/main.c src/stack_lib.c<br>

### Результат работы демо-программы<br>

=== Stack Library Demo ===<br>
Pushing: 10, 20, 30<br>
Peek: 30<br>
Popping sequence: 30 20 10<br>
Final size: 0<br>

### Тесты<br>
=== C Tests ===<br>
Passed: 213 | Failed: 0<br>
