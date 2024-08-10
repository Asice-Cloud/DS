#include<iostream>
#include<string>
using namespace std;

template<class T>
struct node{
    T data;
    node<T> *next;
};

template<class T>
class List{
    public:
        List();
        ~List();
        void insert(T x);
        void remove(T x);
        void print_all();
        const List reverse();
    private:
        node<T> *head;
};

template<class T>
List<T>::List(){
    head = new node<T>;
    head->next = nullptr;
}

template<class T>
List<T>::~List(){
    node<T> *p;
    while(head->next!=nullptr){
        p = head->next;
        head->next = p->next;
        delete p;
    }
    delete head;
}

template<class T>
void List<T>::insert(T x){
    node<T> *p = new node<T>;
    p->data = x;
    p->next = head->next;
    head->next = p;
}

template<class T>
void List<T>::remove(T x){
    node<T> *p = head->next;
    node<T> *q = head;
    while(p!=nullptr && p->data!=x){
        q = p;
        p = p->next;
    }
    if(p!=nullptr){
        q->next = p->next;
        delete p;
    }
}

template<class T>
void List<T>::print_all(){
    node<T> *p = head->next;
    while(p!=nullptr){
        cout<<p->data<<" ";
        p = p->next;
    }
    cout<<endl;
}

template<class T>
const List<T> List<T>::reverse(){
    List<T> l;
    node<T> *p = head->next;
    while(p!=nullptr){
        l.insert(p->data);
        p = p->next;
    }
    return l;
}

int main(){
    List<string> l;
    l.insert("hello");
    l.insert("world");
    l.insert("this");
    l.insert("is");
    l.insert("a");
    l.insert("test");
    l.print_all();
    l.remove("world");
    l.remove("is");
    l.print_all();
    List<string> l2 = l.reverse();
    l2.print_all();
    return 0;
}