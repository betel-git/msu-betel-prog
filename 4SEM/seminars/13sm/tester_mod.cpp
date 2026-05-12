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
#include <cctype>

using namespace std;

#define PORT 5555
#define BUFLEN 8192

struct TestQuestion {
    string question;
    vector<string> answers;
    int ans_type;          // 0 - radio, 1 - checkbox, 2 - text free, 3 - text with check
    vector<int> correct_answers;      // для radio/checkbox (индексы)
    vector<string> correct_texts;     // для текстовых с проверкой (эталоны)
    //TestQuestion() : ans_type(0) {}
};

vector<TestQuestion> test_bank;


// русификация, так сказать
string urlDecode(string str) {
    string res;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '+') res += ' ';
        else if (str[i] == '%' && i + 2 < str.length()) {
            char hex[3] = {str[i+1], str[i+2], 0};
            res += (char)strtol(hex, NULL, 16);
            i += 2;
        } else res += str[i];
    }
    return res;
}

// удаляет пробелы по краям строки
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

// переводит строку в нижний регистр
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// проверка уникальности имени
bool isNameTaken(string user) {
    if (user.empty()) return false;
    ifstream log("answers.log");
    string line;
    string search_pattern = "User: " + user + " |";
    while (getline(log, line)) {
        if (line.find(search_pattern) == 0)
            return true;
    }
    return false;
}

// работа с логами и вопросами
void loadQuestions(string filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        TestQuestion q;
        string question, ans_list, type_str, correct_str;
        getline(ss, q.question, ';');
        getline(ss, ans_list, ';');
        getline(ss, type_str, ';');
        getline(ss, correct_str, ';');
        q.ans_type = atoi(type_str.c_str());

        // разбор вариантов ответов (для radio/checkbox)
        if (!ans_list.empty()) {
            stringstream ss_ans(ans_list);
            string seg;
            while (getline(ss_ans, seg, ','))
                q.answers.push_back(seg);
        }

        if (q.ans_type == 0 || q.ans_type == 1) {
            // числовые правильные ответы
            stringstream ss_corr(correct_str);
            string seg;
            while (getline(ss_corr, seg, ','))
                q.correct_answers.push_back(atoi(seg.c_str()));
        } else if (q.ans_type == 3) {
            // текстовые эталоны, разделённые '|'
            stringstream ss_corr(correct_str);
            string seg;
            while (getline(ss_corr, seg, '|'))
                q.correct_texts.push_back(trim(seg));
        }
        // для ans_type == 2 правильных ответов нет
        test_bank.push_back(q);
    }
}

// получает предыдущий текстовый ответ пользователя на вопрос
string getAnswerText(string user, int q_idx) {
    if (user.empty() || q_idx < 0 || q_idx >= (int)test_bank.size()) return "";
    ifstream log("answers.log");
    string line;
    string target_user = "User: " + user;
    string target_q = "| Q: " + to_string(q_idx + 1) + " |";
    string last_answer = "";
    while (getline(log, line)) {
        if (line.find(target_user) != string::npos && line.find(target_q) != string::npos) {
            size_t pos = line.find("Answer: ");
            if (pos != string::npos) {
                last_answer = line.substr(pos + 8);
                // убрать возможный мусор в конце (например, перевод строки)
                last_answer = trim(last_answer);
            }
        }
    }
    return last_answer;
}

void logAnswer(string user, int q_idx, string ans_val) {
    if (user.empty() || q_idx < 0 || q_idx >= (int)test_bank.size()) return;

    TestQuestion& q = test_bank[q_idx];
    string status;
    string log_answer;

    if (q.ans_type == 0 || q.ans_type == 1) {
        // radio/checkbox: ans_val = "0,2,3"
        vector<int> u_idx;
        stringstream ss(ans_val);
        string seg;
        while (getline(ss, seg, ','))
            u_idx.push_back(atoi(seg.c_str()));
        sort(u_idx.begin(), u_idx.end());

        vector<int> corr = q.correct_answers;
        sort(corr.begin(), corr.end());

        status = (u_idx == corr && !u_idx.empty()) ? "CORRECT" : "INCORRECT";
        log_answer = ans_val;
    } else if (q.ans_type == 2) {
        // свободный текст – всегда засчитывается как верный
        status = "CORRECT";
        log_answer = ans_val;
    } else { // q.ans_type == 3
        // текстовый ответ с проверкой
        string user_ans = trim(ans_val);
        bool ok = false;
        for (const string& correct : q.correct_texts) {
            if (toLower(user_ans) == toLower(correct)) {
                ok = true;
                break;
            }
        }
        status = ok ? "CORRECT" : "INCORRECT";
        log_answer = ans_val;
    }

    ofstream log("answers.log", ios::app);
    if (log.is_open()) {
        log << "User: " << user << " | Q: " << q_idx + 1
            << " | Result: " << status
            << " | Answer: " << log_answer << endl;
        log.close();
    }
}

bool isQuestionCorrect(string user, int q_idx) {
    ifstream log("answers.log");
    string line;
    string target_user = "User: " + user;
    string target_q = "| Q: " + to_string(q_idx + 1) + " |";
    bool correct = false;

    while (getline(log, line)) {
        if (line.find(target_user) != string::npos && line.find(target_q) != string::npos) {
            if (line.find("Result: CORRECT") != string::npos)
                correct = true;
            else
                correct = false;
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

// парсинг параметров из строки (для GET и тела POST)
map<string, string> parseParams(const string& query) {
    map<string, string> params;
    stringstream ss(query);
    string item;
    while (getline(ss, item, '&')) {
        size_t p = item.find('=');
        if (p != string::npos) {
            string k = item.substr(0, p);
            string v = item.substr(p + 1);
            if (params.count(k))
                params[k] += "," + v;
            else
                params[k] = v;
        }
    }
    return params;
}

// генерация HTML
string generatePage(string user, int q_idx, bool finished, bool name_error = false) {
    stringstream html;
    html << "<!DOCTYPE html><html><head><meta charset='utf-8'><style>"
         << "body { font-family: 'Verdana', sans-serif; background: #f0f2f5; display: flex; justify-content: center; padding: 40px; }"
         << ".card { background: white; padding: 30px; border-radius: 12px; box-shadow: 0 4px 15px rgba(0,0,0,0.1); width: 450px; }"
         << "h2 { color: #1c1e21; margin-top: 0; }"
         << "table { width: 100%; border-collapse: collapse; margin: 20px 0; }"
         << "th, td { padding: 12px; border: 1px solid #ddd; text-align: left; }"
         << "button { background: #1877f2; color: white; border: none; padding: 12px; border-radius: 6px; cursor: pointer; width: 100%; font-size: 16px; }"
         << "textarea, input[type='text'] { width: 94%; padding: 12px; margin-bottom: 15px; border: 1px solid #ddd; border-radius: 6px; font-family: monospace; }"
         << ".error { color: #dc3545; background: #f8d7da; padding: 10px; border-radius: 6px; margin-bottom: 15px; border: 1px solid #f5c6cb; }"
         << ".correct { color: #28a745; font-weight: bold; } .wrong { color: #dc3545; font-weight: bold; }"
         << "</style></head><body><div class='card'>";

    if (finished) {
        html << "<h2>Результаты: " << user << "</h2>"
            << "<table style='width:100%; border-collapse: collapse; margin: 20px 0;'>"
            << "<thead><tr style='background:#e9ecef;'>"
            << "<th style='padding: 12px; border: 1px solid #dee2e6; text-align: left;'>Вопрос</th>"
            << "<th style='padding: 12px; border: 1px solid #dee2e6; text-align: left;'>Результат</th>"
            << "</tr></thead><tbody>";
        int score = 0;
        for (size_t i = 0; i < test_bank.size(); ++i) {
            bool ok = isQuestionCorrect(user, (int)i);
            if (ok) score++;
            string row_class = (i % 2 == 0) ? "background:#f8f9fa;" : "";

            // берём текст вопроса и экранируем HTML-символы
            string question_text = test_bank[i].question;
            size_t pos = 0;
            while ((pos = question_text.find("<", pos)) != string::npos) {
                question_text.replace(pos, 1, "&lt;");
                pos += 4;
            }
            pos = 0;
            while ((pos = question_text.find(">", pos)) != string::npos) {
                question_text.replace(pos, 1, "&gt;");
                pos += 4;
            }

            html << "<tr style='" << row_class << "'>"
                << "<td style='padding: 12px; border: 1px solid #dee2e6; word-break: break-word;'>" 
                << question_text << "</td>"
                << "<td style='padding: 12px; border: 1px solid #dee2e6;' class='" << (ok ? "correct" : "wrong") << "'>"
                << (ok ? "Верно" : "Ошибка") << "</td>"
                << "<tr>";
        }
        html << "</tbody></table>"
            << "<h3 style='margin-top: 20px;'>Итого: " << score << " из " << test_bank.size() << "</h3>"
            << "<a href='/'><button style='background:#1877f2; color:white; border:none; padding:12px; border-radius:6px; cursor:pointer; width:100%; font-size:16px;'>На главную</button></a>";
    } else if (q_idx == -1 || name_error) {
        html << "<h2>Тестирование</h2>";
        if (name_error)
            html << "<div class='error'>Имя <b>" << user << "</b> уже занято. Пожалуйста, используйте другое (например, " << user << "2).</div>";
        html << "<img src='/welcome.gif' style='width:100%; border-radius:8px;'><br><br>"
             << "<form method='get'><input name='user' placeholder='Ваше имя / псевдоним / никнейм' required style='width:94%; padding:12px; margin-bottom:15px; border:1px solid #ddd; border-radius:6px;'><br>"
             << "<input type='hidden' name='q' value='0'><button type='submit'>Начать тест</button></form>";
    } else {
        TestQuestion &q = test_bank[q_idx];
        html << "<small>Вопрос " << q_idx + 1 << " из " << test_bank.size() << "</small><h3>" << q.question << "</h3>";

        // выбираем метод формы: POST для текстовых вопросов (чтобы не обрезало длинный текст), GET для остальных
        string method = (q.ans_type == 2 || q.ans_type == 3) ? "post" : "get";
        html << "<form method='" << method << "'>";

        if (q.ans_type == 0 || q.ans_type == 1) {
            // radio / checkbox
            for (size_t i = 0; i < q.answers.size(); ++i) {
                string type = (q.ans_type == 1) ? "checkbox" : "radio";
                html << "<label style='display:block; margin-bottom:10px; padding:10px; background:#f8f9fa; border-radius:6px;'>"
                     << "<input type='" << type << "' name='ans' value='" << i << "'> " << q.answers[i] << "</label>";
            }
        } else {
            // текстовое поле (многострочное для удобства)
            string prev = getAnswerText(user, q_idx);
            html << "<textarea name='ans' rows='5' placeholder='Введите ваш ответ...'>" << prev << "</textarea>";
        }

        html << "<input type='hidden' name='user' value='" << user << "'>"
             << "<input type='hidden' name='prev_q' value='" << q_idx << "'>";

        if (q_idx < (int)test_bank.size() - 1)
            html << "<button name='q' value='" << q_idx + 1 << "'>Следующий вопрос</button>";
        else
            html << "<button name='finish' value='1' style='background:#28a745;'>Завершить</button>";

        html << "</form>";
    }
    html << "</div></body></html>";
    return html.str();
}

void WorkWithClient(int sock) {
    char buffer[BUFLEN];
    memset(buffer, 0, BUFLEN);
    int nbytes = (int)read(sock, buffer, BUFLEN - 1);
    if (nbytes <= 0) return;

    string request(buffer);
    // отделяем первую строку
    size_t first_line_end = request.find("\r\n");
    if (first_line_end == string::npos) return;
    string first_line = request.substr(0, first_line_end);

    // обработка запроса картинки
    if (request.find("GET /welcome.gif") != string::npos) {
        sendBinaryFile(sock, "welcome.gif", "image/gif");
        close(sock);
        return;
    }

    // определяем метод и путь
    string method, path, version;
    istringstream iss(first_line);
    iss >> method >> path >> version;

    map<string, string> params;
    string query_string;

    if (method == "GET") {
        // параметры в URL после '?'
        size_t qpos = path.find('?');
        if (qpos != string::npos) {
            query_string = path.substr(qpos + 1);
            params = parseParams(query_string);
        }
    } else if (method == "POST") {
        // найдём пустую строку, отделяющую заголовки от тела
        size_t body_start = request.find("\r\n\r\n");
        if (body_start == string::npos) {
            close(sock);
            return;
        }
        body_start += 4;
        string body = request.substr(body_start);
        // ищем Content-Length
        size_t cl_pos = request.find("Content-Length:");
        int content_length = 0;
        if (cl_pos != string::npos) {
            size_t end = request.find("\r\n", cl_pos);
            string cl_line = request.substr(cl_pos + 16, end - cl_pos - 16);
            content_length = atoi(cl_line.c_str());
        }

        params = parseParams(body);
    }

    // извлекаем параметры
    string user = params.count("user") ? urlDecode(params["user"]) : "";
    int q_idx = params.count("q") ? stoi(params["q"]) : -1;
    bool fin = (params.count("finish") > 0);
    bool name_taken = false;

    // проверка имени только при попытке начать тест (q=0 и нет предыдущего вопроса)
    if (q_idx == 0 && params.count("prev_q") == 0) {
        if (isNameTaken(user))
            name_taken = true;
    }

    // сохраняем ответ, если есть prev_q и ans
    if (!name_taken && params.count("prev_q") && params.count("ans")) {
        int prev_q = atoi(params["prev_q"].c_str());
        string ans_val = urlDecode(params["ans"]);
        logAnswer(user, prev_q, ans_val);
    }

    string content = generatePage(user, q_idx, fin, name_taken);
    stringstream resp;
    resp << "HTTP/1.1 200 OK\r\n"
         << "Content-Length: " << content.length() << "\r\n"
         << "Content-Type: text/html; charset=utf-8\r\n"
         << "Connection: close\r\n\r\n"
         << content;
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
    signal(SIGCHLD, SIG_IGN);
    while (true) {
        int ns = accept(sock, NULL, NULL);
        if (fork() == 0) {
            close(sock);
            WorkWithClient(ns);
            exit(0);
        }
        close(ns);
    }
    return 0;
}
