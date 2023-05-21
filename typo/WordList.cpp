#include "WordList.h"
#include "Point.h"

// Square root function implementation
float mySqrt(float x) {
    // Using Newton's method for square root approximation
    float guess = x;
    while (guess * guess - x > 0.001 || x - guess * guess > 0.001) {
        guess = (guess + x / guess) / 2;
    }
    return guess;
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
            float totalScore = 0.0;
            for (size_t i = 0; i < points.size(); ++i) {
                float dx = points[i].x - QWERTY[word[i] - 'a'].x;
                float dy = points[i].y - QWERTY[word[i] - 'a'].y;
                float distance = mySqrt(dx * dx + dy * dy);
                float score = 1.0 / (10.0 * distance * distance + 1.0);
                totalScore += score;
            }
            float wordScore = totalScore / static_cast<float>(points.size());

            // Check if the word score is above the cutoff and update the heap if necessary
            if (wordScore >= cutoff) {
                if (heap.count() < maxcount) {
                    heap.push(word, wordScore);
                } else if (wordScore > heap.top().score) {
                    heap.pop();
                    heap.push(word, wordScore);
                }
            }
        }
    }
    return heap;
}



