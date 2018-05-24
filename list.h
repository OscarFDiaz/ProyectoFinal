#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <exception>
#include <string>
#include <string>
#include <fstream>

#include "node.h"

class ListException : public std::exception {
    private:
        std::string msg;

    public:
        explicit ListException(const char* message) : msg(message) { }

        explicit ListException(const std::string& message) : msg(message) { }

        virtual ~ListException() throw () { }

        virtual const char* what() const throw () {
            return msg.c_str();
            }
    };

template<class T>
class List {
    private:
        Node<T>* anchor;

        void copyAll(const List<T>&);

    public:
        List();
        List(const List<T>&);
        ~List();

        bool isValidPos(Node<T>*);

        bool isEmpty();

        void insertData(Node<T>*, const T&);

        void deleteData(Node<T>*);

        Node<T>* getFirstPos();
        Node<T>* getLastPos();
        Node<T>* getPrevPos(Node<T>*);
        Node<T>* getNextPos(Node<T>*);

        Node<T>* findData(const T&);

        T retrieveData(Node<T>*);

        std::string toString();
        int listSize();

        void deleteAll();

        List<T>& operator = (const List<T>&);
        T operator [](int position);

};

template<class T>
void List<T>::copyAll(const List<T>& l) {
    Node<T> *aux(l.anchor), *lastInserted(nullptr), *newNode;

    while (aux!= nullptr) {
        newNode = new Node<T>(aux->getData());
        if(newNode == nullptr){
            throw ListException("memoria no disponible, crear nuevo nodo, intentar copiar");
        }

        if(lastInserted == nullptr){
            anchor = newNode;
        }else{
            lastInserted->setNext(newNode);
        }

        lastInserted = newNode;

        aux = aux->getNext();
        }
    }

template<class T>
bool List<T>::isValidPos(Node<T>* p)    {
    Node<T>* aux(anchor);

    while(aux != nullptr) {
        if(aux == p) {
            return true;
            }
        aux=aux->getNext();
        }
    return false;
    }

template<class T>
List<T>::List() : anchor(nullptr){ }

template<class T>
List<T>::List(const List<T>& l) : anchor(nullptr) {
    copyAll(l);
    }

template<class T>
List<T>::~List() {
    deleteAll();
    }

template<class T>
bool List<T>::isEmpty() {
    return anchor==nullptr;
    }

template<class T>
void List<T>::insertData(Node<T>* p, const T& e) {
    if(p!=nullptr and !isValidPos(p)) {
        throw ListException("Posicion invalida, tratando de insertar");
        }

    Node<T>* aux(new Node<T>(e));

    if(aux == nullptr) {
        throw ListException("memoria no disponible, crando nodo, tratano de insertar");
        }

    if(p == nullptr) {
        aux->setNext(anchor);
        anchor = aux;
        }
    else {
        aux->setNext(p->getNext());
        p->setNext(aux);
        }
    }

template<class T>
void List<T>::deleteData(Node<T>* p) {

    if(!isValidPos(p)) {
        throw ListException("La posicion es invalida, tratando de eliminar");
        }

    if(p == anchor) {
        anchor = anchor->getNext();
        }
    else {
        getPrevPos(p)->setNext(p->getNext());
        }
    delete p;
    }

template<class T>
Node<T>* List<T>::getFirstPos() {
    return anchor;
    }

template<class T>
Node<T>* List<T>::getLastPos() {
    if(isEmpty()) {
        return nullptr;
        }

    Node<T>* aux(anchor);

    while(aux->getNext() != nullptr) {
        aux = aux->getNext();
        }
    return aux;
    }

template<class T>
Node<T>* List<T>::getPrevPos(Node<T>* p) {
    Node<T>* aux(anchor);

    while(aux != nullptr and aux->getNext() != p) {
        aux = aux->getNext();
        }
    return aux;
    }

template<class T>
Node<T>* List<T>::getNextPos(Node<T>* p) {
    if(!isValidPos(p)) {
        return nullptr;
        }
    return p->getNext();
    }

template<class T>
Node<T>* List<T>::findData(const T& e) {
    Node<T>* aux(anchor);

    while(aux != nullptr and aux->getData()!= e) {
        aux = aux->getNext();
        }

    return aux;
    }

template<class T>
T List<T>::retrieveData(Node<T>* p) {
    if(!isValidPos(p)) {
        throw ListException("Posicion invalida, haciendo retrieve");
        }

    return p->getData();
    }

template<class T>
std::string List<T>::toString() {
    std::string result;
    Node<T>* aux(anchor);

    while(aux != nullptr) {
        result += aux->getData().toString() + "\n";

        aux = aux->getNext();
        }
    return result;
    }

template<class T>
int List<T>::listSize(){
    Node<T>* aux(anchor);
    int last = -1;
    while(aux != nullptr) {
        aux = aux->getNext();
        last++;
    }

    return last;
}

template<class T>
void List<T>::deleteAll() {
    Node<T>* aux;

    while(anchor != nullptr) {
        aux=anchor;

        anchor = anchor->getNext();

        delete aux;
        }
    }

template<class T>
List<T>& List<T>::operator=(const List<T>& other) {
    this->deleteAll();

    this->copyAll(other);

    return *this;

}

template<class T>
T List<T>::operator [](int position)
{
    if (isEmpty()) {
        throw ListException("La lista esta vacia");
    }

    Node<T>* aux(anchor);
    int cont = 0;
    while ((aux != nullptr) && (cont != position)) {
        aux = aux->getNext();
        cont++;
    }

    return aux->getData();
}

#endif // LIST_H_INCLUDED

