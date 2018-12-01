#ifndef INFO_CONTENT_VISITOR_H
#define INFO_CONTENT_VISITOR_H

#include "node_visitor.h"

/**
 * @brief InfoContentVisitor, find info content of a specified node object.
 * 
 */
class InfoContentVisitor : public NodeVisitor {
    public:

        /**
         * @brief Construct a new Info Content Visitor object
         * 
         */
        InfoContentVisitor();

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
         * @brief Get the Content Size result
         * 
         * @return int 
         */
        int getContentSize();

    private:

        /**
         * @brief The result of content result
         * 
         */
        int _size;
};

#endif