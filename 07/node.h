#ifndef NODE
#define NODE

#include <functional>
    using std::function;

template <typename T>
class Node {
    public:
        Node();
        Node(T value);

        void initialize(function<T(Node<T> *, Node<T> *)> action, Node<T> *a, Node<T> *b);
        void reset();
        T getValue();
    private:
        function<T(Node<T> *, Node<T> *)> action;
        Node<T> *a = 0;
        Node<T> *b = 0;

        T value;
        bool calculated;
};

#endif
