// Реализовать декартово дерево
// запуск: wg++ -g -O0 Treap.cpp
// valgrind --leak-check=full --show-leak-kinds=all --demangle=yes -s ./a.out
#include <iostream>
#include <random>
#include <utility>
#include <climits>
#include <vector>
#include <algorithm>
#include <ctime>
using std::pair;
using std::cout;
using std::cin;
using std::endl;
using std::sort;

std::mt19937 rd(time(NULL));

struct Node {
    int id;
    int prior;
    int size;

    Node* l;
    Node* r;
    Node () = default;
    Node (int x) {
        id = x;
        prior = rd();
        size = 1;
        l = NULL;
        r = NULL;
    }
};


struct Treap {
    Node* root;

    Treap () {root = nullptr;}
    ~Treap () {_clear(root);}

    pair<Node*, Node*> split (Node* v, int x) {
        if (v == nullptr) {
            return {nullptr, nullptr};
        }
        if (v->id <= x) {
            pair<Node*, Node*> p = split(v->r, x);
            v->r = p.first;
            update_size(v);
            return {v, p.second};
        }
        pair<Node*, Node*> p = split(v->l, x);
        v->l = p.second;
        update_size(v);
        return {p.first, v};
    }

    Node* merge (Node* l, Node* r) {
        if (l == nullptr) {
            return r;
        }
        if (r == nullptr) {
            return l;
        }
        if (l->prior > r->prior) {
            l->r = merge(l->r, r);
            update_size(l);
            return l;
        }
        r->l = merge(l, r->l);
        update_size(r);
        return r;
    }

    Node* _search (Node* v, int x) {
        if (v == nullptr) return nullptr;
        if (v->id == x) return v;
        if (x < v->id) return _search(v->l, x);
        return _search(v->r, x);
    }

    void _clear (Node* v) {
        if (v != nullptr) {
            _clear(v->l);
            _clear(v->r);
            delete v;
        }
    }

    int _lower_bound (Node* v, int x) {
        if (v == nullptr) {
            return INT_MAX;
        }
        if (v->id == x) {
            return x;
        }
        if (v->id < x) {
            return _lower_bound(v->r, x);
        } 
        else {
            int lres = _lower_bound(v->l, x);
            if (lres != INT_MAX) {
                return lres;
            } else {
                return v->id;
            }
        }
    }

    void printTree (Node* node, const std::string& prefix = "", bool isLeft = true) {
        if (node != nullptr) {
            std::cout << prefix;
            std::cout << (isLeft ? "├──" : "└──" );
            std::cout << node->id << "[" << node->prior << "]" << std::endl;
            printTree(node->l, prefix + (isLeft ? "│   " : "    "), true);
            printTree(node->r, prefix + (isLeft ? "│   " : "    "), false);
        }
    }

    void update_size (Node* v) {
        if (v != nullptr) {
            v->size = 1;
            if (v->l != nullptr) v->size += v->l->size;
            if (v->r != nullptr) v->size += v->r->size;
        }
    }

    int _kth_order_statistic (Node* v, int k) {
        if (v == nullptr || k < 0 || k >= v->size) {
            return INT_MAX;
        }
        
        int left_size = (v->l != nullptr) ? v->l->size : 0;
        
        if (k < left_size) {
            return _kth_order_statistic(v->l, k);
        } 
        else if (k == left_size) {
            return v->id;
        }
        else {
            return _kth_order_statistic(v->r, k - left_size - 1);
        }
    }

    //----------------------------------------------

    void insert (int x) {
        if (search(x)) {return;}
        Node* newNode = new Node(x);

        pair<Node*, Node*> p = split(root, x);
        
        root = merge(merge(p.first, newNode), p.second);
    }

    void erase (int x) {
        pair<Node*, Node*> p1 = split(root, x - 1);
        pair<Node*, Node*> p2 = split(p1.second, x);
        if (p2.first != nullptr) {
            delete p2.first;
        }
        root = merge(p1.first, p2.second);
    }

    void print () {
        std::cout << "Дерево:" << std::endl;
        if (root == nullptr) {
            std::cout << "Пустое дерево" << std::endl;
        } else {
            printTree(root);
        }
        std::cout << std::endl;
    }

    int lower_bound (int x) {
        return _lower_bound(root, x);
    }

    bool search (int x) {
        return _search(root, x) != nullptr;
    }

    int kth_order_statistic (int k) {
        return _kth_order_statistic(root, k);
    }

    int count_less_than (int x) {
        pair<Node*, Node*> p = split(root, x - 1);
        int result = (p.first != nullptr) ? p.first->size : 0;
        root = merge(p.first, p.second);
        return result;
    }

    int size () {
        return (root != nullptr) ? root->size : 0;
    }

};

//===================================================================================

// Тест на корректность вставки и удаления
void TestInsertEraseSequence (int n) {
    srand(time(NULL));
    cout << "\n=== ТЕСТ: Последовательность вставок и удалений ===" << endl;
    
    Treap treap;
    std::vector<int> lst;
    
    // Вставляем случайные элементы
    for (int i = 0; i < n; i++) {
        int val = -1000 + (rand() % 2000);
        treap.insert(val);
        lst.push_back(val);
    }
    
    // Проверяем, что все элементы присутствуют
    int found_count = 0;
    for (int i = 0; i < n; i++) {
        if (treap.search(lst[i])) {
            found_count++;
        }
    }
    cout << "После вставки: " << found_count << "/" << n << " элементов найдено" << endl;
    
    // Удаляем элементы
    int remove_count = n;
    for (int i = 0; i < remove_count; i++) {
        treap.erase(lst[i]);
    }
    
    // Проверяем оставшиеся элементы (если, конечно же, они вообще есть)
    found_count = 0;
    for (int i = remove_count; i < n; i++) {
        if (treap.search(lst[i])) {
            found_count++;
        }
    }
    cout << "После удаления: " << found_count << "/" << (n - remove_count) 
                << " оставшихся элементов найдено" << endl;
}

// Тест lower_bound на специальных случаях
void TestLowerBoundCornerCases () {
    cout << "\n=== ТЕСТ: Граничные случаи lower_bound ===" << endl;
    
    Treap treap;
    
    // Тест на пустом дереве
    int result = treap.lower_bound(228);
    cout << "Пустое дерево, lower_bound(228) = " 
                << (result == INT_MAX ? "INT_MAX" : std::to_string(result)) 
                << " (ожидается INT_MAX)" << endl;
    
    // Добавляем элементы
    std::vector<int> tvalues = {1, 3, 5, 7, 9};
    for (int i = 0; i < (int)tvalues.size(); i++) {
        treap.insert(tvalues[i]);
    }

    treap.print();
    
    std::vector<pair<int, int>> cases = {
        {0, 1},   // Меньше минимального
        {1, 1},   // Точное совпадение
        {2, 3},   // Между элементами
        {5, 5},   // Точное совпадение
        {8, 9},   // Между элементами
        {9, 9},   // Точное совпадение
        {10, INT_MAX} // Больше максимального
    };
    
    for (int i = 0; i < (int)cases.size(); i++) {
        int result = treap.lower_bound(cases[i].first);
        bool correct = (result == cases[i].second);
        cout << "lower_bound(" << cases[i].first << ") = " 
                    << (result == INT_MAX ? "INT_MAX" : std::to_string(result))
                    << " (ожидается " 
                    << (cases[i].second == INT_MAX ? "INT_MAX" : std::to_string(cases[i].second))
                    << ") - " << (correct ? "ПРОЙДЕНО" : "ОШИБКА") << endl;
    }
}

// Тест на повторяющиеся операции
void TestDuplicateOperations () {
    cout << "\n=== ТЕСТ: Повторяющиеся операции ===" << std::endl;
    
    Treap treap;
    int test_value = 228;
    
    // Многократная вставка одного элемента
    for (int i = 0; i < 1000; i++) {
        treap.insert(test_value);
    }
    
    bool found = treap.search(test_value);
    cout << "После 1000 вставок " << test_value << ": " 
                << (found ? "найден" : "не найден") 
                << " (ожидается найден)" << endl;
    
    // Однократное удаление
    treap.erase(test_value);
    found = treap.search(test_value);
    cout << "После удаления " << test_value << ": " 
                << (found ? "найден" : "не найден") 
                << " (ожидается не найден)" << endl;
}

// Тест на большой объем данных
void StressTest1 (int n, int a, int b) {
    cout << "\n=== ТЕСТ: Большой объем данных (" << n << " элементов, (a,b) = (" << a << ", " << b <<  ")) ===" << endl;
    
    Treap treap;
    
    auto start = std::clock();
    
    // Вставка
    for (int i = 0; i < n; i++) {
        int val = a + (rand() % (2 * b + 1));
        treap.insert(val);
    }
    auto insert_time = std::clock() - start;

    //if (n == 10000) treap.print();
    
    // Поиск
    start = std::clock();
    int search_count = 0;
    for (int i = a; i < b; i++) {
        //int val = a + (rand() % (2 * b + 1));
        if (treap.search(i)) {
            search_count++;
        }
    }
    auto search_time = std::clock() - start;

    // Lower bound
    start = std::clock();
    int bound_count = 0;
    for (int i = a; i < b; i++) {
        //int val = a + (rand() % (2 * b + 1));
        if (treap.lower_bound(i)) {
            bound_count++;
        }
    }
    auto bound_time = std::clock() - start;

    // Erase
    start = std::clock();
    for (int i = a; i < b; i++) {
        treap.erase(i);
    }
    auto erase_time = std::clock() - start;
    
    cout << "Вставка: " << (double)insert_time / CLOCKS_PER_SEC << " сек" << endl;
    cout << "Search: " << (double)search_time / CLOCKS_PER_SEC << " сек" << endl;
    cout << "Найдено элементов: " << search_count << endl;
    cout << "Lower bound: " << (double)bound_time / CLOCKS_PER_SEC << " сек" << endl;
    cout << "Сколько раз найдена нижняя граница: " << bound_count << endl;
    cout << "Erase: " << (double)erase_time / CLOCKS_PER_SEC << " сек" << endl;
}


void TestOrderStatistics () {
    cout << "\n=== ТЕСТИРОВАНИЕ ПОРЯДКОВОЙ СТАТИСТИКИ ===" << endl;
    
    Treap treap;

    std::vector<int> lst = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < (int)lst.size(); i++) {
        treap.insert(lst[i]);
    }
    
    // Сортируем для проверки
    sort(lst.begin(), lst.end());
    
    treap.print();
    cout << "Размер дерева: " << treap.size() << endl;
    cout << "Отсортированные элементы: ";
    for (int i = 0; i < (int)lst.size(); i++) cout << lst[i] << " ";
    cout << endl << endl;
    
    cout << "K-ая порядковая статистика (k от 0 до " << lst.size() - 1 << "):" << endl;
    for (int k = 0; k < (int)lst.size(); k++) {
        int a = lst[k];
        int b = treap.kth_order_statistic(k);
        cout << "k = " << k << ": ожидается " << a << ", получено " << b;
        cout << (a == b ? " ПРОЙДЕНО" : " НЕ ПРОЙДЕНО") << endl;
    }
    cout << endl;
    
    cout << "Сколько чисел меньше x:" << endl;
    std::vector<int> test_values = {0, 20, 25, 40, 45, 70, 75, 100};
    for (int i = 0; i < (int)test_values.size(); i++) {
        int expected = 0;
        for (int j = 0; j < (int)lst.size(); j++) {
            if (lst[j] < test_values[i]) expected++;
        }
        int c = treap.count_less_than(test_values[i]);
        
        cout << "x = " << test_values[i] << ": ожидается " << expected 
             << ", получено " << c << endl;
    }
    cout << endl;
    
    cout << "Граничные случаи:" << endl;
    cout << "kth(-1): " << (treap.kth_order_statistic(-1) == INT_MAX ? "INT_MAX" : std::to_string(treap.kth_order_statistic(-1))) << " (ожидается INT_MAX)" << endl;
    cout << "kth(100): " << (treap.kth_order_statistic(100) == INT_MAX ? "INT_MAX" : std::to_string(treap.kth_order_statistic(100))) << " (ожидается INT_MAX)" << endl;
    cout << "count_less_than(INT_MIN + 1): " << treap.count_less_than(INT_MIN + 1) << " (ожидается 0)" << endl;
    cout << "count_less_than(INT_MAX): " << treap.count_less_than(INT_MAX) << " (ожидается " << lst.size() << ")" << endl;
}


void StressTest2 () {
    cout << "\n=== СТРЕСС-ТЕСТ ДЛЯ ВТОРОЙ ЗАДАЧИ ===" << endl;
    
    Treap treap;
    std::vector<int> lst;
    int n = 1000;
    
    // Заполняем случайными элементами
    for (int i = 0; i < n; i++) {
        int x = -10000000 + (rand() % 20000000);;
        treap.insert(x);
        lst.push_back(x);
    }
    
    // Сортируем и удаляем повторения в векторе
    sort(lst.begin(), lst.end());
    lst.erase(std::unique(lst.begin(), lst.end()), lst.end());
    
    // Проверяем порядковую статистику
    bool all_correct = true;
    for (int k = 0; k < (int)lst.size(); k++) {
        int a = lst[k];
        int b = treap.kth_order_statistic(k);
        if (a != b) {
            cout << "Ошибка порядковой статистики при k = " << k << ": ожидается " << a << ", получено " << b << endl;
            cout << "Отрезок, на котором ошибка: " << lst[k - 1] << " " << lst[k] << " " << lst[k + 1] << endl;
            all_correct = false;
            break;
        }
    }
    
    if (all_correct) {
        cout << "Порядковая статистика: ВСЕ ТЕСТЫ ПРОЙДЕНЫ" << endl;
    }
    
    // Проверяем подсчет меньших чисел
    all_correct = true;
    for (int i = 0; i < 100; i++) {
        int x = -10000000 + (rand() % 20000000);;
        int a = 0;
        for (int i = 0; i < (int)lst.size(); i++) {
            if (lst[i] < x) a++;
        }
        int b = treap.count_less_than(x);
        if (a != b) {
            cout << "Ошибка подсчёта мешьших чисел при x = " << x << ": ожидается " << a << ", получено " << b << endl;
            all_correct = false;
            break;
        }
    }
    
    if (all_correct) {
        cout << "Подсчет меньших чисел: ВСЕ ТЕСТЫ ПРОЙДЕНЫ" << endl;
    }
    
    cout << "Размер дерева: " << treap.size() << " (ожидается " << n << ")" << endl;
}


int main() {
    TestInsertEraseSequence(1000000);
    TestLowerBoundCornerCases();
    void TestDuplicateOperations();
    StressTest1(10000, -10000, 10000);
    StressTest1(100000, -10000, 10000);
    StressTest1(1000000, -10000, 10000);
    StressTest1(10000000, -100000, 100000);
    TestOrderStatistics();
    StressTest2();

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Хотите получить своё декартово дерево? (YES / NO)" << endl;
    std::string str;
    cin >> str;
    if (str == "NO") return 0;

    Treap treap;
    int n, in;
    cout << "Введите число элементов: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            cin >> in;
            treap.insert(in);
        }
        else if (type == 2) {
            cin >> in;
            treap.erase(in);
        }
        else {
            cin >> in;
            cout << treap.search(in) << endl;
        }
    }
    treap.print();
    return 0;
}
