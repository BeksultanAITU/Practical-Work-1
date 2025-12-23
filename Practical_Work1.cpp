#include <iostream>
#include <cstdlib>  
#include <ctime>    
#include <climits>  
#include <omp.h>
#include <chrono>   // Для измерения времени

using namespace std;

int main() {
    // Часть 1: Работа с массивами
    cout << "Task 1: Part 1 - Array Operations" << endl;

    // Ввод размера массива
    int N;
    cout << "Enter the size of the array: ";
    cin >> N;

    // Создаём массив из N элементов
    int* arr = new int[N];
    srand(time(0)); // Инициализация генератора случайных чисел

    // Заполняем массив случайными числами от 1 до 100
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100 + 1;  
    }

    // Инициализируем переменные для поиска минимума и максимума
    int min = INT_MAX, max = INT_MIN;

    // Ищем минимум и максимум
    for (int i = 0; i < N; i++) {
        if (arr[i] < min) min = arr[i];  
        if (arr[i] > max) max = arr[i];  
    }

    // Выводим массив и найденные минимальное и максимальное значения
    cout << "Array: ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Minimum value: " << min << endl;
    cout << "Maximum value: " << max << endl;

    // Часть 2: Параллелизация с использованием OpenMP
    cout << "\nTask 1: Part 2 - Parallelization with OpenMP" << endl;

    // Последовательная реализация для поиска минимума и максимума
    auto start_seq = chrono::high_resolution_clock::now();

    int min_seq = INT_MAX, max_seq = INT_MIN;
    for (int i = 0; i < N; i++) {
        if (arr[i] < min_seq) min_seq = arr[i];
        if (arr[i] > max_seq) max_seq = arr[i];
    }

    auto end_seq = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_seq = end_seq - start_seq;

    cout << "Sequential minimum: " << min_seq << endl;
    cout << "Sequential maximum: " << max_seq << endl;
    cout << "Sequential execution time: " << duration_seq.count() << " seconds" << endl;

    // Параллельная реализация с OpenMP
    auto start_parallel = chrono::high_resolution_clock::now();

    int min_parallel = INT_MAX, max_parallel = INT_MIN;

    #pragma omp parallel for reduction(min: min_parallel) reduction(max: max_parallel)
    for (int i = 0; i < N; i++) {
        if (arr[i] < min_parallel) min_parallel = arr[i];
        if (arr[i] > max_parallel) max_parallel = arr[i];
    }

    auto end_parallel = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_parallel = end_parallel - start_parallel;

    cout << "Parallel minimum: " << min_parallel << endl;
    cout << "Parallel maximum: " << max_parallel << endl;
    cout << "Parallel execution time: " << duration_parallel.count() << " seconds" << endl;

    // Часть 3: Работа со структурами данных
    cout << "\nTask 2: Part 1 - Data Structures (Linked List, Stack, Queue)" << endl;

    // Реализация односвязного списка
    struct Node {
        int data;
        Node* next;
    };

    class LinkedList {
    public:
        Node* head;

        LinkedList() {
            head = nullptr;
        }

        void addFirst(int value) {
            Node* newNode = new Node();
            newNode->data = value;
            newNode->next = head;
            head = newNode;
        }

        void removeFirst() {
            if (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

        bool search(int value) {
            Node* temp = head;
            while (temp != nullptr) {
                if (temp->data == value) {
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }

        void printList() {
            Node* temp = head;
            while (temp != nullptr) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    };

    // Создаём список и выполняем операции
    LinkedList list;
    list.addFirst(10);
    list.addFirst(20);
    list.addFirst(30);
    cout << "Linked List: ";
    list.printList();
    list.removeFirst();
    cout << "Linked List after removeFirst: ";
    list.printList();

    if (list.search(20)) {
        cout << "Found 20 in the list." << endl;
    } else {
        cout << "20 not found in the list." << endl;
    }

    // Стек
    class Stack {
    private:
        int* arr;
        int top;
        int capacity;

    public:
        Stack(int size) {
            arr = new int[size];
            capacity = size;
            top = -1;
        }

        void push(int value) {
            if (top < capacity - 1) {
                arr[++top] = value;
            } else {
                cout << "Stack Overflow" << endl;
            }
        }

        int pop() {
            if (top >= 0) {
                return arr[top--];
            } else {
                cout << "Stack Underflow" << endl;
                return -1;
            }
        }

        bool isEmpty() {
            return top == -1;
        }

        ~Stack() {
            delete[] arr;
        }
    };

    Stack s(5);
    s.push(10);
    s.push(20);
    cout << "Pop from stack: " << s.pop() << endl;

    // Очередь
    class Queue {
    private:
        int* arr;
        int front, rear, size, capacity;

    public:
        Queue(int cap) {
            capacity = cap;
            arr = new int[capacity];
            front = 0;
            rear = -1;
            size = 0;
        }

        void enqueue(int value) {
            if (size < capacity) {
                rear = (rear + 1) % capacity;
                arr[rear] = value;
                size++;
            } else {
                cout << "Queue Overflow" << endl;
            }
        }

        int dequeue() {
            if (size > 0) {
                int val = arr[front];
                front = (front + 1) % capacity;
                size--;
                return val;
            } else {
                cout << "Queue Underflow" << endl;
                return -1;
            }
        }

        bool isEmpty() {
            return size == 0;
        }

        ~Queue() {
            delete[] arr;
        }
    };

    Queue q(5);
    q.enqueue(10);
    q.enqueue(20);
    cout << "Dequeue from queue: " << q.dequeue() << endl;

    // Часть 4: Динамическая память и указатели
    cout << "\nTask 3: Part 1 - Dynamic Array with Pointers" << endl;

    // Создание динамического массива с помощью указателей
    int* dynamicArr = new int[N];

    // Заполнение массива случайными числами
    for (int i = 0; i < N; i++) {
        dynamicArr[i] = rand() % 100 + 1;
    }

    // Вывод массива
    cout << "Dynamic Array: ";
    for (int i = 0; i < N; i++) {
        cout << dynamicArr[i] << " ";
    }
    cout << endl;

    // Освобождение памяти
    delete[] dynamicArr;

    // Часть 5: Параллельный подсчёт среднего значения
    cout << "\nTask 3: Part 2 - Parallel Average Calculation with OpenMP" << endl;

    // Параллельный подсчёт суммы и среднего
    int* arr2 = new int[N];
    for (int i = 0; i < N; i++) {
        arr2[i] = rand() % 100 + 1;
    }

    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += arr2[i];
    }

    double average = static_cast<double>(sum) / N;
    cout << "Average: " << average << endl;

    delete[] arr2;

    return 0;
}
