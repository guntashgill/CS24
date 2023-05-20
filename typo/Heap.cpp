#include "Heap.h"
#include <stdexcept>

Heap::Heap(size_t capacity)
    : mData(new Entry[capacity]), mCapacity(capacity), mCount(0) {}

Heap::Heap(const Heap& other)
    : mData(new Entry[other.mCapacity]), mCapacity(other.mCapacity), mCount(other.mCount) {
    for (size_t i = 0; i < mCount; i++) {
        mData[i] = other.mData[i];
    }
}

Heap::Heap(Heap&& other)
    : mData(other.mData), mCapacity(other.mCapacity), mCount(other.mCount) {
    other.mData = nullptr;
    other.mCapacity = 0;
    other.mCount = 0;
}

Heap::~Heap() {
    delete[] mData;
}

size_t Heap::capacity() const {
    return mCapacity;
}

size_t Heap::count() const {
    return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const {
    if (index >= mCount) {
        throw std::out_of_range("Index out of range");
    }
    return mData[index];
}

Heap::Entry Heap::pop() {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }

    Entry entry = mData[0];
    mCount--;
    mData[0] = mData[mCount];

    size_t parent = 0;
    size_t child = 1;

    while (child < mCount) {
        if (child + 1 < mCount && mData[child + 1].score < mData[child].score) {
            child++;
        }

        if (mData[parent].score <= mData[child].score) {
            break;
        }

        std::swap(mData[parent], mData[child]);
        parent = child;
        child = parent * 2 + 1;
    }

    return entry;
}

void Heap::push(const std::string& value, float score) {
    if (mCount == mCapacity) {
        throw std::overflow_error("Heap is full");
    }

    size_t index = mCount;
    mCount++;
    mData[index].value = value;
    mData[index].score = score;

    size_t parent = (index - 1) / 2;
    while (index > 0 && mData[index].score < mData[parent].score) {
        std::swap(mData[index], mData[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }

    Entry entry = mData[0];
    if (score > entry.score) {
        mData[0].value = value;
        mData[0].score = score;
        size_t parent = 0;
        size_t child = 1;

        while (child < mCount) {
            if (child + 1 < mCount && mData[child + 1].score < mData[child].score) {
                child++;
            }

            if (mData[parent].score <= mData[child].score) {
                break;
            }

            std::swap(mData[parent], mData[child]);
            parent = child;
            child = parent * 2 + 1;
        }
    }

    return entry;
}

const Heap::Entry& Heap::top() const {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    return mData[0];
}
