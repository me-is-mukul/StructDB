#include "classes.h"


// 📘 Show Related Topics + Links + Difficulty
void TopicGraph::showRelated(string topic) {
    if(topicMap.find(topic) == topicMap.end()) {
        cout << "\n Topic not found!\n";
        return;
    }

    cout << "\n Topic: " << topic << endl;
    cout << " Study Link: " << topicMap[topic].link << endl;
    cout << " Difficulty Level: " << topicMap[topic].difficulty << "/3" << endl;

    cout << "\n Related Topics: ";
    for(string t : topicMap[topic].relatedTopics) cout << t << "  ";
    cout << endl;
}

// 🚀 BFS — Recommended Learning Path (Allowed in course)
void TopicGraph::showLearningPath(string startTopic) {
    if(topicMap.find(startTopic) == topicMap.end()) {
        cout << "Topic not found.\n";
        return;
    }

    unordered_set<string> visited;
    queue<string> q;

    cout << "\n Recommended Learning Path:\n";
    q.push(startTopic);
    visited.insert(startTopic);

    while(!q.empty()) {
        string current = q.front(); q.pop();
        cout << current << " -> ";

        for(string next : topicMap[current].relatedTopics) {
            if(!visited.count(next)) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
    cout << "END\n";
}

// 📘 DFS — Concept Depth
void TopicGraph::dfsTraversal(string topic, unordered_set<string> &visited) {
    visited.insert(topic);
    cout << topic << " -> ";

    for(string next : topicMap[topic].relatedTopics) {
        if(!visited.count(next)) {
            dfsTraversal(next, visited);
        }
    }
}
