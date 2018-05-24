#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

template<class T>
class Node {

    private:
        T data;
        Node<T>* next;

    public:

        Node();
        Node(const T&);

        T getData();
        Node<T>* getNext();

        void setData(const T&);
        void setNext(Node<T>*);

    };

template<class T>
Node<T>::Node() : next(nullptr) { }

template<class T>
Node<T>::Node(const T& e) : data(e), next(nullptr) { }

template<class T>
T Node<T>::getData() {
    return data;
    }

template<class T>
Node<T>* Node<T>::getNext() {
    return next;
    }

template<class T>
void Node<T>::setData(const T& e) {
    data = e;
    }

template<class T>
void Node<T>::setNext(Node<T>* p) {
    next = p;
    }


#endif // NODE_H_INCLUDED
