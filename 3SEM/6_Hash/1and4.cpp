// реализовать хеш-таблицы с закрытой и открытой адресацией с ключами - строками.
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <random>
using std::pair;
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

std::mt19937 rd(time(NULL));

// надо было сразу отдельный класс для элементов создать,
// а не возиться с этими парами...

template<typename T>
struct HashTableClose {
    using VPST = vector<pair<string, T>>; // чтобы постоянно не писать эту большую штуку
    vector<VPST> table;
    int els = 0; // это количество элементов
    int size; // а это размер таблицы, т.е. её ёмкость

    HashTableClose (int init = 101) {
        size = init;
        table.resize(size);
    }

    ~HashTableClose () = default;

    int PolyHash (const string& key) {
        int x = 37;
        int m = 1e9 + 9;

        long long int val = 0;
        long long int pow = 1;

        for (int i = 0; i < (int)key.length(); i++) {
            int char_val = (unsigned char)key[i] + 1;
            val = (val + char_val * pow) % m;
            pow = (pow * x) % m;
        }
        return val % size;
    }

    void rehash () {
        int new_size = size * 2;
        int old_size = size;
        std::vector<VPST> new_table(new_size);
        
        std::vector<VPST> old_table = std::move(table);
        size = new_size;
        table = std::move(new_table);
        els = 0;
        
        // перехешируем
        for (int i = 0; i < (int)old_size; i++) {
            for (int j = 0; j < (int)old_table[i].size(); j++) {
                //insert(old_table[i][j].first, old_table[i][j].second);
                const string& key = old_table[i][j].first;
                const T& val = old_table[i][j].second;
                int id = PolyHash(key);
                VPST& bucket = table[id];

                int found = 0;
                for (int k = 0; k < (int)bucket.size(); k++) {
                    if (bucket[k].first == key) {
                        bucket[k].second = val;
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    bucket.emplace_back(key, val);
                    els++;
                }
            }
        }
    }

    void insert (const string& key, const T& val) {
        if ((double)els / size > 0.75) { // это типа load factor
            rehash();
        }
        int id = PolyHash(key);
        VPST& bucket = table[id];
        
        for (int i = 0; i < (int)bucket.size(); i++) {
            if (bucket[i].first == key) {
                bucket[i].second = val;
                return;
            }
        }
        // здесь я просто ещё не знал про emplace_back
/*         pair<string, T> megapair;
        megapair.first = key;
        megapair.second = val;
        bucket.push_back(megapair); */
        bucket.emplace_back(key, val);
        ++els;
    }

    int search (const string& key, T& val) {
        if (els == 0) return 0;
        int id = PolyHash(key);
        VPST& bucket = table[id];

        for (int i = 0; i < (int)bucket.size(); i++) {
            if (bucket[i].first == key) {
                val = bucket[i].second;
                return 1;
            }
        }
        return 0;
    }
    
    void erase (const string& key) {
        if (els == 0) return;
        int id = PolyHash(key);
        VPST& bucket = table[id];

        for (int i = 0; i < (int)bucket.size(); i++) {
            if (bucket[i].first == key) {
                bucket.erase(bucket.begin() + i);
                els--;
                return;
            }
        }
        return;
    }

    int size_table () {return els;}

};


template <typename T>
struct HashTableOpen {
    vector<pair<string, T>> table;
    vector<int> states; // 1 - занята, 0 - пуста, -1 - удалена
    int els = 0;
    int size;

    HashTableOpen (int init = 101) {
        size = init;
        table.resize(size);
        states.resize(size, 0);
    }
    ~HashTableOpen () = default;

    int PolyHash (const string& key) {
        int x = 37;
        int m = 1e9 + 9;

        long long int val = 0;
        long long int pow = 1;

        for (int i = 0; i < (int)key.length(); i++) {
            int char_val = (unsigned char)key[i] + 1;
            val = (val + char_val * pow) % m;
            pow = (pow * x) % m;
        }
        return val % size;
    }

    int FindIndex (const string& key, bool forInsert = false) {
        int id = PolyHash(key);
        int firstDeleted = -1;
        int i = 0;

        while (i != size) {
            if (states[id] == 0) { // нашли пустую ячейку
                if (forInsert && firstDeleted != -1) {
                    return firstDeleted;
                }
                return id;
            }
            
            if (states[id] == 1 && table[id].first == key) { // нашли существующий ключ
                return id;
            }
            
            // запоминаем первую удаленную ячейку для вставки
            if (forInsert && states[id] == -1 && firstDeleted == -1) {
                firstDeleted = id;
            }
            
            // линейное пробирование
            id = (id + 1) % size;
            i++;
        } 
        
        return forInsert ? firstDeleted : -1;
    }

    void rehash () {
        int new_size = size * 2;
        vector<pair<string, T>> old_table = std::move(table);
        vector<int> old_states = std::move(states);
        int old_size = size;
        
        size = new_size;
        table.resize(size);
        states.resize(size, 0);
        els = 0;
        
        for (int i = 0; i < old_size; i++) {
            if (old_states[i] == 1) {
                const string& key = old_table[i].first;
                int id = PolyHash(key);
                int j = 0;
                
                while (j < size) {
                    if (states[id] == 0) {
                        table[id] = old_table[i];
                        states[id] = 1;
                        els++;
                        break;
                    }
                    id = (id + 1) % size;
                    j++;
                }
            }
        }
    }

    void insert(const string& key, const T& val) {
        if ((double)els / size > 0.75) {
            rehash();
        }
        
        int id = FindIndex(key, true);
        if (id == -1) { // заполнена
            rehash();
            insert(key, val); // пробуем снова после рехеширования
            return;
        }
        
        if (states[id] == 1 && table[id].first == key) { // обновляем существующий ключ
            table[id].second = val;
        } 
        else { // вставляем новый ключ
            table[id].first = key;
            table[id].second = val;
            states[id] = 1;
            els++;
        }
    }

    int search (const string& key, T& val) {
        if (els == 0) return 0;
        
        int id = FindIndex(key);
        if (id != -1 && states[id] == 1 && table[id].first == key) {
            val = table[id].second;
            return 1;
        }
        return 0;
    }

    void erase (const string& key) {
        if (els == 0) return;
        
        int id = FindIndex(key);
        if (id != -1 && states[id] == 1 && table[id].first == key) {
            states[id] = -1;
            table[id].first = "";
            els--;
        }
    }

};


string RandStr () {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string rand_str;
    int str_len = rd() % 10 + 1; // здесь можно выбрать нужную длину строки

    for (int i = 0; i < str_len; i++) {
        int rand_ind = rd() % alphabet.length();
        rand_str += alphabet[rand_ind];
    }

    return rand_str;
}


void StressTest (int n) {
    HashTableClose<int> ht;
    HashTableOpen<int> ht2;
    vector<pair<string, int>> lst;
    
    for (int i = 0; i < n; i++) {
        int typ = rd() % 3;
        if (typ == 0) { // вставка
            int x = rd() % (int)pow(10, 4);
            string str = RandStr();
            ht.insert(str, x);
            ht2.insert(str, x);
            pair<string, int> megapair;
            megapair.first = str;
            megapair.second = x;
            lst.push_back(megapair);
            cout << i << ") " << typ << " " << str << " " << x << endl;
        }
        if (typ == 1 && !lst.empty()) { // удаление
            std::swap(lst[rd() % lst.size()], lst.back());
            ht.erase(lst.back().first);
            ht2.erase(lst.back().first);
            cout << i << ") " << typ << " " << lst.back().first << endl;
            lst.pop_back();
        }
        if (typ == 2) { // поиск
            string x;
            int val, val2;
            if (lst.empty()) {
                continue;
            } 
            else {
                x = (rd() % 2) ? RandStr() : lst[rd() % lst.size()].first;
            }
            cout << i << ") " << typ << " " << x << endl;
            cout << "   close: " << ht.search(x, val);
            if (ht.search(x, val) == 0) cout << endl;
            else cout << " " << val << endl;

            cout << "   open: " << ht2.search(x, val2);
            if (ht2.search(x, val2) == 0) cout << endl;
            else cout << " " << val2 << endl;
            if (ht.search(x, val) != ht2.search(x, val2) || (val != val2 && ht.search(x, val) == 1)) {
                cout << "ERROR" << endl;
                return;
            }
        }
    }
    cout << "Успех!" << endl;
    return;
}

int main() {
    int n = 1000;
    StressTest(n);

    
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Введите 0 для входа в интерактивный режим, иначе введите что-нибудь другое: ";
    std::string str;
    cin >> str;
    if (str != "0") return 0;

    HashTableClose<int> ht;
    int m;
    cout << "Введите количество операций: ";
    cin >> m;
    for (int i = 0; i < m; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            string in1;
            int in2;
            cin >> in1 >> in2;
            ht.insert(in1, in2);
        }
        else if (type == 2) {
            string in;
            cin >> in;
            ht.erase(in);
        }
        else {
            string in1;
            int in2;
            cin >> in1;
            cout << ht.search(in1, in2);
            if (ht.search(in1, in2) == 0) cout << endl;
            else cout << " " << in2 << endl;
        }
    }

    return 0;
}
