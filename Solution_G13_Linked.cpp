#include <iostream>
#include <list>

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

void createNodeAtPos(int pos, int value, DataNode* &head) {
    DataNode* prev = new DataNode;
    DataNode* current = new DataNode;
    DataNode* temp = new DataNode;
    current = head;

    for (int i = 0; i < pos; i++) {
        prev = current;
        current = current->next;
    }
    temp->data = value;
    prev->next = temp;
    temp->next = current;
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

void removeAndAddElement(DataNode* &head, int idx) {
    DataNode* temp = nullptr;
    DataNode* current = head;
    int value = 0;

    if (idx == 0) {
        temp = head->next;
        value = head->data;
        delete head;
        createNodeAtPos(idx, value, head);
    } else {
        for (int i = 0; i < idx - 1; i++) {
            current = current->next;
        }

        temp = current->next;
        value = temp->data;
        current->next = temp->next;
        delete temp;
        createNodeAtPos(idx, value, head);
    }
}

int main() {
    // initialize value to store pointers
    DataNode* head = nullptr;
    DataNode* tail = nullptr;

    // Input handler for list
    int input;
    cout << "Enter list elements, press 0 to stop : " << endl;

    do {
        cin >> input;  // get the input

        if (input == 0) {
            if (head == nullptr) {  // Check if head is nullptr so we know if its the first value
                cout << "Empty list, try again!" << endl;
                input = 1;
            } else {
                break;
            }
        } else {    // Good value, create a new node for it
            createNode(input, head, tail);
        }
    } while(input != 0);    // keep the loop going while input != 0

    printLinkedList(head);

    int index;
    do {
        cout << "Enter index of element to swap : " << endl;
        cin >> index; // get n'th element of list to perform action on
        if (index - 1 > countElements(head))   // check if element is not bigger then list size
            cout << index << " -> Index doesnt exist, try again! " << endl;

    } while (index - 1 > countElements(head)); // loop while element is not bigger then list size

    removeAndAddElement(head, index);  // Do the magic

    printLinkedList(head); // Print out our list of integers after the swap

    return 0;

}
