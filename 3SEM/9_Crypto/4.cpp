#include "crypto.h"

// функция Эйлера (простая реализация для простого p)
long long euler_phi(long long p) {
    return p - 1; // для простого p
}

// нахождение порядка элемента g
long long find_order(long long g, long long p) {
    long long phi = euler_phi(p);
    long long order = phi;
    
    // факторизуем phi = p-1 и проверяем делители
    vector<long long> divisors;
    for (long long i = 1; i * i <= phi; i++) {
        if (phi % i == 0) {
            divisors.push_back(i);
            if (i != phi / i) {
                divisors.push_back(phi / i);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
    
    for (long long d : divisors) {
        if (fast_pow(g, d, p) == 1) {
            order = d;
            break;
        }
    }
    return order;
}

// расширенный алгоритм Евклида
long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// решение линейного сравнения a*x ≡ b (mod m)
vector<long long> solve_linear_congruence(long long a, long long b, long long m) {
    long long x, y;
    long long gcd = extended_gcd(a, m, x, y);
    vector<long long> solutions;
    
    if (b % gcd != 0) {
        return solutions; // нет решений
    }
    
    long long x0 = (x * (b / gcd)) % m;
    if (x0 < 0) x0 += m;
    
    for (long long k = 0; k < gcd; k++) {
        solutions.push_back((x0 + k * (m / gcd)) % m);
    }
    
    return solutions;
}

// дискретный логарифм в общем случае
vector<long long> discrete_log_general(long long g, long long a, long long p) {
    if (a == 1) {
        return {0};
    }
    
    // находим порядок g
    long long order_g = find_order(g, p);
    
    // baby-step giant-step для подгруппы порядка order_g
    long long m = ceil(sqrt(order_g));
    
    unordered_map<long long, long long> table;
    long long current = a % p;
    
    // baby steps
    for (long long j = 0; j < m; j++) {
        if (table.find(current) == table.end()) {
            table[current] = j;
        }
        current = (current * g) % p;
    }
    
    // giant steps
    long long g_m = fast_pow(g, m, p);
    current = 1;
    vector<long long> solutions;
    
    for (long long i = 0; i <= m; i++) {
        if (table.find(current) != table.end()) {
            long long j = table[current];
            long long y = (i * m - j) % order_g;
            if (y < 0) y += order_g;
            // проверяем, что это действительно решение
            if (fast_pow(g, y, p) == a) {
                solutions.push_back(y);
            }
        }
        current = (current * g_m) % p;
    }
    
    if (solutions.empty()) {
        // метод с линейными сравнениями
        long long phi = euler_phi(p);
        solutions = solve_linear_congruence(1, 0, order_g);
    }

    sort(solutions.begin(), solutions.end());
    solutions.erase(unique(solutions.begin(), solutions.end()), solutions.end());
    
    return solutions;
}

// главная функция - находит наименьшее неотрицательное решение
long long discrete_log(long long g, long long a, long long p) {
    vector<long long> solutions = discrete_log_general(g, a, p);
    if (solutions.empty()) {
        return -1; // решение не существует
    }
    return solutions[0]; // возвращаем наименьшее решение
}

int main() {
    long long p, g, a;
    cin >> p >> g >> a;
    
    long long y = discrete_log(g, a, p);
    if (y == -1) {
        cout << "Решение не существует" << endl;
    } else {
        cout << y << endl;
        cout << "Проверка: " << g << "^" << y << " mod " << p << " = " << fast_pow(g, y, p) << endl;
    }
    
    return 0;
}
