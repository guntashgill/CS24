#include "WordList.h"
#include "Point.h"

// Helper function to calculate the square of a number
float square(float num) {
    return num * num;
}

// Helper function to calculate the square root of a number using Newton's method
float sqrt(float num) {
    float x = num;
    float y = 1.0;
    float epsilon = 0.000001;
    while (x - y > epsilon) {
        x = (x + y) / 2.0;
        y = num / x;
    }
    return x;
}

WordList::WordList(std::istream& stream) {
    std::string word;
    char line[256];
    while (stream.getline(line, sizeof(line))) {
        size_t i = 0;
        while (line[i] != '\0') {
            if (line[i] < 'a' || line[i] > 'z')
                break;
            i++;
        }
        if (line[i] == '\0')
            mWords.push_back(line);
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap heap(maxcount);
    for (const std::string& word : mWords) {
        if (word.length() == points.size()) {
            // Calculate the score for the word using the provided scoring algorithm
            float score = 0.0;
            for (size_t i = 0; i < points.size(); ++i) {
                float dx = points[i].x - QWERTY[word[i] - 'a'].x;
                float dy = points[i].y - QWERTY[word[i] - 'a'].y;
                float distance = sqrt(square(dx) + square(dy));
                score += 1.0 / (1.0 + distance);
            }

            // Check if the score is above the cutoff and update the heap if necessary
            if (score >= cutoff) {
                if (heap.count() < maxcount) {
                    heap.push(word, score);
                } else if (score > heap.top().score) {
                    heap.pop();
                    heap.push(word, score);
                }
            }
        }
    }
    return heap;
}



