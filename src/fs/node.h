#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <vector>
#include "node_iterator.h"
#include "node_visitor.h"

/**
 * @brief The node object, abstract class for the file and folder
 * 
 */
class Node {

    public:

        /**
         * @brief Construct a new Node object
         * 
         * @param path 
         * @throw If lstat not found.
         */
        explicit Node(const char* path): _path(path), _parent(nullptr), _pathString(std::string(path)) {
            if (lstat(_path, &_st) != 0) {
                throw std::string("No such file or directory.");
            }
        }

        /**
         * @brief Destroy the Node object
         * 
         */
        virtual ~Node() {

        }

        /**
         * @brief Return stat size
         * 
         * @return int 
         */
        int size() const {
            return _st.st_size;
        }

        /**
         * @brief Return node's info content
         * 
         * @return int 
         */
        virtual int infoContent() const {
            return this->size();
        }

        /**
         * @brief Add child node, not implement, default throw.
         * 
         * @param node 
         */
        virtual void add(Node* node) {
            throw std::string("unable to add");
        }

        /**
         * @brief Get child node number, not implement, default throw.
         * 
         * @return int 
         */
        virtual int numberOfChildren() const {
            throw std::string("number of children: not applicable");
        }

        /**
         * @brief Get the node name, folder or file.
         * 
         * @return std::string 
         */
        virtual std::string name() const {
            std::string path = this->_pathString;
            std::size_t lastSlash = path.find_last_of("/");

            if (lastSlash == path.size() - 1) {
                lastSlash = path.substr(0, path.size() - 1).find_last_of("/");
            }

            std::string name = path.substr(lastSlash + 1);
            if (name.find("/") != std::string::npos) {

                return name.substr(0, name.size() - 1);
            }

            return name;
        }

        /**
         * @brief Get the node path, no name in this path.
         * 
         * @return std::string 
         */
        virtual std::string path() const {
            std::string path = this->_pathString;
            std::size_t lastSlash = path.find_last_of("/");

            if (lastSlash == path.size() - 1) {
                lastSlash = path.substr(0, path.size() - 1).find_last_of("/");
            }

            return path.substr(0, lastSlash + 1);
        }

        /**
         * @brief Find all matches path by specified node name, not implement, default throw.
         * 
         * @param nodeName 
         * @return std::string 
         */
        virtual std::string find(std::string nodeName) const {
            throw std::string("not implement.");
        }

        /**
         * @brief Find all matches node by specified node name, default do nothing.
         * 
         * @param nodeName 
         * @param results 
         */
        virtual void findNode(std::string nodeName, std::vector<Node*>& results) const {
        };

        /**
         * @brief accept visitor
         * 
         * @param visitor 
         */
        virtual void accept(NodeVisitor* visitor) {
            throw std::string("not implement.");
        }

        /**
         * @brief Create a NodeIterator
         * 
         * @return NodeIterator* 
         */
        virtual NodeIterator* createIterator() {
            return nullptr;
        }

        /**
         * @brief Get the Parent node.
         * 
         * @return Node* 
         */
        Node* getParent() const {
            return this->_parent;
        }

        /**
         * @brief Set the Parent node to this node.
         * 
         * @param node 
         */
        virtual void setParent(Node* node) {
            this->_parent = node;
        }

    private:
        Node* _parent;
        const char* _path;

    protected:
        struct stat _st{};
        std::string _pathString;
};

#endif
