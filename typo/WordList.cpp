#include "WordList.h"
#include "Heap.h"
#include "Point.h"
#include <vector>
#include <fstream>
#include <cmath>

WordList::WordList(std::istream& stream) {
    std::string word;
    while (std::getline(stream, word)) {
        bool isLowercase = true;
        for (char c : word) {
            if (c < 'a' || c > 'z') {
                isLowercase = false;
                break;
            }
        }
        if (isLowercase)
            mWords.push_back(word);
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap heap(maxcount);
    for (const std::string& word : mWords) {
        if (word.length() == points.size()) {
            float totalScore = 0.0;
            for (size_t i = 0; i < points.size(); ++i) {
                const Point& touchPoint = points[i];
                const Point& keyLocation = QWERTY[word[i] - 'a'];
                float distance = std::sqrt(std::pow(touchPoint.x - keyLocation.x, 2) +
                                           std::pow(touchPoint.y - keyLocation.y, 2));
                float score = 1.0 / (10.0 * std::pow(distance, 2) + 1.0);
                totalScore += score;
            }
            float wordScore = totalScore / static_cast<float>(points.size());
            if (wordScore >= cutoff)
                heap.insert(wordScore, word);
        }
    }
    return heap;
}






