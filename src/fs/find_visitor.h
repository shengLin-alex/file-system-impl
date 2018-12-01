#ifndef FIND_VISITOR_H
#define FIND_VISITOR_H

#include "node_visitor.h"

/**
 * @brief FindVisitor, find paths that matched given node name.
 * 
 */
class FindVisitor : public NodeVisitor {
    public:

        /**
         * @brief Construct a new Find Visitor object
         * 
         * @param name Node name.
         */
        FindVisitor(std::string name);

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
         * @brief Get result
         * 
         * @return std::string 
         */
        std::string findResult();

    private:

        /**
         * @brief The given target node name.
         * 
         */
        std::string _name;

        /**
         * @brief The result that found.
         * 
         */
        std::string _result;
};

#endif