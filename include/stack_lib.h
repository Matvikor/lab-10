#ifndef STACK_LIB_H
#define STACK_LIB_H

/**
 * @file stack_lib.h
 * @brief Публичный интерфейс библиотеки динамического стека целых чисел.
 * 
 * Реализует структуру данных LIFO на основе динамического массива.
 * Поддерживает автоматическое расширение буфера, строгую валидацию аргументов
 * и безопасное управление памятью. Предназначена для вызова из C и Python.
 */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Непрозрачный дескриптор стека.
 */
typedef struct stack_t stack_t;

/**
 * @brief Коды возврата функций библиотеки.
 */
typedef enum {
    STACK_OK = 0,          /**< Успешное выполнение */
    STACK_ERR_NULL_PTR,    /**< Передан NULL-указатель */
    STACK_ERR_EMPTY,       /**< Операция над пустым стеком */
    STACK_ERR_ALLOC,       /**< Ошибка выделения памяти */
    STACK_ERR_INVALID_ARG  /**< Некорректный аргумент (напр., capacity == 0) */
} stack_err_t;

/**
 * @brief Создание нового стека.
 * @param initial_capacity Начальная ёмкость (>0).
 * @return Указатель на стек или NULL при ошибке выделения памяти/аргумента.
 */
stack_t* stack_create(size_t initial_capacity);

/**
 * @brief Уничтожение стека и освобождение памяти.
 * @param stack Указатель на стек. Безопасно передавать NULL.
 */
void stack_destroy(stack_t* stack);

/**
 * @brief Добавление элемента в вершину стека.
 * @param stack Указатель на стек.
 * @param value Добавляемое целое число.
 * @return STACK_OK при успехе, код ошибки иначе.
 * @note При переполнении буфер автоматически увеличивается в 2 раза.
 */
stack_err_t stack_push(stack_t* stack, int value);

/**
 * @brief Извлечение элемента из вершины стека.
 * @param stack Указатель на стек.
 * @param out_value Указатель для сохранения извлечённого значения.
 * @return STACK_OK при успехе, STACK_ERR_EMPTY или STACK_ERR_NULL_PTR иначе.
 */
stack_err_t stack_pop(stack_t* stack, int* out_value);

/**
 * @brief Чтение верхнего элемента без удаления.
 * @param stack Указатель на стек.
 * @param out_value Указатель для сохранения значения.
 * @return STACK_OK при успехе, STACK_ERR_EMPTY или STACK_ERR_NULL_PTR иначе.
 */
stack_err_t stack_peek(const stack_t* stack, int* out_value);

/**
 * @brief Проверка пустоты стека.
 * @param stack Указатель на стек.
 * @return 1 если пуст, 0 иначе. Возвращает 0 при NULL.
 */
int stack_is_empty(const stack_t* stack);

/**
 * @brief Проверка заполненности текущего буфера.
 * @param stack Указатель на стек.
 * @return 1 если заполнен, 0 иначе. Возвращает 0 при NULL.
 */
int stack_is_full(const stack_t* stack);

/**
 * @brief Получение текущего количества элементов.
 * @param stack Указатель на стек.
 * @return Количество элементов или 0 при NULL.
 */
size_t stack_size(const stack_t* stack);

#ifdef __cplusplus
}
#endif

#endif /* STACK_LIB_H */