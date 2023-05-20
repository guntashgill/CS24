#include "WordList.h"
#include <fstream>

WordList::WordList(std::istream& stream) {
    std::string word;
    while (std::getline(stream, word)) {
        bool isLowercaseASCII = true;
        for (char ch : word) {
            if (!(ch >= 'a' && ch <= 'z')) {
                isLowercaseASCII = false;
                break;
            }
        }
        if (isLowercaseASCII)
            mWords.push_back(word);
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap heap(maxcount);

    for (const std::string& word : mWords) {
        if (word.length() == points.size()) {
            float score = 0.0f;
            for (size_t i = 0; i < points.size(); ++i) {
                float dx = points[i].x - QWERTY[word[i] - 'a'].x;
                float dy = points[i].y - QWERTY[word[i] - 'a'].y;
                float distance = std::sqrt(dx * dx + dy * dy);
                score += 1.0f / (10.0f * distance * distance + 1.0f);
            }
            score /= static_cast<float>(points.size());

            if (score >= cutoff)
                heap.push(word, score);
        }
    }

    return heap;
}

