#include "find_node_by_pathname_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"

FindNodeByPathnameVisitor::FindNodeByPathnameVisitor(std::vector<std::string>* pathnames) : _pathnames(pathnames), _result(nullptr), _isFound(false) {
    if (this->_pathnames == nullptr || this->_pathnames->size() == 0) {
        this->_targetPath = "";
    } else {
        this->_targetPath = ".";
        for (std::string pathname : *this->_pathnames) {
            this->_targetPath += "/";
            this->_targetPath += pathname;
        }
    }
}

void FindNodeByPathnameVisitor::visitFolder(Folder* folder) {
    if (this->_pathnames == nullptr || this->_pathnames->size() == 0) {
        return;
    }

    std::string folderPath = folder->path() + folder->name();
    if (folderPath == this->_targetPath) {
        this->_result = folder;
        return;
    }

    NodeIterator* it = folder->createIterator();
    for (it->first(); !it->isDone(); it->next()) {
        it->currentItem()->accept(this);

        // if is found, break loop.
        if (this->_isFound) {
            break;
        }
    }
}

void FindNodeByPathnameVisitor::visitFile(File* file) {
    if (this->_pathnames == nullptr || this->_pathnames->size() == 0) {
        return;
    }

    std::string filePath = file->path() + file->name();
    if (filePath == this->_targetPath) {
        this->_result = file;
        this->_isFound = true; // set is found
        return;
    }

    std::string fileName = this->_pathnames->at(this->_pathnames->size() - 1);

    // do this only when given pathnames size = 1(only give file/link name)
    if (this->_pathnames->size() == 1 && fileName == file->name()) {
        this->_result = file;
        this->_isFound = true;
        return;
    }
}

void FindNodeByPathnameVisitor::visitLink(Link* link) {
    if (this->_pathnames == nullptr || this->_pathnames->size() == 0) {
        return;
    }

    std::string linkPath = link->path() + link->name();
    if (linkPath == this->_targetPath) {
        this->_result = link;
        this->_isFound = true;
        return;
    }

    std::string linkName = this->_pathnames->at(this->_pathnames->size() - 1);

    // do this only when given pathnames size = 1(only give file/link name)
    if (this->_pathnames->size() == 1 && linkName == link->name()) {
        this->_result = link;
        this->_isFound = true; // set is found
        return;
    }
}

Node* FindNodeByPathnameVisitor::getNode() const {
    return this->_result;
}