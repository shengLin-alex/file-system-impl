#ifndef FILE_H
#define FILE_H

#include "node.h"
#include "null_iterator.h"

/**
 * @brief File object
 * 
 */
class File : public Node {
    
    public:

        /**
         * @brief Construct a new File object
         * 
         * @param path The path of this file object.
         */
        File(const char* path) : Node(path) {
            if (!S_ISREG(this->_st.st_mode)) {
                throw std::string("Path of constructor does not correspond with class.");
            }
        }

        /**
         * @brief Find specified node name in file object,
         * it will return this file object node name, when
         * nodeName equals this->name().
         * 
         * @param nodeName The specified node name.
         * @return std::string 
         */
        std::string find(std::string nodeName) const {
            if (this->name() == nodeName) {
                return nodeName;
            } else {
                return "";
            }
        }

        /**
         * @brief Accept Visitor
         * 
         * @param visitor 
         */
        void accept(NodeVisitor* visitor) {
            visitor->visitFile(this);
        }

        /**
         * @brief Create a NullIterator.
         * 
         * @return NodeIterator* 
         */
        NodeIterator* createIterator() {
            return new NullIterator(this);
        }
};

#endif