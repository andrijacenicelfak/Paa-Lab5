using namespace std;
template <class T>
class Stack {
   public:
    Stack(int size);
    ~Stack();
    void push(T k);
    T pop();
    T topElement();
    bool isFull();

    bool isEmpty();

   private:
    int top;
    int size;
    T* st;
};
template <class T>
Stack<T>::~Stack() {
    delete[] st;
}
template <class T>
Stack<T>::Stack(int size) {
    this->size = size;
    top = -1;
    st = new T[size];
}
template <class T>
void Stack<T>::push(T k) {
    if (isFull()) return;
    st[++top] = k;
}
template <class T>
bool Stack<T>::isEmpty() {
    if (top == -1)
        return 1;
    else
        return 0;
}
template <class T>
bool Stack<T>::isFull() {
    if (top == (size - 1))
        return 1;
    else
        return 0;
}
template <class T>
T Stack<T>::pop() {
    T popped_element = st[top];
    top--;
    return popped_element;
}
template <class T>
T Stack<T>::topElement() {
    T top_element = st[top];

    return top_element;
}
