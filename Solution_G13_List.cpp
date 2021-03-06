#include <iostream>
#include <list>

using namespace std;

void printList(list<int> &input) {
    // Iterate over list elements
    for (auto &element : input) {
        cout << element << " ";
    }
    cout << endl;
}

size_t countElements(list<int> &input) {
    return input.size();
}

void removeAndAddElement(list<int> &input, int& n) {

    list<int>::iterator itter = next(input.begin(), n - 1);  // get element to remove from index

    if (*itter > countElements(input)) {    // check if element can be inserted
        cout << "Error, element with index " << *itter << " does not exist" << endl;
        return;
    }

    list<int>::iterator itter2 = input.begin();
    advance(itter2, n - 1); // get the index of our value in list

    input.erase(itter);

    list<int>::iterator itter3 = next(input.begin(), *itter - 1);   // get the value from index using our first itter value
    input.insert(itter3, *itter2);
}

int main() {
    // initialize list
    list<int> inputList;

    // Input handler for list
    int input;
    cout << "Enter elements for list, press 0 to stop" << endl;

    do {
        cin >> input;  // get the input

        if (input == 0) {
            if (!inputList.empty()) {
                break;  // if input equals 0, break loop
            } else {
                cout << "Empty list, try again!" << endl;
                input = 1; // Small hack to prevent while loop from exiting
            }
        } else {
             inputList.emplace_back(input);  // emplace input into list
        }
    } while(input != 0);    // keep the loop going while input != 0

    printList(inputList); // Print out our list of integers

    // Input handler for element
    int index;
    do {
        cout << "Enter index : " << endl;
        cin >> index; // get n'th element of list to perform action on
        if (index - 1 > countElements(inputList))   // check if element is not bigger then list size
            cout << index << " <- Index doesnt exist, try again!" << endl;

    } while (index - 1 > countElements(inputList)); // loop while element is not bigger then list size

    removeAndAddElement(inputList, index);  // Do the magic

    printList(inputList); // Print out our list of integers after the swap

    return 0;
}

// Test cases
/*
    Entry list : 1 2 3 4 6 7        idx = 4     output = 1 2 3 4 6 7                  = GOOD
    Entry list : 4 5 1 2 1          idx = 1     output = 2 5 1 2 1                    = GOOD
    Entry list : 1 2 3              idx = 2     output = 1 2 3                        = GOOD
    Entry list :                    idx =       output = Empty list, try again!       = GOOD
    Entry list : 1                  idx = 1     output = 1                            = GOOD
    Entry list : 1                  idx = 3     output = 3 <- Index doesnt exist, try again! = GOOD
*/
