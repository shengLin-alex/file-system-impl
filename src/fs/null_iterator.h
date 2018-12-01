#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include "node_iterator.h"

/**
 * @brief Inner class, empty iterator
 * 
 */
class NullIterator : public NodeIterator {
    public:

        /**
         * @brief Construct a new Null Iterator object
         * 
         * @param node 
         */
        NullIterator(Node* node): _node(node) {
        }

        void first() {
        }

        Node* currentItem() {
            return this->_node;
        }

        void next() {
        }

        bool isDone() {
            return true;
        }
            
    private:
        Node* _node;
};

#endif