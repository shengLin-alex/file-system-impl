#ifndef VISITOR_H
#define VISITOR_H

#include "string"

class File;
class Folder;
class Link;

/**
 * @brief NodeVisitor interface
 * 
 */
class NodeVisitor {
    public:
        virtual void visitFile(File* file) = 0;
        virtual void visitFolder(Folder* folder) = 0;
        virtual void visitLink(Link* link) = 0;
};

#endif