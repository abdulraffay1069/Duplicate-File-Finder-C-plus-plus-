#ifndef HASHMAP_H
#define HASHMAP_H
#include "HashingChecking.h"
#include <iostream>
#include <vector>
using namespace std;

//the node which i am gonna store in hashMap it has(key,values,bool telling if it has duplicates or not,address of next node)
struct HashNode {
    string key;
    vector<string> values;
    bool duplicate;
    HashNode* next;

    HashNode(const string& key, const vector<string>& values, HashNode* next, bool duplicate)
        : key(key), values(values), next(next), duplicate(duplicate) {}
};

class HashMap {
public:
    HashMap(int capacity = 15);
    virtual ~HashMap();

    void put(string key, string filePath);    //function to insert key value pair in hashMap
    vector<string> get(string key);           //function which will return vector<string> which are values of specifc key
    bool contains(string key);                  //function that will tell us if key exists
    int getSize();                              //function which will tell us how many key value pairs are there in hash map
    bool isEmpty();                             //function which will check if hashMap is empty or not
    void printHashMap();                        //funct that will print all the nodes...
    void printDuplicates();                     //func that will print only duplicates
    void callRehash();                          //func that will generate newHash Map if it exceeds a specific size
    void freeTable();                           //func to delete the hashmap
    void duplicateFilesDeletion();
    vector<int> duplicates;         // stores bucket indices which have node having duplicate values

private:
    vector<HashNode*> buckets;      // vector of bucket head pointers

    int capacity;                   // number of buckets
    int size;                       // total number of keys
    HashingChecking helper;

    void put(string key, vector<string> values);   // internal put
    int hashFunction(string& key, int capacity);  // compute bucket index
    void rehash();                                 // expand table safely
    void duplicatePutter(int index);              // record duplicate bucket
};

#endif // HASHMAP_H

