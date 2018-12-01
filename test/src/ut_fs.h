#ifndef UT_FS_H
#define UT_FS_H

#include <gtest/gtest.h>
#include <sys/stat.h>
#include <memory>
#include <folder.h>
#include <file.h>
#include <link.h>
#include <info_content_visitor.h>
#include <find_link_visitor.h>
#include <find_node_by_pathname_visitor.h>
#include <node_iterator.h>
#include <node_builder.h>

TEST(MiscTest, lstatOnFolder) {
    const char *path = "./test_data";
    struct stat st;
    ASSERT_EQ(0, lstat(path, &st));
    ASSERT_EQ(4096, st.st_size);
    ASSERT_EQ(true, S_ISDIR(st.st_mode));
    ASSERT_EQ(false, S_ISREG(st.st_mode));
    ASSERT_EQ(false, S_ISLNK(st.st_mode));
}

TEST(MiscTest, NodeTypeError) {
    ASSERT_ANY_THROW(new File("./test_data/folder")); // Do not indicate the file path.
    ASSERT_ANY_THROW(new Folder("./test_data/hello")); // Do not indicate the Folder path.
    ASSERT_ANY_THROW(new Link("./test_data/hello.cpp")); // Do not indicate the Link path.
}

TEST (FindNodeByPathnameVisitor, Link){
    Node* hello = new Link("./test_data/hello");
    std::vector<std::string>* names = new std::vector<std::string>{std::string("hello")};
    FindNodeByPathnameVisitor* fv = new FindNodeByPathnameVisitor(names);
    hello->accept(fv);
    ASSERT_EQ(hello, fv->getNode());
}

TEST (FindNodeByPathnameVisitor, LinkInFolder){
    Node* test_data = new Folder ("./test_data");
    Node* hello = new Link("./test_data/hello");
    test_data->add(hello);
    std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("hello")};
    FindNodeByPathnameVisitor* fv = new FindNodeByPathnameVisitor(names);
    test_data->accept(fv);
    ASSERT_EQ(hello, fv->getNode());
}

TEST (FindNodeByPathnameVisitor, FolderInFolder) {
    Node* test_data = new Folder ("./test_data");
    Node* test_data2 = new Folder("./test_data/test_data");
    test_data->add(test_data2);
    std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("test_data")};
    FindNodeByPathnameVisitor* fv = new FindNodeByPathnameVisitor(names);
    test_data->accept(fv);
    ASSERT_EQ(test_data2, fv->getNode());
}

TEST (FindNodeByPathnameVisitor, FileInNestedFolder) {
    Node* test_data = new Folder("./test_data");
    Node* folder1 = new Folder("./test_data/folder");
    Node* folder2 = new Folder("./test_data/folder/folder");
    Node* a_out1 = new File("./test_data/folder/a.out");
    Node* a_out2 = new File("./test_data/folder/folder/a.out");

    folder2->add(a_out2);
    folder1->add(folder2);
    folder1->add(a_out1);
    test_data->add(folder1);

    std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("folder"), std::string("folder"), std::string("a.out")};
    FindNodeByPathnameVisitor* fv1 = new FindNodeByPathnameVisitor(names);
    test_data->accept(fv1);
    ASSERT_EQ(a_out2, fv1->getNode());

    std::vector<std::string>* names2 = new std::vector<std::string>{std::string("test_data"), std::string("folder"), std::string("a.out")};
    FindNodeByPathnameVisitor* fv2 = new FindNodeByPathnameVisitor(names2);
    test_data->accept(fv2);
    ASSERT_EQ(a_out1, fv2->getNode());
}

TEST (FindNodeByPathnameVisitor, nonExistingFileInFileSystem) {
    Node* test_data = new Folder ("./test_data");
    std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("helloWorld")};
    FindNodeByPathnameVisitor* fv = new FindNodeByPathnameVisitor(names);
    test_data->accept(fv);
    ASSERT_EQ(nullptr, fv->getNode());
}

class FileSystemTest : public ::testing::Test {
    protected:
        void SetUp() override {
            test_data = new Folder("./test_data");
            folder = new Folder("./test_data/folder");
            hello_cpp = new File("./test_data/hello.cpp");
            a_out = new File("./test_data/folder/a.out");
            hello = new Link("./test_data/hello", a_out);
            folder->add(a_out);
            test_data->add(folder);
            test_data->add(hello);
            test_data->add(hello_cpp);
        }

        void TearDown() override {
            delete a_out;
            delete hello_cpp;
            delete hello;
            delete folder;
            delete test_data;
        }

        Node *test_data;
        Node *folder;
        Node *hello_cpp;
        Node *a_out;
        Node *hello;
};

TEST_F(FileSystemTest, Size) {
    ASSERT_EQ(4096, test_data->size());
    ASSERT_EQ(4096, folder->size());
    ASSERT_EQ(83, hello_cpp->size());
    ASSERT_EQ(8432, a_out->size());
    ASSERT_EQ(12, hello->size());
    ASSERT_EQ(8432, dynamic_cast<Link *>(hello)->getSource()->size());
    ASSERT_EQ(3, test_data->numberOfChildren());
}

TEST_F(FileSystemTest, Visitor) {
    InfoContentVisitor *icv = new InfoContentVisitor();
    a_out->accept(icv);
    ASSERT_EQ(8432, icv->getContentSize());
    delete icv;

    InfoContentVisitor *icv10 = new InfoContentVisitor();
    hello->accept(icv10);
    ASSERT_EQ(8432, icv10->getContentSize());
    // icv = new InfoContentVisitor("");
    InfoContentVisitor *icv2 = new InfoContentVisitor();
    folder->accept(icv2);
    ASSERT_EQ(8432, icv2->getContentSize());

    InfoContentVisitor *icv3 = new InfoContentVisitor();
    test_data->accept(icv3);
    ASSERT_EQ(16947, icv3->getContentSize());
}

TEST_F(FileSystemTest, NodeIterator) {
    std::unique_ptr<NodeIterator> it(test_data->createIterator());
    // NodeIterator * it = test_data->createIterator();
    it->first();
    ASSERT_EQ(4096, it->currentItem()->size());
    it->next();
    ASSERT_EQ(12, it->currentItem()->size());
    it->next();
    ASSERT_EQ(83, it->currentItem()->size());
    it->next();
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());

    // delete it;
}

TEST_F(FileSystemTest, NodeBuilderOnFile) {
    NodeBuilder nb;
    nb.build("test_data/hello.cpp");
    ASSERT_EQ(83, nb.getRoot()->size());

    nb.build("test_data/hello");
    ASSERT_EQ(12, nb.getRoot()->size());
    // ASSERT_EQ(8432, dynamic_cast<Link *>(nb.getRoot())->getSource()->size());

    nb.build("test_data/folder");
    ASSERT_EQ(4096, nb.getRoot()->size());

    std::unique_ptr<NodeIterator> it(nb.getRoot()->createIterator());
    it->first();
    // ASSERT_TRUE(it->isDone());
    ASSERT_EQ(8432, it->currentItem()->size());

    it->next();
    it->next();
    it->next();
    ASSERT_TRUE(it->isDone());

    nb.build("test_data");
    ASSERT_EQ(4096, nb.getRoot()->size());
    std::unique_ptr<NodeIterator> it1(nb.getRoot()->createIterator());
    it1->first();
    ASSERT_EQ(4096, it1->currentItem()->size());
    it1->next();
    ASSERT_EQ(12, it1->currentItem()->size());
    it1->next();
    ASSERT_EQ(83, it1->currentItem()->size());
    it1->next();
    it1->next();
    ASSERT_TRUE(it1->isDone());
}

TEST_F(FileSystemTest, FindLinkVisitor) {
    NodeBuilder nb;
    nb.build("test_data");

    FindLinkVisitor* visitor = new FindLinkVisitor();
    visitor->visitFolder(dynamic_cast<Folder*>(nb.getRoot()));
    ASSERT_EQ(1, visitor->getLinks().size());
}

#endif