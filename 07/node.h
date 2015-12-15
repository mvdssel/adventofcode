#ifndef NODE
#define NODE

#include <functional>
    using std::function;

/**
 * A node with a value. The value is calculated based on the value of other nodes and a
 * specific action.
 */
template <typename T>
class Node {
    public:
        /**
         * Create an empty node
         */
        Node();
        /**
         * Create a leaf that is not dependant of other nodes
         */
        Node(T value);

        /**
         * Initialize a node whose value is dependent on other node(s)
         */
        void initialize(function<T(Node<T> *, Node<T> *)> action, Node<T> *a, Node<T> *b);
        /**
         * Reset the node so its value will be recalculated
         */
        void reset();
        /**
         * Get the value of the node (calculate if needed)
         */
        T getValue();
    private:
        /**
         * How is the value of the node calculated?
         */
        function<T(Node<T> *, Node<T> *)> action;
        /**
         * The nodes used to calculate this->value
         */
        Node<T> *a = 0;
        Node<T> *b = 0;
        /**
         * The value of the node
         */
        T value;
        /**
         * Indicates if the value of the node is already calculated
         */
        bool calculated;
};

#endif
