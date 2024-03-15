#pragma once
#include <deque>
#include <string>
#include <vector>

#include "document.h"
#include "search_server.h"


class RequestQueue
{
public:
    explicit RequestQueue(const SearchServer& search_server);

    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate)
    {
        auto data = search_server_.FindTopDocuments(raw_query, document_predicate);
        PushRequest(raw_query, data);
        return data;
    }

    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string& raw_query);
    int GetNoResultRequests() const;

private:
    struct QueryResult
    {
        bool isFind;
        int time;
        std::string request;
    };

    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    const SearchServer& search_server_;

    void PushRequest(const std::string& raw_query, std::vector<Document>& data);
};
