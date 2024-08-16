#include<iostream>
#include<string>
#include<utility>

using namespace std;

template<class T>
struct node{
    T data;
    node<T> *next;
    node<T> *prev;
};

template<class T>
class Queue{
    public:
        Queue();
        ~Queue();
        node<T>* find(T x);
        void enqueue(T x);
        void dequeue(T x);
        T front();
        T back();
        bool isEmpty();
        void print_all();
    private:
        node<T> *head;
        node<T> *tail;
};

template<class T>
Queue<T>::Queue(){
    head = new node<T>;
    tail = new node<T>;
    head->next = tail;
    head->prev = nullptr;
    tail->next = nullptr;
    tail->prev = head;
}

template<class T>
Queue<T>::~Queue(){
    node<T> *p;
    while(head->next!=tail){
        p = head->next;
        head->next = p->next;
        delete p;
    }
    delete head;
    delete tail;
}

template<class T>
node<T>* Queue<T>::find(T x){
    node<T> *p = head->next;
    while(p!=tail && p->data!=x){
        p = p->next;
    }
    return p;
}

template<class T>
void Queue<T>::enqueue(T x){
    node<T> *p = new node<T>;
    p->data = x;
    p->next = tail;
    p->prev = tail->prev;
    tail->prev->next = p;
    tail->prev = p;
}

template<class T>
void Queue<T>::dequeue(T x){
    node<T> *p = find(x);
    if(p!=tail){
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
    }
}

template<class T>
T Queue<T>::front(){
    node<T> *p = head->next;
    if(p!=tail){
        return p->data;
    }
    return 0;
}

template<class T>
T Queue<T>::back(){
    node<T> *p = tail->prev;
    if(p!=head){
        return p->data;
    }
    return 0;
}

template<class T>
bool Queue<T>::isEmpty(){
    return head->next==tail;
}

template<class T>
void Queue<T>::print_all(){
    node<T> *p = head->next;
    while(p!=tail){
        cout<<p->data<<" ";
        p = p->next;
    }
    cout<<endl;
}

int main(){
    Queue<string> q;
    q.enqueue("a");
    q.enqueue("b");
    q.enqueue("c");
    q.print_all();
    
    cout<<q.back()<<endl;
    q.dequeue("b");
    q.print_all();

    return 0;
}