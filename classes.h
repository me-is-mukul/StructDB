#ifndef CLASSES_H
#define CLASSES_H 


#include <iostream>
#include <vector>
#include<unordered_map>
#include<unordered_set>
#include<queue>
using namespace std;

struct entity {
    string name;
    int search_frequency;
};

//swasti
struct Topic {
    string name;
    vector<string> relatedTopics; // adjacency list
    string link;
    int difficulty; // 1=Easy, 2=Medium, 3=Hard
    Topic( string n, vector<string> r, string l, int d) {
        name = n;
        relatedTopics = r;
        link = l;
        difficulty = d;
    }
};

#endif 
