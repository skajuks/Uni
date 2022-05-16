#include "Unit_tests.hpp"

using namespace std;

struct DataNode {
    int data = 0;   // Stored data inside node
    DataNode* next;   // Pointer to next data node
};

void printLinkedList(DataNode* head) {
    // Iterate over elements
    DataNode* current = head;  // Start from the head and move to tail
    while (current != nullptr) {    // loop while we dont hit nullptr
        cout << current->data << " ";
        current = current->next;    // assing to next
    }
    cout << endl;
}

size_t countElements(DataNode* head) {  // same logic as oldNode
    size_t elements = 0;
     // Iterate over elements
    DataNode* current = head;  // Start from the head and move to tail
    while (current != nullptr) {    // loop while we dont hit nullptr
        elements++;
        current = current->next;    // assing to next
    }
    return elements;
}

void createNode(int &in, DataNode* &head, DataNode* &tail) {
    DataNode* temp = new DataNode;  // creating a temp node
    temp->data = in;  // assign node data to data from input
    temp->next = nullptr;

    if (head == nullptr) { // Check if its the first node created
        head = temp;    // Assign values from temp
        tail = temp;
    } else { // If its not the first node
        tail->next = temp;
        tail = temp;
    }
}

void removeElement(DataNode* &head, int idx) {
    DataNode* temp = nullptr;
    DataNode* current = head;
    int value = 0;

    if (idx == 0) {
        temp = head->next;
        value = head->data;
        delete head;
        cout << "Deleted node with value : " << value << endl;
    } else {
        for (int i = 0; i < idx - 1; i++) {
            current = current->next;
        }

        temp = current->next;
        value = temp->data;
        current->next = temp->next;
        delete temp;
        cout << "Deleted node with value : " << value << endl;
    }
}

int main() {

    // Unit tests
    Test({{1,23,4,5}, 6}, 1);
    Test({{1,2,3,4}, 2}, 2);
    Test({{1,0,0,0}, 1}, 3);

    return 0;

}
