#include <iostream>
#include <random>
#include <string>
using namespace std;

struct Queue {
    int studentId;
    Queue* next;
};

Queue* create_queue() {
    return nullptr;
}

Queue* add_to_queue(Queue* head, int id) {
    Queue* new_elem = new Queue;
    new_elem->studentId = id;
    new_elem->next = nullptr;

    if (head == nullptr) {
        return new_elem;
    }

    Queue* p = head;
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = new_elem;
    return head;
}

Queue* remove_from_queue(Queue* head) {
    if (head == nullptr) {
        return nullptr;
    }
    Queue* temp = head->next;
    delete head;
    return temp;
}

void display_queue(Queue* head) {
    if (head == nullptr) {
        cout << "Очередь пуста\n";
        return;
    }
    cout << "Текущая очередь: ";
    Queue* p = head;
    while (p != nullptr) {
        cout << "Студент_" << p->studentId;
        if (p->next != nullptr) {
            cout << " -> ";
        }
        p = p->next;
    }
    cout << "\n";
}

int get_queue_size(Queue* head) {
    int count = 0;
    Queue* p = head;
    while (p != nullptr) {
        count++;
        p = p->next;
    }
    return count;
}

void clear_queue(Queue* head) {
    while (head != nullptr) {
        head = remove_from_queue(head);
    }
}

int main() {
    srand(time(nullptr));
    Queue* washMachineQueue = create_queue();
    int studentCounter = 1;
    bool running = true;
    int serviceCount = 0;

    cout << "========== ОЧЕРЕДЬ НА СТИРАЛЬНУЮ МАШИНУ ==========\n";
    cout << "Нажмите Enter для выполнения события, введите 'stop' для выхода\n\n";

    while (running) {
        string input;
        cout << "Команда (Enter/stop): ";
        getline(cin, input);

        if (input == "stop") {
            cout << "\nОстановка программы...\n";
            running = false;
            break;
        }

        int event = rand() % 2;

        if (event == 0) {
            cout << "\n*** СОБЫТИЕ: Студент встал в очередь ***\n";
            washMachineQueue = add_to_queue(washMachineQueue, studentCounter);
            cout << "Студент_" << studentCounter << " добавлен в очередь\n";
            studentCounter++;
        } else {
            if (get_queue_size(washMachineQueue) == 0) {
                cout << "\n*** СОБЫТИЕ: Попытка обслуживания (очередь пуста) ***\n";
                cout << "Никого нет для обслуживания\n";
            } else {
                cout << "\n*** СОБЫТИЕ: Обслуживание ***\n";
                Queue* temp = washMachineQueue;
                cout << "Студент_" << temp->studentId << " начал пользоваться стиральной машиной\n";
                washMachineQueue = remove_from_queue(washMachineQueue);
                serviceCount++;
            }
        }

        display_queue(washMachineQueue);
        cout << "Статистика: обслужено студентов = " << serviceCount << "\n";
        cout << "\n";
    }

    cout << "\nИтоговая статистика:\n";
    cout << "Всего обслужено: " << serviceCount << "\n";
    cout << "Осталось в очереди: " << get_queue_size(washMachineQueue) << "\n";

    clear_queue(washMachineQueue);

    return 0;
}
