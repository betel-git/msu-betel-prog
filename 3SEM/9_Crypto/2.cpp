// DIFFIE-HELLMAN KEY EXCHANGE PROTOCOL
#include "crypto.h"
const int p = 1000000007;
std::mt19937 rd(time(NULL));


// из следствия малой теоремы Ферма a^{-1} = a^{p-2} (mod p) при простом p
ll fast_inv(ll a, ll mod) {
    return fast_pow(a, mod - 2, mod);
}


struct Speaker {
    ll s; // секретный ключ
    ll g; // первообразный корень
    
    Speaker (ll prim_root) {
        g = prim_root;
        s = rd() % (p - 1) + 1;
    }
    
    ll gen_open () {
        return fast_pow(g, s, p);
    }
    
    ll cipher (ll message, ll open_key) {
        ll shared_key = fast_pow(open_key, s, p);
        return (message * shared_key) % p;
    }
    
    ll decipher (ll cipher_text, ll open_key) {
        ll shared_key = fast_pow(open_key, s, p);
        ll inv_shared_key = fast_inv(shared_key, p);
        return (cipher_text * inv_shared_key) % p;
    }
};


int main() {
    ll prim_root = find_root(p);
    Speaker alice(prim_root);
    Speaker bob(prim_root);
    
    ll alice_open = alice.gen_open();
    ll bob_open = bob.gen_open();
    
    cout << "Открытый ключ Алисы: " << alice_open << endl;
    cout << "Открытый ключ Боба: " << bob_open << endl;
    
    ll message;
    cout << "Введите сообщение, которое Алиса передаст Бобу:" << endl;
    cin >> message;
    cout << "Изначальное сообщение (число больше 10^9 + 6 нельзя): " << message << endl;
    
    ll encrypted = alice.cipher(message, bob_open);
    cout << "Зашифрованное сообщение: " << encrypted << endl;
    
    ll decrypted = bob.decipher(encrypted, alice_open);
    cout << "Расшифрованное сообщение: " << decrypted << endl;
    
    cout << "Шифрование " << (message == decrypted ? "успешно" : "провалилось") << endl;
    
    return 0;
}
