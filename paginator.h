#pragma once
#include <vector>

template <typename It>
class IteratorRange {
public:
    IteratorRange(It begin, It end) : begin_(begin), end_(end) {
        size_ = distance(begin, end);
    }
    It begin() const {
        return begin_;
    }
    It end() const {
        return end_;
    }
    size_t size() const {
        return size_;
    }

private:
    It begin_, end_;
    size_t size_;
};

template <typename Iterator>
class Paginator {
    // тело класса
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) : begin_(begin), end_(end), page_size_(page_size) {
        size_t size = distance(begin, end);
        size_t pages = size / page_size;

        if (size % page_size != 0) {
            pages++;
        }
        for (size_t i = 0; i < pages; i++) {
            pages_.push_back({ next(begin, i * page_size), next(begin, std::min((i + 1) * page_size, size)) });
        }
    }
    auto begin() const {
        return pages_.begin();
    }
    auto end() const {
        return pages_.end();
    }
    size_t size() const {
        return pages_.size();
    }
    auto operator[](size_t index) const {
        return pages_[index];
    }
private:
    Iterator begin_;
    Iterator end_;
    size_t page_size_;
    std::vector<IteratorRange<Iterator>> pages_;
};

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}