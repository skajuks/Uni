#include <iostream>
#include <map>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>


using namespace std;

class Data {
public:
    int id;
    char word[30];
    bool status;

    Data() {};
    ~Data() {};
};

enum States : int {     // hold enumerations for all states to be accessed via switch statement
    STATE_DELETE_RECORD = 1,
    STATE_PRINT_NON_DELETED,
    STATE_PRINT_ALL_RECORDS,
    STATE_PURGE_ALL_RECORDS
};

inline map<int, map<string, bool>> readFromBinaryFile(string filename) {
	ifstream file(filename, ios::binary);   // read in file

	map<int, map<string, bool>> temp;
	Data dta;
	while (file.read((char*)&dta, sizeof(Data))) {  // itterate through entries
		temp[dta.id].insert(make_pair(dta.word, dta.status));   // assign data to map
	}

	file.close();
	return temp;
}

inline void writeToBinaryFile(const map<int, map<string, bool>> items, string filename) {
	ofstream file(filename, ios::binary);   // get our file
    for (auto const& item : items) {    // loop to get data from first map
        Data dta;   // temp buffer to store our data
        dta.id = item.first;
        for (auto const& pair : item.second) {  // get data from nested map
            if (pair.first.length() > 30) {
                std::cout << "[Error] : String " <<  pair.first << " is longer then 30 chars" << std::endl;
                throw("");
            }
            strcpy(dta.word, pair.first.c_str());
            dta.status = pair.second;
        }
		file.write((char*)&dta, sizeof(Data));  // write from temp buffer
    }
	file.close();
}

inline void printMap(map<int, map<string, bool>> const& inputMap) {
    // basic looping through nested map and simply printing to console
	for (auto const& item : inputMap) {
        cout << item.first << " ";
        for (auto const& pair : item.second) {
            cout << pair.first << " " << pair.second << endl;
        }
	}
}

inline void printMapNonDeleted(map<int, map<string, bool>> const& inputMap) {
    // same thing as before, just this time checking for bool
	for (auto const& item : inputMap) {
        for (auto const& pair : item.second) {
            if(!pair.second)
                cout << item.first << " " << pair.first << " " << pair.second << endl;
        }
	}
}

inline void deleteFromIndex(map<int, map<string, bool>> &datamap, int &indx) {
    auto it = datamap.find(indx);       // find data entry from index
    for (auto i = it->second.begin(); i != it->second.end(); ++i)   // some weird way to get access to our bool value
        i->second = true;
}

inline void purgeRecords(map<int, map<string, bool>>& inputMap) {
    vector<int> eraseKeys;
    // get keys of all entries we want to delete
    for (auto const& item : inputMap) {
        for (auto const& pair : item.second) {
            if(pair.second)
                eraseKeys.push_back(item.first);
        }
    }
    // loop our key array and delete them from map
    for (auto const& key : eraseKeys)
        inputMap.erase(key);
}

int main() {

    // File setup for test case 1

    map<int, map<string, bool>> createFileData_1;

    // basic for loop to insert some dummy data here, can be changed to insert individual entites
    for (int i = 1; i < 3; i++) {
        createFileData_1[i].insert(make_pair("Test_String_" + to_string(i), false));
    }
    // extras
    createFileData_1[11].insert(make_pair("Jenots", true));
    createFileData_1[12].insert(make_pair("Lacis", false));
    writeToBinaryFile(createFileData_1, "test_case_1.bin");

    // File setup for test case 2

    map<int, map<string, bool>> createFileData_2;

    // basic for loop to insert some dummy data here, can be changed to insert individual entites
    for (int i = 1; i < 2; i++) {
        createFileData_2[i].insert(make_pair("Test_String_" + to_string(i), false));
    }
    // extras
    createFileData_2[14].insert(make_pair("Atomelektrostacija_Atomelektrostacija_Atomelektrostacija", false));    // throw an error
    writeToBinaryFile(createFileData_2, "test_case_2.bin");

    // Lets read data from our bin file
    const string test_file = "test_case_1.bin"; // change test case

    map<int, map<string, bool>> binaryData = readFromBinaryFile(test_file);

    int input;
    do {
        cout << "1 : [delete] 2 : [print non-deleted] 3 : [print all] 4 : [purge deleted] " << endl;
        cin >> input;
        switch (input) {    // State machine go brrrr
            case States::STATE_DELETE_RECORD:
                int id;
                cout << "Input id for record to be deleted : " << endl;
                cin >> id;
                deleteFromIndex(binaryData, id);    // change boolean state
                break;
            case States::STATE_PRINT_NON_DELETED:
                printMapNonDeleted(binaryData);     // print all with bool state false
                break;
            case States::STATE_PRINT_ALL_RECORDS:
                printMap(binaryData);   // print all
                break;
            case States::STATE_PURGE_ALL_RECORDS:
                purgeRecords(binaryData);   // delete map entries with bool state false
                break;
            default : break;
        }
    } while (input != 0);
}

// Test case
// case 1 :
/*
    File writes without issues

    Content:
        1 Test_String_1 0
        2 Test_String_2 0
        3 Test_String_3 0
        11 Jenots 1
        12 Lacis 0

    Output after option 1 -> delete id 2
        1 Test_String_1 0
        2 Test_String_2 1
        3 Test_String_3 0
        11 Jenots 1
        12 Lacis 0
    Output after option 2 -> print all non deleted entries
        1 Test_String_1 0
        3 Test_String_3 0
        12 Lacis 0
    Output after option 3 -> print all entries
        1 Test_String_1 0
        2 Test_String_2 1
        3 Test_String_3 0
        11 Jenots 1
        12 Lacis 0
    Output after option 4 -> purge all deleted entries
        1 Test_String_1 0
        3 Test_String_3 0
        12 Lacis 0
*/
//case 2 :
/*
    File write generates error -> [Error] : String Atomelektrostacija_Atomelektrostacija_Atomelektrostacija is longer then 30 chars
*/