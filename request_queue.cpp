#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server) : search_server_(search_server)
{
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status)
{
    // напишите реализацию
    auto data = search_server_.FindTopDocuments(raw_query, status);
    PushRequest(raw_query, data);
    return data;
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query)
{
    // напишите реализацию
    auto data = search_server_.FindTopDocuments(raw_query);
    PushRequest(raw_query, data);
    return data;
}

int RequestQueue::GetNoResultRequests() const
{
    // напишите реализацию
    return std::count_if(requests_.begin(), requests_.end(), [](const QueryResult& result)
        { return result.isFind; });
}

void RequestQueue::PushRequest(const std::string& raw_query, std::vector<Document>& data)
{
    int time = requests_.size() + 1;

    if (time > min_in_day_)
    {
        time = min_in_day_;
        requests_.pop_back();
    }

    QueryResult result;

    if (data.empty())
    {
        result = { true, time, raw_query };
    }
    else
    {
        result = { false, time, raw_query };
    }

    requests_.push_front(result);
}