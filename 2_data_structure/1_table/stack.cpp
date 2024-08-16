#include<iostream>
using namespace std;

template<class T>
struct node{
    T data;
    node<T> *next;
};

template<class T>
class Stack{
    public:
        Stack();
        ~Stack();
        void push(T x);
        void pop();
        int top();
        bool isEmpty();
    private:
        node<T> *head;
};

template<class T>
Stack<T>::Stack(){
    head = new node<T>;
    head->next = nullptr;
}

template<class T>
Stack<T>::~Stack(){
    node<T> *p;
    while(head->next!=nullptr){
        p = head->next;
        head->next = p->next;
        delete p;
    }
    delete head;
}

template<class T>
void Stack<T>::push(T x){
    node<T> *p = new node<T>;
    p->data = x;
    p->next = head->next;
    head->next = p;
}

template<class T>
void Stack<T>::pop(){
    node<T> *p = head->next;
    if(p!=nullptr){
        head->next = p->next;
        delete p;
    }
}

template<class T>
int Stack<T>::top(){
    node<T> *p = head->next;
    if(p!=nullptr){
        return p->data;
    }
    cout<<"Empty stack"<<endl;
    return 0;
}

template<class T>
bool Stack<T>::isEmpty(){
    return head->next==nullptr;
}

int main(){
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout<<s.top()<<endl;
    s.pop();
    cout<<s.top()<<endl;
    s.pop();
    cout<<s.top()<<endl;
    s.pop();
    cout<<s.isEmpty()<<endl;
    return 0;
}
