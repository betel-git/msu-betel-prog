// найти длину наидлиннейшего палиндрома в строке
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::cin;
using std::endl;
using std::max;
using std::min;

const int x = 29;
const long long MOD = 1e9 + 7;

vector<long long> Pows (int n) { // заранее все степени по основанию x по модулю mod посчитаем
    vector<long long> pow;
    pow.resize(n + 1);
    pow[0] = 1;
    
    for (int i = 0; i < n; i++) {
        pow[i + 1] = (pow[i] * x) % MOD;
    }
    return pow;
}

vector<long long> PrefixHashes (const string& s) { // считаем префиксные хеши
    vector<long long> pref;
    int n = s.size();
    pref.resize(n + 1);
    pref[0] = 0;
    
    for (int i = 0; i < n; i++) {
        pref[i + 1] = (pref[i] * x + s[i]) % MOD;
    }
    return pref;
}

long long MegaPolyHash (int l, int r, const vector<long long>& pref, const vector<long long>& pow) { // считаем хеши на отрезке [l,r-1]
    long long res = (pref[r] - pref[l] * pow[r - l]) % MOD;
    if (res < 0) res += MOD;
    return res;
}

bool IsPalindrome (const vector<long long>& direct_hashes, const vector<long long>& reverse_hashes, const vector<long long>& pow, int n, int l, int r) {
    int rev_l = n - 1 - r;
    int rev_r = n - 1 - l;
    return MegaPolyHash(l, r + 1, direct_hashes, pow) == MegaPolyHash(rev_l, rev_r + 1, reverse_hashes, pow);
}

int LongestPalindrome (const string& str) {
    if (str.empty()) return 0;
    // вставим элемент # между каждым символом, чтобы строка всегда была нечётной длины
    // тогда у строки всегда будет центр
    string s;
    s += "#";
    for (int i = 0; i < (int)str.size(); i++) {
        s += str[i];
        if (i != (int)str.size() - 1) {
            s += '#';
        }
    }
    s += "#";
    int n = s.size();

    if (n == 1) return 1;

    vector<long long> pow = Pows(n);
    
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    //cout << rev_s << endl;
    //cout << s << endl;
    
    vector<long long> direct_hashes = PrefixHashes(s);
    vector<long long> reverse_hashes = PrefixHashes(rev_s);

    int max_len = 1;

    int low, mid, high, l, r;
    for (int i = 0; i < n; i++) {
        low = 0;
        high = min(i, n - 1 - i);
        while (low <= high) {
            mid = (low + high) / 2;
            l = i - mid;
            r = i + mid;
            if (IsPalindrome(direct_hashes, reverse_hashes, pow, n, l, r)) {
                max_len = max(max_len, 2 * mid - 1);
                low = mid + 1;
            } 
            else high = mid - 1;
        }
    }

    return (max_len + 1) / 2;
}

int main() {
    string s;
    vector<pair<string, int>> tests;
    tests.emplace_back("", 0);
    tests.emplace_back("a", 1);
    tests.emplace_back("aa", 2);
    tests.emplace_back("ab", 1);
    tests.emplace_back("aba", 3); // нечётный палиндром - вся строка
    tests.emplace_back("abba", 4); // чётный палиндром - вся строка 
    tests.emplace_back("aabbcd", 2); // палиндром в начале
    tests.emplace_back("cdbbaa", 2); // палиндром в конце
    tests.emplace_back("xyabaz", 3); // палиндром в середине
    tests.emplace_back("racecar", 7); // палидром - вся строка
    tests.emplace_back("abacaba", 7); // вложенные палиндромы
    tests.emplace_back("aaaaa", 5); // палидром из строки из одного символа
    tests.emplace_back("Aaaaa", 4); // разные регистры
    tests.emplace_back("a a a", 5); // пробелы
    
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string rev_alphabet = alphabet;
    reverse(rev_alphabet.begin(), rev_alphabet.end());
    alphabet += rev_alphabet;

    tests.emplace_back(alphabet, 104);

    for (int i = 0; i < (int)tests.size(); i++) {
        if (tests[i].second != LongestPalindrome(tests[i].first)) {
            cout << "Ошибка на тесте со строкой " << tests[i].first << ", полученный ответ: " << LongestPalindrome(tests[i].first) << ", правильный ответ: " << tests[i].second << endl;
            //return -1;
        }
    }
    cout << "Успех!" << endl;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "Интерактивный режим: \n";
    cin >> s;
    cout << LongestPalindrome(s) << endl;
    return 0;
}
