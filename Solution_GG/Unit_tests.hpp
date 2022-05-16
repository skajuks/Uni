#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

// Forward declarations so c++ understands where all those functions came from
struct DataNode;
void createNode(int &in, DataNode* &head, DataNode* &tail);
void printLinkedList(DataNode* head);
size_t countElements(DataNode* head);
void removeElement(DataNode* &head, int idx);

class Test {
public:
    Test(tuple<vector<int>, int> n, int id) : Nodes(n), id(id) {
        doTestCase(Nodes, id);
    };
    inline void doTestCase(tuple<vector<int>, int> &Nodes, int &id);

private:
    int id;
    tuple<vector<int>, int> Nodes;
};

inline void Test::doTestCase(tuple<vector<int>, int> &Nodes, int &id) {
    // initialize value to store pointers
    DataNode* head = nullptr;
    DataNode* tail = nullptr;

    try {
        for (auto element : get<0>(Nodes))  // loop through integers in vector
            createNode(element, head, tail);

        printLinkedList(head);

        if (get<1>(Nodes) > countElements(head))   // check if element is not bigger then list size
            throw runtime_error(to_string(get<1>(Nodes)) + " -> Index doesnt exist!");

        removeElement(head, get<1>(Nodes));  // Remove element

        printLinkedList(head); // Print out our list of integers after removal

        cout << "Test case id " << id << " success!" << endl;

    } catch(exception &e) {
        cout << "Test case id " << id << " failed, reason : " << e.what() << endl;
    }
}