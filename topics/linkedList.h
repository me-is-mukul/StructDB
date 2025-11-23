#include "../classes.h"

void TopicGraph::loadLinkedListTopics() {
    topicMap["LinkedList"] = {"LinkedList", {"SinglyLL", "DoublyLL", "CircularLL"},
                              "https://gfg/linkedlist", 1};

    topicMap["SinglyLL"] = {"SinglyLL", {"Reversal"}, 
                            "https://gfg/sll", 2};
}
