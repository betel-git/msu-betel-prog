
template <int MOD = 1000000007>
struct Modular {
    int val;
    
    Modular () {val = 0;}
    Modular (int a) {
        val = a % MOD;
        if (val < 0) val += MOD;
    }

    int value() const {return val;}
    
    Modular operator +(const Modular &a) {
        return (val + a.val) % MOD;
    }

    Modular operator *(const Modular &a) {
        return (val * a.val) % MOD;
    }
    
    friend std::ostream& operator<<(std::ostream &stream, const Modular &num) {
        return stream << num.val;
    }
    
    friend std::istream& operator>>(std::istream& stream, Modular& num) {
        int v;
        stream >> v;
        num = Modular(v);
        return stream;
    }

    
    
    Modular pow(Modular base, int exponent) {
        if (exponent < 0) return inv().pow(-exponent);
        
        Modular result(1);
        
        while (exponent > 0) {
            if (exponent & 1) result = result * base;
            base = base * base;
            exponent >>= 1;
        }
        
        return result;
    }
    
    Modular inv() const {
        if (val == 0) exit(1);
        
        int a = val, b = MOD;
        int x = 0, y = 1, last_x = 1, last_y = 0;
        
        while (b != 0) {
            int quotient = a / b;
            
            int temp = a;
            a = b;
            b = temp % b;
            
            temp = x;
            x = last_x - quotient * x;
            last_x = temp;
            
            temp = y;
            y = last_y - quotient * y;
            last_y = temp;
        }
        
        if (last_x < 0) last_x += MOD;
        return Modular(last_x);
    }
    
};

using Mod = Modular<1000000007>;