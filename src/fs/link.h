#ifndef LINK_H
#define LINK_H

#include "node.h"

/**
 * @brief Link object, a proxy class for node object.
 * 
 */
class Link : public Node {
    public:

        /**
         * @brief Construct a new Link object
         * 
         * @param path The link object path
         * @param node The node that link object linked.
         */
        Link(const char* path, Node* node = nullptr) : Node(path) {
            if (!S_ISLNK(this->_st.st_mode)) {
                throw std::string("Path of constructor does not correspond with class.");
            }

            this->addLink(node);
        }

        /**
         * @brief Add a link to this link object
         * 
         * @param node 
         */
        void addLink(Node* node) {
            _source = node;
        }

        /**
         * @brief Get the Source node
         * 
         * @return Node* 
         */
        Node* getSource() {
            return _source;
        }

        /**
         * @brief Accept visitor
         * 
         * @param visitor 
         */
        void accept(NodeVisitor* visitor) {
            visitor->visitLink(this);
        }

    private:

        /**
         * @brief The source node that link object linked.
         * 
         */
        Node* _source;
};

#endif
