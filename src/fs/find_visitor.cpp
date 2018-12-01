#include "find_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"

FindVisitor::FindVisitor(std::string name): _name(name), _result("") {
}

void FindVisitor::visitFile(File* file) {
    this->_result = "";

    if (file->name() == this->_name) {
        this->_result = this->_name;
    } else {
        this->_result = "";
    }
}

void FindVisitor::visitFolder(Folder* folder) {
    this->_result = "";

    // find all match nodes first.
    std::vector<Node*> matchNode;
    folder->findNode(this->_name, matchNode);
    std::vector<std::string> results;

    // the top path is this folder name. eg. test_data->find("folder")
    // then top path is "test_data"
    std::string topPath = folder->name();

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

    this->_result = content;
}

void FindVisitor::visitLink(Link* link) {
    link->getSource()->accept(this);
}

std::string FindVisitor::findResult() {
    return this->_result;
}