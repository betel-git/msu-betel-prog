# Декартово дерево

1. Реализовать декартово дерево (запросы добавления, удаления, поиска данного числа, lower_bound). Написать стресс-
тест для проверки корректности кода. P.S. Запрос lower_bound — запрос вида “минимальное число, не меньшее $x$”.
2. Реализовать в декартовом дереве запросы “$k$-ая порядковая статистика” и “сколько есть чисел, меньших данного”.

# Запуск программы:
g++ -g -O0 Treap.cpp
со следующими ключами:
-W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align \
-Wformat-security -Wmissing-format-attribute -Wformat=1 \
-Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors \
-Wunused -Wuninitialized \
--param inline-unit-growth=1000000 --param max-inline-insns-single=10000000 \
--param large-function-growth=10000000 -fPIC

valgrind --leak-check=full --show-leak-kinds=all --demangle=yes -s ./a.out