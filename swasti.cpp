// #ifndef SWASTI_H
// #define SWASTI_H
#include "classes.h"

void TopicGraph::loadFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;  // skip blank lines

        stringstream ss(line);
        string name, relatedStr, link, diffStr;

        getline(ss, name, ';');
        getline(ss, relatedStr, ';');
        getline(ss, link, ';');
        getline(ss, diffStr, ';');

        Topic t;
        t.name = name;
        t.link = link;
        t.difficulty = stoi(diffStr);

        string word;
        stringstream relStream(relatedStr);
        while (getline(relStream, word, ',')) {
            if (!word.empty())
                t.relatedTopics.push_back(word);
        }

        topicMap[name] = t;
    }
    file.close();
}


//#endif // SWASTI_H