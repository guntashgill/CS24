#include "WordList.h"
#include "Point.h"

float mySqrt(float x) {
    float guess = x;
    while (guess * guess - x > 0.001 || x - guess * guess > 0.001) {
        guess = (guess + x / guess) / 2;
    }
    return guess;
}

bool isValidWord(const std::string& word) {
    for (char c : word) {
        if (c < 'a' || c > 'z') {
            return false;
        }
    }
    return true;
}

WordList::WordList(std::istream& stream) {
    std::string word;
    while (std::getline(stream, word)) {
        if (isValidWord(word)) {
            mWords.push_back(word);
        }
    }
}

float calculateDistance(const Point& p1, const Point& p2) {
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    return mySqrt(dx * dx + dy * dy);
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap heap(maxcount);
    for (const std::string& word : mWords) {
        if (word.length() == points.size()) {
            float totalScore = 0.0;
            for (size_t i = 0; i < points.size(); ++i) {
                float dx = points[i].x - QWERTY[word[i] - 'a'].x;
                float dy = points[i].y - QWERTY[word[i] - 'a'].y;
                float distance = calculateDistance(points[i], QWERTY[word[i] - 'a']);
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



