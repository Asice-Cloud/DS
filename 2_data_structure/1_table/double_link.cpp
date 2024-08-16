#include<iostream>
#include<string>
using namespace std;

template<class T>
struct node{
    T data;
    node<T> *next;
    node<T> *prev;
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
    head->prev = nullptr;
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
    p->prev = head;
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
    List<int> l;
    l.insert(1);
    l.insert(2);
    l.insert(3);
    l.insert(4);
    l.insert(5);
    l.print_all();
    l.remove(3);
    l.print_all();
    List<int> l2 = l.reverse();
    l2.print_all();

    List<string> l3;
    l3.insert("hello");
    l3.insert("world");
    l3.insert("this");
    l3.insert("is");
    l3.insert("a");
    l3.insert("test");
    l3.print_all();
    l3.remove("world");
    l3.remove("is");
    l3.print_all();
    List<string> l4 = l3.reverse();
    l4.print_all();

    return 0;
}
