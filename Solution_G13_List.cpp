#include <iostream>
#include <list>

void printList(std::list<int> input) {
    // Iterate over list elements
    for (auto &element : input) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

size_t countElements(std::list<int> input) {
    return input.size();
}

void removeAndAddElement(std::list<int> input, int& idx) {

    auto destroy = std::next(input.begin(), idx - 1);  // get element to remove from index
    auto replace_with = std::next(input.begin(), *destroy - 1);  // get element value to put back

    input.erase(destroy); // remove element from list
    input.insert(destroy, *replace_with);   // place it back in the list
}

int main() {
    // initialize list
    std::list<int> inputList;

    // Input handler for list
    int input;
    std::cout << "Ievadiet sarakstu! Ievadiet 0, lai beigtu!" << std::endl;

    do {
        std::cin >> input;  // get the input

        if (input == 0) {
            if (!inputList.empty()) {
                break;  // if input equals 0, break loop
            } else {
                std::cout << "Tukss saraksts. Meginiet velreiz!" << std::endl;
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
        std::cout << "Ievadiet indeksu : " << std::endl;
        std::cin >> index; // get n'th element of list to perform action on
        if (index - 1 > countElements(inputList))   // check if element is not bigger then list size
            std::cout << "Nepastav " << index << ". elementa! Meginiet velreiz!" << std::endl;

    } while (index - 1 > countElements(inputList)); // loop while element is not bigger then list size

    removeAndAddElement(inputList, index);  // Do the magic

    printList(inputList); // Print out our list of integers after the swap

    return 0;
}


