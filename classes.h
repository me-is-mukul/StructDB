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
};

class TopicGraph {
public:
    unordered_map<string, Topic> topicMap;

    void loadArrayTopics();
    void loadLinkedListTopics();
    void loadSortingTopics();
    void loadStackTopics();
    void loadQueueTopics();
    void loadGraphTopics();
    void loadTreeTopics();

    void showRelated(string topic);
    void showLearningPath(string startTopic);
    void dfsTraversal(string topic, unordered_set<string>& visited);
};
#endif // CLASSES_H
