@"
# Dynamic Stack Library

Библиотека для работы со стеком (LIFO) на динамическом массиве.

## Функции
- Push/Pop/Peek
- Автоматическое расширение буфера
- Валидация аргументов
- Интеграция с Python через ctypes

## Сборка
\`\`\`bash
make all
make test
make py-test
\`\`\`
"@ | Out-File -FilePath "README.md" -Encoding utf8 -NoNewline