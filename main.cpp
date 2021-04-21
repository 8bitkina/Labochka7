//Описать структуру (класс) с именем STUDENT, содержащую следующие поля: номер(int); фамилия и инициалы(char *, string);
// номер группы  (аббревиатура специальности, курс) (char *, string); успеваемость (массив из пяти элементов(int)).
//Написать программу, выполняющую следующие действия:
// -Ввод данных  (файл, клавиатура на выбор пользователя).
// -Упорядочить  записи по возрастанию номера.
// -Вывод на экран фамилий и номеров групп для всех студентов, включенных в список, если средний балл студента больше К(float).
// -Вывод на экран фамилии и успеваемость для всех студентов, включенных в список, если группа равна N(char *, string).
//Если  информация не найдена, вывести соответствующее сообщение.
//Предусмотреть возможность редактирования элементов списка – удаление, добавление, изменение.

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

vector<int> null (5, 0);
class student {
    int Number;
    string FIO;
    string GroupNumber;
    vector<int> Marks;
public:
    student(const int &n = 0, const string &f = "", const string &g = "", const vector<int> &m = null) {
        Number = n;
        FIO = f;
        GroupNumber = g;
        Marks = m;
    }
    friend istream &operator >> (istream &in, student &a);
    friend ostream &operator << (ostream &out, student &a);
    bool operator < (const student &a) const {
        return Number < a.Number;
    }
    float GPA () {
        float sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += Marks[i];
        }
        return sum/5;
    }
    friend void IfGPA(float k, vector<student> list);
    friend void Group(string N, vector<student> list);
    int GetNumber() const {
        return Number;
    }
    void SetFIO (string s) {
        FIO = s;
    }
    void SetGN (string s) {
        GroupNumber = s;
    }
    void SetMarks (vector<int> a) {
        Marks = a;
    }
};

istream &operator >> (istream &in, student &a) {
    in >> a.Number >> a.FIO >> a.GroupNumber >> a.Marks[0] >> a.Marks[1] >> a.Marks[2] >> a.Marks[3] >> a.Marks[4];
    return in;
}
ostream &operator << (ostream &out, student &a) {
    out << a.Number << ' ' << a.FIO << ' ' << a.GroupNumber << ' ' << a.Marks[0] << ' ' << a.Marks[1] << ' ' << a.Marks[2] << ' ' << a.Marks[3] << ' ' << a.Marks[4];
    return out;
}

void IfGPA (float k, vector<student> list) {
    for (auto & i : list) {
        if (i.GPA() > k) {
            cout << i.FIO << ' ' << i.GroupNumber << endl;
        }
    }
}

void Group(string N, vector<student> list) {
    for (auto & i : list) {
        if (i.GroupNumber == N) {
            cout << i.FIO << ' ';
            for (int j = 0; j < 5; j++)
                cout << i.Marks[j] << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<student> list;
    int command;
    string s;
    student a;
    int num;
    while (command != 8) {
        cout << "1. Ввести список студентов" << endl;
        cout << "2. Добавить студента" << endl;
        cout << "3. Удалить студента с номером ..." << endl;
        cout << "4. Редактировать данные студента с номером ..." << endl;
        cout << "5. Средний балл балл больше ..." << endl;
        cout << "6. Студенты группы ..." << endl;
        cout << "7. Вывести список студентов" << endl;
        cout << "8. Выход" << endl;
        cin >> command;
        bool f = true;
        switch (command) {
            case 1:
                cout << "клавиатура или файл?" << endl;
                cin >> s;
                if (s == "клавиатура") {
                    cout << "Количество студентов?" << endl;
                    int n;
                    cin >> n;
                    list.resize(n);
                    for (auto & i : list) {
                        cin >> i;
                    }
                }
                else {
                    cout << "Имя файла?" << endl;
                    string FileName;
                    cin >> FileName;
                    ifstream in(FileName);
                    if (in.is_open()) {
                        while (!in.eof()) {
                            in >> a;
                            list.push_back(a);
                        }
                    }
                    else {
                        cout << "Файл не найден" << endl;
                    }
                }
                sort(list.begin(), list.end());
                break;
            case 2:
                cout << "Введите данные студента" << endl;;
                cin >> a;
                list.push_back(a);
                sort(list.begin(), list.end());
                break;
            case 3:
                cout << "Введите номер студента" << endl;
                cin >> num;
                for (int i = 0; i < list.size(); i++) {
                    if (list[i].GetNumber() == num) {
                        list.erase(list.begin() + i);
                        f = false;
                        break;
                    }
                }
                if (f)
                    cout << "Студента с таким номером нет" << endl;
                break;
            case 4:
                cout << "Введите номер студента" << endl;
                cin >> num;
                int j;
                for (int i = 0; i < list.size(); i++) {
                    if (list[i].GetNumber() == num) {
                        j = i;
                        f = false;
                        break;
                    }
                }
                if (f) {
                    cout << "Студента с таким номером нет" << endl;
                }
                else {
                    cout << "Какие данные редактировать (ФИО,  группа, оценки)?" << endl;
                    cin >> s;
                    cout << "Введите новые данные" << endl;
                    if (s == "ФИО") {
                        string nw;
                        cin >> nw;
                        list[j].SetFIO(nw);
                    }
                    if (s == "группа") {
                        string nw;
                        cin >> nw;
                        list[j].SetGN(nw);
                    }
                    if (s == "оценки") {
                        vector<int> nw(5);
                        for (auto i: nw)
                            cin >> i;
                        list[j].SetMarks(nw);
                    }
                }
                break;
            case 5:
                cout << "Введите балл" << endl;
                float k;
                cin >> k;
                IfGPA(k, list);
                break;
            case 6:
                cout << "Введите группу" << endl;
                cin >> s;
                Group(s, list);
                break;
            case 7:
                for (auto i : list)
                    cout << i << endl;
                break;
        }
    }
    return 0;
}
