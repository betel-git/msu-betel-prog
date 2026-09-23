#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

using namespace std;

#define PORT 5555
#define BUFLEN 8192

struct TestQuestion {
    string question;
    vector<string> answers;
    int ans_type; 
    vector<int> correct_answers;
    TestQuestion() : ans_type(0) {}
};

vector<TestQuestion> test_bank;

// --- Вспомогательные функции ---

string urlDecode(string str) {
    string res;
    for (int i = 0; i < (int)str.length(); ++i) {
        if (str[i] == '+') res += ' ';
        else if (str[i] == '%' && i + 2 < (int)str.length()) {
            res += (char)strtol(str.substr(i + 1, 2).c_str(), NULL, 16);
            i += 2;
        } else res += str[i];
    }
    return res;
}

// --- Проверка уникальности имени ---
bool isNameTaken(string user) {
    if (user.empty()) return false;
    ifstream log("answers.log");
    string line;
    string search_pattern = "User: " + user + " |";
    while (getline(log, line)) {
        if (line.find(search_pattern) == 0) { // Имя в начале строки
            return true;
        }
    }
    return false;
}

// --- Работа с логами и вопросами ---

void loadQuestions(string filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        TestQuestion q;
        string segment, ans_list, correct_list;
        getline(ss, q.question, ';');
        getline(ss, ans_list, ';');
        getline(ss, segment, ';');
        q.ans_type = atoi(segment.c_str());
        getline(ss, correct_list, ';');
        stringstream ss_ans(ans_list);
        while (getline(ss_ans, segment, ',')) q.answers.push_back(segment);
        stringstream ss_corr(correct_list);
        while (getline(ss_corr, segment, ',')) q.correct_answers.push_back(atoi(segment.c_str()));
        test_bank.push_back(q);
    }
}

void logAnswer(string user, int q_idx, string ans_val) {
    if (user.empty() || q_idx < 0 || q_idx >= (int)test_bank.size()) return;
    
    vector<int> u_idx;
    stringstream ss(ans_val);
    string seg;
    while (getline(ss, seg, ',')) u_idx.push_back(atoi(seg.c_str()));
    sort(u_idx.begin(), u_idx.end());

    vector<int> corr = test_bank[q_idx].correct_answers;
    sort(corr.begin(), corr.end());

    string status = (u_idx == corr && !u_idx.empty()) ? "CORRECT" : "INCORRECT";

    ofstream log("answers.log", ios::app);
    if (log.is_open()) {
        log << "User: " << user << " | Q: " << q_idx + 1 << " | Result: " << status << endl;
        log.close();
    }
}

bool isQuestionCorrect(string user, int q_idx) {
    ifstream log("answers.log");
    string line;
    bool correct = false;
    string target_user = "User: " + user;
    string target_q = "| Q: " + to_string(q_idx + 1) + " |";

    while (getline(log, line)) {
        if (line.find(target_user) != string::npos && line.find(target_q) != string::npos) {
            correct = (line.find("Result: CORRECT") != string::npos);
        }
    }
    return correct;
}

void sendBinaryFile(int sock, string filename, string contentType) {
    ifstream file(filename.c_str(), ios::binary | ios::ate);
    if (!file.is_open()) return;
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);
    vector<char> buffer((size_t)size);
    if (file.read(buffer.data(), size)) {
        stringstream head;
        head << "HTTP/1.1 200 OK\r\nContent-Type: " << contentType << "\r\n";
        head << "Content-Length: " << (int)size << "\r\nConnection: close\r\n\r\n";
        write(sock, head.str().c_str(), (int)head.str().length());
        write(sock, buffer.data(), (int)size);
    }
}

// --- Генерация HTML ---

string generatePage(string user, int q_idx, bool finished, bool name_error = false) {
    stringstream html;
    html << "<!DOCTYPE html><html><head><meta charset='utf-8'><style>"
         << "body { font-family: 'Verdana', sans-serif; background: #f0f2f5; display: flex; justify-content: center; padding: 40px; }"
         << ".card { background: white; padding: 30px; border-radius: 12px; box-shadow: 0 4px 15px rgba(0,0,0,0.1); width: 450px; }"
         << "h2 { color: #1c1e21; margin-top: 0; }"
         << "table { width: 100%; border-collapse: collapse; margin: 20px 0; }"
         << "th, td { padding: 12px; border: 1px solid #ddd; text-align: left; }"
         << "button { background: #1877f2; color: white; border: none; padding: 12px; border-radius: 6px; cursor: pointer; width: 100%; font-size: 16px; }"
         << ".error { color: #dc3545; background: #f8d7da; padding: 10px; border-radius: 6px; margin-bottom: 15px; border: 1px solid #f5c6cb; }"
         << ".correct { color: #28a745; font-weight: bold; } .wrong { color: #dc3545; font-weight: bold; }"
         << "</style></head><body><div class='card'>";

    if (finished) {
        html << "<h2>Результаты: " << user << "</h2><table>";
        int score = 0;
        for (int i = 0; i < (int)test_bank.size(); ++i) {
            bool ok = isQuestionCorrect(user, i);
            if (ok) score++;
            html << "<tr><td>Вопрос " << i+1 << "</td><td class='" << (ok ? "correct" : "wrong") << "'>" << (ok ? "Верно" : "Ошибка") << "</td></tr>";
        }
        html << "</table><h3>Итого: " << score << " из " << (int)test_bank.size() << "</h3><a href='/'><button>На главную</button></a>";
    } else if (q_idx == -1 || name_error) {
        html << "<h2>Тестирование</h2>";
        if (name_error) {
            html << "<div class='error'>Имя <b>" << user << "</b> уже занято. Пожалуйста, используйте другое (например, " << user << "2).</div>";
        }
        html << "<img src='/welcome.png' style='width:100%; border-radius:8px;'><br><br>"
             << "<form><input name='user' placeholder='Ваше имя' required style='width:94%; padding:12px; margin-bottom:15px; border:1px solid #ddd; border-radius:6px;'><br>"
             << "<input type='hidden' name='q' value='0'><button type='submit'>Начать тест</button></form>";
    } else {
        TestQuestion &q = test_bank[q_idx];
        html << "<small>Вопрос " << q_idx + 1 << " из " << (int)test_bank.size() << "</small><h3>" << q.question << "</h3><form>";
        for (int i = 0; i < (int)q.answers.size(); ++i) {
            string type = (q.ans_type == 1) ? "checkbox" : "radio";
            html << "<label style='display:block; margin-bottom:10px; padding:10px; background:#f8f9fa; border-radius:6px;'><input type='" << type << "' name='ans' value='" << i << "'> " << q.answers[i] << "</label>";
        }
        html << "<input type='hidden' name='user' value='" << user << "'><input type='hidden' name='prev_q' value='" << q_idx << "'>";
        if (q_idx < (int)test_bank.size() - 1) html << "<button name='q' value='" << q_idx + 1 << "'>Следующий вопрос</button>";
        else html << "<button name='finish' value='1' style='background:#28a745;'>Завершить</button>";
        html << "</form>";
    }
    html << "</div></body></html>";
    return html.str();
}

void WorkWithClient(int sock) {
    char buffer[BUFLEN];
    memset(buffer, 0, BUFLEN);
    int nbytes = (int)read(sock, buffer, BUFLEN);
    if (nbytes <= 0) return;

    string request(buffer);
    if (request.find("GET /welcome.png") != string::npos) {
        sendBinaryFile(sock, "welcome.png", "image/png");
        close(sock);
        return;
    }

    size_t start_pos = request.find("GET /?");
    map<string, string> params;
    if (start_pos != string::npos) {
        size_t end_pos = request.find(" ", start_pos + 6);
        string query = request.substr(start_pos + 6, end_pos - (start_pos + 6));
        stringstream ss(query);
        string item;
        while (getline(ss, item, '&')) {
            size_t p = item.find('=');
            if (p != string::npos) {
                string k = item.substr(0, p), v = item.substr(p + 1);
                if (params.count(k)) params[k] += "," + v; else params[k] = v;
            }
        }
    }

    string user = params.count("user") ? urlDecode(params["user"]) : "";
    int q_idx = params.count("q") ? stoi(params["q"]) : -1;
    bool fin = (params.count("finish") > 0);
    bool name_taken = false;

    // Проверка имени только при попытке начать тест (q=0 и нет предыдущих вопросов)
    if (q_idx == 0 && !params.count("prev_q")) {
        if (isNameTaken(user)) {
            name_taken = true;
        }
    }

    if (!name_taken && params.count("prev_q") && params.count("ans")) {
        logAnswer(user, atoi(params["prev_q"].c_str()), params["ans"]);
    }

    string content = generatePage(user, q_idx, fin, name_taken);
    stringstream resp;
    resp << "HTTP/1.1 200 OK\r\nContent-Length: " << (int)content.length() << "\r\nContent-Type: text/html; charset=utf-8\r\nConnection: close\r\n\r\n" << content;
    write(sock, resp.str().c_str(), (int)resp.str().length());
    close(sock);
}

int main() {
    loadQuestions("questions.txt");
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);
    while (true) {
        int ns = accept(sock, NULL, NULL);
        if (fork() == 0) { WorkWithClient(ns); exit(0); }
        close(ns);
    }
    return 0;
}
