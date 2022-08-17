// HashTable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define LISTSIZE 10



class HashTable {
public:
    HashTable();
    ~HashTable();
    int key;
    int data;
    int occupied;
    int HashFunction(void* (*HashPtr)(void* Key),int TempKey);
    HashTable* FindAttach();
    int Search(void* (*HashPtr)(void* Key), int SearchKey);
    HashTable* Next;

private:
    int HashDefault(int Key);
    
};


int HashTable::HashDefault(int Key) {
    int test = Key % LISTSIZE;
    return test; 
}

int HashTable::HashFunction(void* (*HashPtr)(void* Key),int TempKey) {
    int Index;
    if (HashPtr == 0) {
        Index = HashDefault(TempKey);
    }
    else {
        Index = *(int*)(*HashPtr)((void*)&TempKey); //convert function return to int* then take the value corresponding to location
    }
    return Index;
}

HashTable::HashTable() {
    data = 0;
    key = 0;
    Next = 0;
    occupied = 0;
    Next = this;
}

HashTable::~HashTable() {
    HashTable* FreeAddr = Next;
    while (FreeAddr != this) {
        FreeAddr = Next;
        Next = Next->Next;
        free(FreeAddr);
    }
}


HashTable* HashTable::FindAttach() {
    HashTable* Start = this;
    HashTable *Save = Start;
    while (Next != Start) {
        Save = Next;
        Next = Next->Next;
    }
    Next = (HashTable*)malloc(sizeof(HashTable));
    Save->Next = Next;
    Next->Next = Start;
    return Next;
}

int HashTable::Search(void* (*HashPtr)(void* Key), int SearchKey) { //if use default enters 0
    int index = 0;
    if (HashPtr) {
        index = *(int*)(*HashPtr)((void*)&SearchKey);
    }
    else {
        index = HashDefault(SearchKey);
    }
    return index;
}

int main()
{
    HashTable List[LISTSIZE];
    int index = 0, tempKey, tempData;
    for (int i = 0; i < 10; i++) {
        std::cout << i << "\n";
        std::cout << "Enter Key: ";
        std::cin >> tempKey;
        std::cout << "Enter Data: ";
        std::cin >> tempData;
        if (i == 3) {
            i = 3;
        }
        index = List[0].HashFunction(0,tempKey);
        if (List[index].occupied == 0) {
            List[index].key = tempKey;
            List[index].data = tempData;
            List[index].occupied = 1;
        }
        else {
            HashTable* place = List[index].FindAttach();
            place->key = tempKey;
            place->data = tempData;
            place->occupied = 1;
        }
    }

    int SearchKey = 0;
    while (true) {
        HashTable* pt;
        std::cout << "\nEnter SearchKey: ";
        std::cin >> SearchKey;
        if (SearchKey < 0) {
            break;
        }
        int location = List[0].Search(0,SearchKey);
        pt = &List[location];
        while (pt->key != SearchKey && pt->Next != &List[location]) {
            pt = pt->Next;
        }
        std::cout << "\nthe data is: " << pt->data;
    }
    std::cout << "Hello World!\n";
}

/* test input
7735
1
5837
2
4101
3
7515
4
5106
5
8840
6
8211
7
5394
8
8418
9
4194
10
*/
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
