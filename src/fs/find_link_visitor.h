#ifndef FIND_LINK_VISITOR_H
#define FIND_LINK_VISITOR_H

#include "node_visitor.h"
#include <vector>

class Node;

/**
 * @brief FindLinkVisitor, find all Link object in Folder node or Link node itself.
 * 
 */
class FindLinkVisitor : public NodeVisitor {
    public:
        
        /**
         * @brief Construct a new Find Link Visitor object
         * 
         */
        FindLinkVisitor();

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
         * @brief Get the Links object that found.
         * 
         * @return std::vector<Node*> 
         */
        std::vector<Node*> getLinks(); // return the Link objects.
    
    private:

        /**
         * @brief The structure that storage link objects found.
         * 
         */
        std::vector<Node*> _links;
};

#endif