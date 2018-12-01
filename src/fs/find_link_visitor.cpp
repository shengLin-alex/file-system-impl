#include "find_link_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"

FindLinkVisitor::FindLinkVisitor() : _links(std::vector<Node*>{}) {

}

void FindLinkVisitor::visitFolder(Folder* folder) {
    NodeIterator* it = folder->createIterator();

    for (it->first(); !it->isDone(); it->next()) {
        it->currentItem()->accept(this);
    }
}

void FindLinkVisitor::visitFile(File* file) {

}

void FindLinkVisitor::visitLink(Link* link) {
    this->_links.push_back(link);
}

std::vector<Node*> FindLinkVisitor::getLinks() {
    return this->_links;
}