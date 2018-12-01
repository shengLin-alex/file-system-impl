#ifndef FIND_NODE_BY_PATHNAME_VISITOR_H
#define FIND_NODE_BY_PATHNAME_VISITOR_H

#include "node_visitor.h"
#include <vector>
#include <string>

class Node;

/**
 * @brief The visitor for find Node by given pathname
 * 
 */
class FindNodeByPathnameVisitor : public NodeVisitor {
    public:

        /**
         * @brief Construct a new FindNodeByPathnameVisitor object
         * 
         * @param pathnames 
         */
        FindNodeByPathnameVisitor(std::vector<std::string>* pathnames);

        /**
         * @brief visitor Folder object
         * 
         * @param folder 
         */
        void visitFolder(Folder* folder);

        /**
         * @brief visitor File object
         * 
         * @param file 
         */
        void visitFile(File* file);

        /**
         * @brief visit Link object
         * 
         * @param link 
         */
        void visitLink(Link* link);

        /**
         * @brief Get the Node object
         * 
         * @return Node* 
         */
        Node* getNode() const;

    private:
        std::vector<std::string>* _pathnames;
        std::string _targetPath;
        Node* _result;
        bool _isFound;
};

#endif