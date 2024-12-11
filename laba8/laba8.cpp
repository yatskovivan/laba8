#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Discipline {
    string name; 
    int grade;   
};
struct Student {
    string studentsname;
    vector<Discipline> disciplines; 
};
struct Node {
    Student student; 
    Node* next;      
    Node* prev;     
    Node(const Student& student) : student(student), next(this), prev(this) {}
};
class list1 {
private:
    Node* head;
public:
    list1() : head(nullptr) {}
    void addStudent(const Student& student) {
        Node* newNode = new Node(student);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
    }
    int counter2() {
        if (head == nullptr) return 0;
        int count = 0;
        Node* current = head;
        do {
            for (const auto& discipline : current->student.disciplines) {
                if (discipline.grade < 3) {
                    count++;
                    break; 
                }
            }
            current = current->next;
        } while (current != head);
        return count;
    }
    int counter5() {
        if (head == nullptr) return 0;
        int count = 0;
        Node* current = head;
        do {
            bool allExcellent = true;
            for (const auto& discipline : current->student.disciplines) {
                if (discipline.grade != 5) {
                    allExcellent = false;
                    break;
                }
            }
            if (allExcellent) count++;
            current = current->next;
        } while (current != head);
        return count;
    }
    void displayStudents() {
        if (head == nullptr) {
            cout << "Список пуст." << endl;
            return;
        }
        Node* current = head;
        do {
            cout << "ФИО: " << current->student.studentsname << endl;
            for (const auto& discipline : current->student.disciplines) {
                cout << "  Дисциплина: " << discipline.name << ", Оценка: " << discipline.grade << endl;
            }
            current = current->next;
        } while (current != head);
    }
    ~list1() {
        if (head == nullptr) return;

        Node* current = head;
        do {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        } while (current != head);
    }
};
int main() {
    setlocale(LC_ALL, "Russian");
    list1 studentList;
    int n;
    cout << "Введите количество студентов: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin.ignore();
        Student student;
        cout << "Введите ФИО студента " << i + 1 << ": ";
        getline(cin, student.studentsname);
        int countersubj;
        cout << "Введите количество дисциплин для студента: ";
        cin >> countersubj;
        for (int j = 0; j < countersubj; j++) {
            Discipline discipline;
            cin.ignore();
            cout << "Введите название дисциплины " << j + 1 << ": ";
            getline(cin, discipline.name);
            cout << "Введите оценку по дисциплине " << j + 1 << ": ";
            cin >> discipline.grade;
            student.disciplines.push_back(discipline);
        }
        studentList.addStudent(student);
    }
    cout << "\nСписок студентов:\n";
    studentList.displayStudents();
    cout << "\nКоличество студентов с неудовлетворительной оценкой: "
        << studentList.counter2() << endl;
    cout << "Количество студентов, сдавших все экзамены на 5: "
        << studentList.counter5() << endl;
    return 0;
}