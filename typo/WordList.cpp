#include "WordList.h"

// Helper function to calculate the square of a number
float square(float num) {
    return num * num;
}

WordList::WordList(std::istream& stream) {
    std::string word;
    char c;
    while (getline(stream, word)) {
        bool valid = true;
        for (size_t i = 0; i < word.size(); ++i) {
            c = word[i];
            if (!(c >= 'a' && c <= 'z')) {
                valid = false;
                break;
            }
        }
        if (valid) {
            mWords.push_back(word);
        }
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    struct ScoredWord {
        std::string word;
        float score;
    };

    std::vector<ScoredWord> scoredWords;
    for (size_t i = 0; i < mWords.size(); ++i) {
        const std::string& word = mWords[i];
        if (word.size() != points.size()) {
            continue;
        }

        float wordScore = 0.0f;
        for (size_t j = 0; j < word.size(); ++j) {
            const Point& point = QWERTY[word[j] - 'a'];
            float dx = points[j].x - point.x;
            float dy = points[j].y - point.y;
            float distance = square(dx) + square(dy);
            float letterScore = 1.0f / (10 * distance + 1);
            wordScore += letterScore;
        }
        wordScore /= word.size();

        if (wordScore >= cutoff) {
            scoredWords.push_back({word, wordScore});
            if (scoredWords.size() > maxcount) {
                std::sort(scoredWords.begin(), scoredWords.end(), [](const ScoredWord& a, const ScoredWord& b) {
                    return a.score > b.score;
                });
                scoredWords.pop_back();
            }
        }
    }

    Heap result(scoredWords.size());
    for (const ScoredWord& scoredWord : scoredWords) {
        result.push(scoredWord.word, scoredWord.score);
    }

    return result;
}
