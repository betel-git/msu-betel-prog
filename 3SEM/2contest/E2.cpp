#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include "stack.h"
#include "modular.h"
#include "compl.h"
using namespace std;


bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}


vector<string> Parser(const string& expression) {
    vector<string> tokens;
    string token;
    
    for (char c : expression) {
        if (c == ' ') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }
    
    return tokens;
}

double PolandNotation(const string& expression) {
    Stack<double> st;
    vector<string> tokens = Parser(expression);
    
    for (const string& token : tokens) {
        if (isOperator(token)) {
            if (st.size < 2) {
                throw runtime_error("Недостаточно операндов для операции: " + token);
            }
            
            double b = st.pop();
            double a = st.pop();
            double result;
            
            if (token == "+") {
                result = a + b;
            } else if (token == "-") {
                result = a - b;
            } else if (token == "*") {
                result = a * b;
            } else if (token == "/") {
                if (fabs(b) < 1e-9) {
                    throw runtime_error("Деление на ноль");
                }
                result = a / b;
            }
            
            st.push(result);
        }
        else {
            double num = stod(token);
            st.push(num);
        }
    }
    
    if (st.size != 1) {
        throw runtime_error("Некорректное выражение");
    }
    
    return st.pop();
}


int main() {
    string expr;
    getline(cin, expr);
    cout << PolandNotation(expr) << endl;
    return 0;
}