#pragma once
#include <set>
#include <string>
#include <vector>

#include "document.h"
#include "paginator.h"

std::vector<std::string> SplitIntoWords(const std::string& text);

template <typename StringContainer>
std::set<std::string> MakeUniqueNonEmptyStrings(const StringContainer& strings)
{
    std::set<std::string> non_empty_strings;

    for (const std::string& str : strings)
    {
        if (!str.empty())
        {
            non_empty_strings.insert(str);
        }
    }
    
    return non_empty_strings;
}

std::ostream& operator<<(std::ostream& os, const Document& document);

template <typename It>
std::ostream& operator<<(std::ostream& os, const IteratorRange<It>& range) {
    for (auto item = range.begin(); item != range.end(); ++item) {
        os << *item;
    }

    return os;
}
