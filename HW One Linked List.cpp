#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node* next;

    Node() = default;

    Node(const T& data) {
        this->data = data;
        this->next = nullptr;
    }
};

template <typename T>
class OneLinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
public:
    OneLinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void AddToHead(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
    }

    void AddToTail(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void DeleteFromHead() {
        if (head == nullptr) return;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
    }

    void DeleteFromTail() {
        if (tail == nullptr) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
    }

    void DeleteAll() {
        while (head != nullptr) {
            DeleteFromHead();
        }
    }

    void Show() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // task 2 practic

    void InsertAtindex(T value, int index) {
        if (index < 0) return;
        if (index == 0) {
            AddToHead(value);
            return;
        }
        Node<T>* newNode = new Node<T>(value);
        Node<T>* temp = head;
        for (int i = 1; i < index && temp != nullptr; ++i) {
            temp = temp->next;
        }
        if (temp == nullptr) return;
        newNode->next = temp->next;
        temp->next = newNode;
        if (newNode->next == nullptr) {
            tail = newNode;
        }
    }

    void DeleteAtindex(int index) {
        if (index < 0 || head == nullptr) return;
        if (index == 0) {
            DeleteFromHead();
            return;
        }
        Node<T>* temp = head;
        for (int i = 1; i < index && temp->next != nullptr; ++i) {
            temp = temp->next;
        }
        if (temp->next == nullptr) return;
        Node<T>* nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        if (nodeToDelete == tail) {
            tail = temp;
        }
        delete nodeToDelete;
    }

    int Search(T value) const {
        Node<T>* temp = head;
        int index = 0;
        while (temp != nullptr) {
            if (temp->data == value) {
                return index;
            }
            temp = temp->next;
            ++index;
        }
        return NULL;
    }

    int SearchAndReplace(T oldValue, T newValue) {
        Node<T>* temp = head;
        int count = 0;
        while (temp != nullptr) {
            if (temp->data == oldValue) {
                temp->data = newValue;
                ++count;
            }
            temp = temp->next;
        }
        return count > 0 ? count : -1;
    }

    void Reverse() {
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;
        tail = head;
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    ~OneLinkedList()
    {
        DeleteAll();
    }
};


int main() {
    OneLinkedList<int> list;
    list.AddToHead(1);
    list.AddToTail(2);
    list.AddToTail(3);
    list.Show();
    list.InsertAtindex(4, 2);
    list.Show();
    list.DeleteAtindex(1);
    list.Show();
    
    cout << "Index of 4th: " << list.Search(4) << endl;
    cout << "Replacements made: " << list.SearchAndReplace(4, 5) << endl;
    
    list.Show();
    list.Reverse();
    list.Show();
    list.DeleteAll();
    list.Show();
    return 0;
}

/*
1 2 3
1 2 4 3
1 4 3
Index of 4th: 1
Replacements made: 1
1 5 3
3 5 1


C:\Users\David\source\repos\HW One Linked List\x64\Debug\HW One Linked List.exe (процесс 17916) завершил работу с кодом 0 (0x0).
Нажмите любую клавишу, чтобы закрыть это окно:


*/