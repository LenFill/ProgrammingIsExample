// Лабораторная работа 10
// Односвязный линейный список и задача учета автобусов.

#include <iostream>
#include <string>

using namespace std;

struct Bus {
    int number;
    string driver;
    int route;
};

ostream& operator<<(ostream& out, const Bus& bus)
{
    out << "Автобус " << bus.number << ", водитель: " << bus.driver
        << ", маршрут: " << bus.route;
    return out;
}

template <class T, class Key>
class SingleList {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;

public:
    SingleList()
    {
        head = nullptr;
    }

    ~SingleList()
    {
        clear();
    }

    bool empty() const
    {
        return head == nullptr;
    }

    void pushBack(const T& value)
    {
        Node* node = new Node{ value, nullptr };
        if (head == nullptr) {
            head = node;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) current = current->next;
        current->next = node;
    }

    T* find(Key key, Key(*getKey)(const T&))
    {
        Node* current = head;
        while (current != nullptr) {
            if (getKey(current->data) == key) return &current->data;
            current = current->next;
        }
        return nullptr;
    }

    bool remove(Key key, Key(*getKey)(const T&), T* removed = nullptr)
    {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr && getKey(current->data) != key) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) return false;

        if (removed != nullptr) *removed = current->data;

        if (previous == nullptr) head = current->next;
        else previous->next = current->next;

        delete current;
        return true;
    }

    bool insertAfter(Key key, const T& value, Key(*getKey)(const T&))
    {
        Node* current = head;
        while (current != nullptr && getKey(current->data) != key) {
            current = current->next;
        }

        if (current == nullptr) return false;

        Node* node = new Node{ value, current->next };
        current->next = node;
        return true;
    }

    bool insertBefore(Key key, const T& value, Key(*getKey)(const T&))
    {
        if (head == nullptr) return false;

        if (getKey(head->data) == key) {
            head = new Node{ value, head };
            return true;
        }

        Node* previous = head;
        Node* current = head->next;
        while (current != nullptr && getKey(current->data) != key) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) return false;

        previous->next = new Node{ value, current };
        return true;
    }

    void addSorted(const T& value, Key(*getKey)(const T&))
    {
        Node* node = new Node{ value, nullptr };

        if (head == nullptr || getKey(value) < getKey(head->data)) {
            node->next = head;
            head = node;
            return;
        }

        Node* current = head;
        while (current->next != nullptr && getKey(current->next->data) < getKey(value)) {
            current = current->next;
        }

        node->next = current->next;
        current->next = node;
    }

    void sort(Key(*getKey)(const T&))
    {
        SingleList<T, Key> sorted;

        Node* current = head;
        while (current != nullptr) {
            sorted.addSorted(current->data, getKey);
            current = current->next;
        }

        clear();
        head = sorted.head;
        sorted.head = nullptr;
    }

    void print(const string& title) const
    {
        cout << "\n" << title << endl;
        if (head == nullptr) {
            cout << "  Список пуст" << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            cout << "  " << current->data << endl;
            current = current->next;
        }
    }

    void clear()
    {
        while (head != nullptr) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }
};

int getBusNumber(const Bus& bus)
{
    return bus.number;
}

void moveBus(SingleList<Bus, int>& from, SingleList<Bus, int>& to, int number)
{
    Bus bus;
    if (from.remove(number, getBusNumber, &bus)) {
        to.pushBack(bus);
        cout << "Автобус " << number << " перемещен" << endl;
    }
    else {
        cout << "Автобус " << number << " не найден" << endl;
    }
}

int main()
{
    system("chcp 1251>nul");

    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 10 ===" << endl;

    SingleList<Bus, int> park;
    SingleList<Bus, int> route;

    park.pushBack({ 101, "Иванов И.И.", 5 });
    park.pushBack({ 215, "Петров П.П.", 12 });
    park.pushBack({ 307, "Сидоров С.С.", 7 });
    park.pushBack({ 118, "Кузнецов К.К.", 5 });

    park.insertAfter(101, { 150, "Орлов О.О.", 9 }, getBusNumber);
    park.insertBefore(307, { 260, "Морозов М.М.", 14 }, getBusNumber);
    park.print("Автобусы в парке после формирования списка:");

    Bus* found = park.find(215, getBusNumber);
    if (found != nullptr) cout << "\nНайден по номеру 215: " << *found << endl;

    moveBus(park, route, 215);
    moveBus(park, route, 118);
    park.print("Автобусы в парке:");
    route.print("Автобусы на маршруте:");

    moveBus(route, park, 215);
    park.sort(getBusNumber);
    route.sort(getBusNumber);

    park.print("Автобусы в парке после возвращения и сортировки:");
    route.print("Автобусы на маршруте после сортировки:");

    return 0;
}
