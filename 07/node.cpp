#include "node.h"
#include <iostream>

template <typename T>
Node<T>::Node() { }

template <typename T>
Node<T>::Node(T value) {
    this->value = value;
    this->calculated = true;
}

template <typename T>
void Node<T>::initialize(function<T(Node<T> *, Node<T> *)> action, Node<T> *a, Node<T> *b) {
    this->action = action;
    this->a = a;
    this->b = b;
    this->calculated = false;
}

template <typename T>
void Node<T>::reset() {
    this->calculated = false;
}

template <typename T>
T Node<T>::getValue() {
    if(calculated) return value;
    value = action(a, b);
    calculated = true;
    return value;
}
