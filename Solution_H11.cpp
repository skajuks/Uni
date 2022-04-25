#include <iostream>
#include <map>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

class Data {
public:
    int id;
    char word[30];
    bool status;

    Data() {};
    Data(const int &id, const string &input, bool &status) {
        this->id = id;
        if (input.length() > 30)
            cout << "string too long lol" << endl;
        strcpy(this->word ,input.c_str());
        this->status = status;
    }
};

enum States : int {     // hold enumerations for all states to be accessed via switch statement
    STATE_DELETE_RECORD = 1,
    STATE_PRINT_NON_DELETED,
    STATE_PRINT_ALL_RECORDS,
    STATE_PURGE_ALL_RECORDS
};

inline map<int, map<string, bool>> readFromBinaryFile(string filename) {
	ifstream file(filename, ios::binary);

	map<int, map<string, bool>> temp;
	Data dta;
	while (file.read((char*)&dta, sizeof(Data))) {
		temp[dta.id].insert(make_pair(dta.word, dta.status));
	}

	file.close();
	return temp;
}

inline void writeToBinaryFile(const map<int, map<string, bool>> items, string filename) {
	ofstream file(filename, ios::binary);
    for (auto const& item : items) {
        Data dta;
        dta.id = item.first;
        for (auto const& pair : item.second) {
            strcpy(dta.word, pair.first.c_str());
            dta.status = pair.second;
        }
		file.write((char*)&dta, sizeof(Data));
    }
	file.close();
}

inline void printMap(map<int, map<string, bool>> const& inputMap) {
	for (auto const& item : inputMap) {
        cout << item.first << " ";
        for (auto const& pair : item.second) {
            cout << pair.first << " " << pair.second << endl;
        }
	}
}

inline void printMapNonDeleted(map<int, map<string, bool>> const& inputMap) {
	for (auto const& item : inputMap) {
        for (auto const& pair : item.second) {
            if(!pair.second)
                cout << item.first << " " << pair.first << " " << pair.second << endl;
        }
	}
}

inline void deleteFromIndex(map<int, map<string, bool>> &datamap, int &indx) {
    auto it = datamap.find(indx);
    for (auto i = it->second.begin(); i != it->second.end(); ++i)
        i->second = true;
}

inline void purgeRecords(map<int, map<string, bool>>& inputMap) {
    vector<int> eraseKeys;
    for (auto const& item : inputMap) {
        for (auto const& pair : item.second) {
            if(pair.second)
                eraseKeys.push_back(item.first);
        }
    }
    for (auto const& key : eraseKeys)
        inputMap.erase(key);
}

int main() {
    map<int, map<string, bool>> createFileData;
    for (int i = 0; i < 10; i++) {
        createFileData[i].insert(make_pair("Jenots", false));
    }
    writeToBinaryFile(createFileData, "binary_data.bin");

    map<int, map<string, bool>> binaryData = readFromBinaryFile("binary_data.bin");

    int input;
    do {
        cout << "1 : [delete] 2 : [print non-deleted] 3 : [print all] 4 : [purge deleted] " << endl;
        cin >> input;
        switch (input) {    // State machine go brrrr
            case States::STATE_DELETE_RECORD:
                int id;
                cout << "Input id for record to be deleted : " << endl;
                cin >> id;
                deleteFromIndex(binaryData, id);
                break;
            case States::STATE_PRINT_NON_DELETED:
                printMapNonDeleted(binaryData);
                break;
            case States::STATE_PRINT_ALL_RECORDS:
                printMap(binaryData);
                break;
            case States::STATE_PURGE_ALL_RECORDS:
                purgeRecords(binaryData);
                break;
            default : break;
        }
    } while (input != 0);
}