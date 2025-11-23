#include <classes.h>

int main() {
    TopicGraph graph;

    // Load all topic modules
    graph.loadArrayTopics();
    graph.loadLinkedListTopics();
    graph.loadSortingTopics();
    graph.loadStackTopics();
    graph.loadQueueTopics();
    graph.loadGraphTopics();
    graph.loadTreeTopics();

    string topic;
    cout << "\nEnter topic: ";
    cin >> topic;

    graph.showRelated(topic);

    cout << "\nBFS Learning Path: ";
    graph.showLearningPath(topic);

    unordered_set<string> visited;
    cout << "\nDFS Depth: ";
    graph.dfsTraversal(topic, visited);
    cout << "END\n";

    return 0;
}
