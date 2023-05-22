#include "WordList.h"
#include "Point.h"
#include <cmath>

float mySqrt(float x) {
    float guess = x;
    while (std::abs(guess * guess - x) >= 0.0001) {
        guess = (guess + x / guess) / 2;
    }
    return guess;
}

WordList::WordList(std::istream& stream) {
    std::string word;
    std::string line;
    while (std::getline(stream, line)) {
        bool isLowerCase = true;
        for (char c : line) {
            if (c < 'a' || c > 'z') {
                isLowerCase = false;
                break;
            }
        }
        if (isLowerCase)
            mWords.push_back(line);
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap heap(maxcount);
    for (const std::string& word : mWords) {
        if (word.length() == points.size()) {
            float totalScore = 0.0;
            for (size_t i = 0; i < points.size(); ++i) {
                float dx = points[i].x - QWERTY[word[i] - 'a'].x;
                float dy = points[i].y - QWERTY[word[i] - 'a'].y;
                float distance = mySqrt(dx * dx + dy * dy);
                float score = 1.0 / (10.0 * distance * distance + 1.0);
                totalScore += score;
            }
            float wordScore = totalScore / static_cast<float>(points.size());

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
