#include <iostream>
#include <string>
using namespace std;

struct Logger {
    void log(const string& message) const {
        cout << "[LOG]: " << message << endl;
    }

    void info(const string& message) const {
        cout << "[INFO]: " << message << endl;
    }

    void warn(const string& message) const {
        cout << "[WARN]: " << message << endl;
    }

    void error(const string& message) const {
        cout << "[ERROR]: " << message << endl;
    }
};

struct Node {
    int data;
    Node* next;

   // Node() = default;

    Node() : data(0), next(nullptr) {}; // без default тому що вказiвник потрiбно прописати самому для безпеки кода
};

class Stack {
private:
    Node* top;
    int size;
    Logger logger;
public:
    Stack() : top(nullptr), size(0) {}

    void push(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
        size++;
        logger.info("Pushed: " + to_string(value) + ", Stack size: " + to_string(size));
    }

    void pop() {
        if (top == nullptr) {
            logger.warn("Stack is empty, no elements to pop.");
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
        size--;
        logger.info("Popped, Stack size: " + to_string(size));
    }

    int getSize() {
        return size;
    }

    void print() {
        Node* arr = top;
        int count = 0;
        while (arr != nullptr) {
            cout << "Element " << count << " of one linked list: " << arr->data << endl;
            arr = arr->next;
            count++;
        }
        cout << endl;
    }

    Stack clone() const {
        Stack newStack;
        Node* temp = this->top;
        Stack tempStack;
        logger.log("Start cloning");
        while (temp) {
            tempStack.push(temp->data);
            logger.info("Pushed to tempStack: " + to_string(temp->data));
            temp = temp->next;
        }
        logger.log("Finished pushing to tempStack");
        temp = tempStack.top;
        while (temp) {
            newStack.push(temp->data);
            logger.info("Pushed to newStack: " + to_string(temp->data));
            temp = temp->next;
        }
        logger.log("Finished cloning");

        return newStack;
    }

    Stack operator+(const Stack& other) {
        Stack result;
        Node* current = this->top;
        logger.log("Start adding stacks");

        while (current != nullptr) {
            result.push(current->data);
            logger.info("Added from first stack: " + to_string(current->data));
            current = current->next;
        }

        Node* current2 = other.top;
        while (current2 != nullptr) {
            result.push(current2->data);
            logger.info("Added from second stack: " + to_string(current2->data));
            current2 = current2->next;
        }

        logger.log("Finished adding stacks");
        return result;
    }

    Stack operator*(const Stack& other) {
        Stack result;
        Node* current1 = this->top;
        logger.log("Start intersecting stacks");

        while (current1 != nullptr) {
            Node* current2 = other.top;
            while (current2 != nullptr) {
                if (current1->data == current2->data) {
                    result.push(current1->data);
                    logger.info("Found common element: " + to_string(current1->data));
                    break;
                }
                current2 = current2->next;
            }
            current1 = current1->next;
        }

        logger.log("Finished intersecting stacks");
        return result;
    }
};

int main() {
    Stack stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    Stack stack2;
    stack2.push(10);
    stack2.push(20);
    stack2.push(30);

    
    Stack resultAdd = stack1 + stack2;
    resultAdd.print();
    
    Stack resultMul = stack1 * stack2;
    resultMul.print();
    
    Stack clonedStack = stack1.clone();
    clonedStack.print();
    
    return 0;
}

/*
[INFO]: Pushed: 1, Stack size: 1
[INFO]: Pushed: 2, Stack size: 2
[INFO]: Pushed: 3, Stack size: 3
[INFO]: Pushed: 10, Stack size: 1
[INFO]: Pushed: 20, Stack size: 2
[INFO]: Pushed: 30, Stack size: 3
[LOG]: Start adding stacks
[INFO]: Pushed: 3, Stack size: 1
[INFO]: Added from first stack: 3
[INFO]: Pushed: 2, Stack size: 2
[INFO]: Added from first stack: 2
[INFO]: Pushed: 1, Stack size: 3
[INFO]: Added from first stack: 1
[INFO]: Pushed: 30, Stack size: 4
[INFO]: Added from second stack: 30
[INFO]: Pushed: 20, Stack size: 5
[INFO]: Added from second stack: 20
[INFO]: Pushed: 10, Stack size: 6
[INFO]: Added from second stack: 10
[LOG]: Finished adding stacks
Element 0 of one linked list: 10
Element 1 of one linked list: 20
Element 2 of one linked list: 30
Element 3 of one linked list: 1
Element 4 of one linked list: 2
Element 5 of one linked list: 3

[LOG]: Start intersecting stacks
[LOG]: Finished intersecting stacks

[LOG]: Start cloning
[INFO]: Pushed: 3, Stack size: 1
[INFO]: Pushed to tempStack: 3
[INFO]: Pushed: 2, Stack size: 2
[INFO]: Pushed to tempStack: 2
[INFO]: Pushed: 1, Stack size: 3
[INFO]: Pushed to tempStack: 1
[LOG]: Finished pushing to tempStack
[INFO]: Pushed: 1, Stack size: 1
[INFO]: Pushed to newStack: 1
[INFO]: Pushed: 2, Stack size: 2
[INFO]: Pushed to newStack: 2
[INFO]: Pushed: 3, Stack size: 3
[INFO]: Pushed to newStack: 3
[LOG]: Finished cloning
Element 0 of one linked list: 3
Element 1 of one linked list: 2
Element 2 of one linked list: 1


C:\Users\David\source\repos\HW One Linked List\x64\Debug\HW One Linked List.exe (процесс 2452) завершил работу с кодом 0 (0x0).
Нажмите любую клавишу, чтобы закрыть это окно:

*/