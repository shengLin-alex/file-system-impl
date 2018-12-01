#ifndef FOLDER_H
#define FOLDER_H

#include "node.h"
#include <vector>
#include <map>
#include <algorithm>

/**
 * @brief The folder object
 * 
 */
class Folder : public Node {

    public:

        /**
         * @brief Inner class, the iterator of folder
         * 
         */
        class FolderIterator : public NodeIterator {
            public:

                /**
                 * @brief Construct a new Folder Iterator object
                 * 
                 * @param folder
                 */
                FolderIterator(Folder* folder): _folder(folder) {
                }

                /**
                 * @brief Point to first iterator of _children
                 * 
                 */
                void first() {
                    _it = _folder->_children.begin();
                }

                /**
                 * @brief Get current item from current iterator
                 * 
                 * @return Node* 
                 */
                Node* currentItem() {
                    if (isDone()) {
                        throw std::string("no current item");
                    }

                    return _it->second;
                }

                /**
                 * @brief Point to next iterator
                 * 
                 */
                void next() {
                    if (isDone()) {
                        throw std::string("moving past the end");
                    }
                    _it++;
                }

                /**
                 * @brief Check if iterator is end.
                 * 
                 * @return true 
                 * @return false 
                 */
                bool isDone() {
                    return _it == _folder->_children.end();
                }

            private:
                /**
                 * @brief The folder that create iterator
                 * 
                 */
                Folder* _folder;

                /**
                 * @brief The actual iterator for _children
                 * 
                 */
                std::map<std::string, Node*>::iterator _it;
        };

        /**
         * @brief Construct a new Folder object
         * 
         * @param path The specified path for this folder object.
         */
        Folder(const char* path) : Node(path) {
            if (!S_ISDIR(this->_st.st_mode)) {
                throw std::string("Path of constructor does not correspond with class.");
            }
        }

        /**
         * @brief Add child node to this folder
         * 
         * @param node 
         */
        void add(Node* node) {
            // set this folder as child parent.
            node->setParent(this);
            this->_children[node->path() + node->name()] = node;
            // this->_children.insert(std::pair<std::string, Node*>(node->path() + node->name(), node));
        }

        /**
         * @brief Get info content from this folder
         * 
         * @return int 
         */
        int infoContent() const {
            int sum = 0;
            std::map<std::string, Node*>::const_iterator it;

            for(it = this->_children.begin(); it != this->_children.end(); it++) {
                sum += it->second->infoContent();
            }
            
            return sum;
        }

        /**
         * @brief Get the number of children node
         * 
         * @return int 
         */
        int numberOfChildren() const {
            return this->_children.size();
        }

        /**
         * @brief Get folder or fild path by specified node name
         * 
         * @param nodeName 
         * @return std::string 
         */
        std::string find(std::string nodeName) const {

            // find all match nodes first.
            std::vector<Node*> matchNode;
            this->findNode(nodeName, matchNode);
            std::vector<std::string> results;

            // the top path is this folder name. eg. test_data->find("folder")
            // then top path is "test_data"
            std::string topPath = this->name();

            for (Node* node : matchNode) {

                // results doesn't contain the name of the folder itself.
                if (node->name() == topPath) {
                    results.push_back("");
                }

                std::size_t topPathPosition = node->path().find("/" + topPath);
                if (topPathPosition != std::string::npos) {
                    std::string path = node->path();

                    // remove the top path then push node's name
                    results.push_back("." + path.substr(topPathPosition + topPath.size() + 1) + node->name());
                }
            }

            std::string content = "";
            for (std::string str : results) {
                if (str == "") {
                    continue;
                }

                content += str;
                if (str != *(results.end() - 1)) {
                    content += "\n";
                }
            }

            return content;
        }

        /**
         * @brief find all child node, including child folder's child node, that match sepcified node name.
         * 
         * @param nodeName 
         * @param results 
         */
        void findNode(std::string nodeName, std::vector<Node*>& results) const {
            std::map<std::string, Node*>::const_iterator it;

            for (it = this->_children.begin(); it != this->_children.end(); it++) {
                if (it->second->name() == nodeName) {
                    results.push_back(it->second);
                }
                it->second->findNode(nodeName, results);
            }

            // std::reverse(results.begin(), results.end());
        }

        /**
         * @brief Accept visitor
         * 
         * @param visitor 
         */
        void accept(NodeVisitor* visitor) {
            visitor->visitFolder(this);
        }

        /**
         * @brief Create a FolderIterator object
         * 
         * @return NodeIterator* 
         */
        NodeIterator* createIterator() {
            return new Folder::FolderIterator(this);
        }

    private:

        /**
         * @brief The structure that storage folder's child node.
         * 
         */
        std::map<std::string, Node*> _children;
};

#endif