#pragma once

#include <mutex>
#include <queue>
#include <string>
#include <condition_variable>

template <class T>
class Jobs
{
public:
    // inserisce un job in coda in attesa di essere processato, può
    // essere bloccante se la coda dei job è piena
    void put(T job);
    // legge un job dalla coda e lo rimuove
    // si blocca se non ci sono valori in coda
    T get();
};

class StringJobs : public Jobs<std::string>
{
private:
    std::mutex m_buffer;
    std::condition_variable cv_put, cv_get;
    std::queue<std::string> jobs_buffer;

public:
    void put(std::string job);
    std::string get();
};