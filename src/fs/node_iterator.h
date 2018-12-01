#ifndef NODE_ITERATOR
#define NODE_ITERATOR

class Node;

/**
 * @brief NodeIterator interface
 * 
 */
class NodeIterator {
    public:
        virtual void first() = 0;
        virtual Node* currentItem() = 0;
        virtual void next() = 0;
        virtual bool isDone() = 0;
};

#endif