# Длинная арифметика

## Задача

  Реализовать пользовательский тип для целого знакового числа фиксированной длины **int2023_t**.
  Размер получившегося типа не должен превышать 253 байтa.

  Для вышеуказанного типа требуется реализовать следующий набор функций и операторов

     1. Конвертация из типа int32_t
     2. Конвертация из строки
     3. Сложение
     4. Вычитание
     5. Умножение
     6. Деление
     7. Вывод числа в поток (не обязательно в 10й системе счисления)

### Тесты

Проект содержит базовый набор тестов, который позволит убедится, что реализация функций выполнена без явных ошибок.
Для запуска тестов в командной строке можно выполнить след операцию:

***cmake --build . --target number_tests && ctest -V***

Тесты при желании можно дополнять, но это не обязательно.

## Примечание

- Переполнение - Undefined Behavior
