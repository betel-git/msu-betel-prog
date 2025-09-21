
struct Complex {
    double re, im;
    Complex () {
        re = 0;
        im = 0;
    }
    Complex (double a, double b) {
        re = a;
        im = b;
    }
    ~Complex() = default;

    double Re() {return re;}
    double Im() {return im;}

    void Re(double a) {re = a;}
    void Im(double a) {im = a;}
    void set(double a, double b) {
        re = a;
        im = b;
    }
    
    Complex operator +(const Complex &a) {
        Complex tmp;
        tmp.re = re + a.re;
        tmp.im = im + a.im;
        return tmp;
    }

    Complex (const Complex &a) {
        re = a.re;
        im = a.im;
    }

    friend std::ostream& operator <<(std::ostream &stream, const Complex &num) {
        stream << "(" << num.re << "," << num.im << ")";
        return stream;
    }

    friend std::istream& operator>>(std::istream &stream, Complex&num) {
        stream >> num.re >> num.im;
        return stream;
    }
    
    Complex operator *(const Complex &a) {
        Complex tmp;
        tmp.re = re * a.re - im * a.im;
        tmp.im = re * a.im + im * a.re;
        return tmp;
    }

    double len() {
        return std::sqrt(re * re + im * im);
    }

    void operator =(const Complex &a) {
        re = a.re;
        im = a.im;
    }
};