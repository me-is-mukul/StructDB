#include "../classes.h"

void TopicGraph::loadArrayTopics() {
    topicMap["Array"] = {"Array", {"Searching", "Sorting"}, 
                         "https://gfg/array", 1};

    topicMap["Searching"] = {"Searching", {"BinarySearch", "LinearSearch"},
                             "https://gfg/searching", 1};

    topicMap["Sorting"] = {"Sorting", {"QuickSort", "MergeSort"},
                           "https://gfg/sorting", 2};

    topicMap["BinarySearch"] = {"BinarySearch", {}, 
                                "https://gfg/binarysearch", 2};
}
