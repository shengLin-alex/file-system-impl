#ifndef NODE_BUILDER_H
#define NODE_BUILDER_H
#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include <string>
#include <sys/stat.h>
#include <dirent.h>

/**
 * @brief Builder for build specified path Node object.
 * 
 */
class NodeBuilder {
    public:

        /**
         * @brief Construct a new Node Builder object
         * 
         */
        NodeBuilder() : _root(nullptr) {
        }

        /**
         * @brief Build specified node object by given path.
         * 
         * @param path 
         */
        void build(const char* path) {
            struct stat st;

            // check if path is legel.
            if (lstat(path, &st) != 0) {
                return;
            }

            if (S_ISREG(st.st_mode)) { // check if is a file.
                _root = new File(path);
            } else if (S_ISLNK(st.st_mode)) { // check if is a link.
                // get real path from link.
                char* actualPath = realpath(path, NULL);
                NodeBuilder nb;
                nb.build(actualPath); // build real node object.
                _root = new Link(path, nb.getRoot());
            } else if (S_ISDIR(st.st_mode)) { // check if is a folder.
                _root = new Folder(path);
                DIR* dir = opendir(path);
                if (dir == nullptr) { 
                    throw std::string("open folder error");
                }

                struct dirent* entry = nullptr;
                while ((entry = readdir(dir)) != nullptr) {
                    if (std::string(entry->d_name) != "." && std::string(entry->d_name) != "..") {
                        NodeBuilder nb;
                        std::string pathString = std::string(path) + "/" + std::string(entry->d_name);
                        nb.build(pathString.c_str());
                        _root->add(nb.getRoot());
                    }
                }
            }
        }

        /**
         * @brief Get root that builder built.
         * 
         * @return Node* 
         */
        Node* getRoot() {
            return _root;
        }

    private:

        /**
         * @brief The node object that builder built.
         * 
         */
        Node* _root;
};

#endif
