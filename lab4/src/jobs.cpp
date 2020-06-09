#include "lib/jobs.h"

#define MAX_QUEUE 100

void StringJobs::put(std::string job)
{
    std::unique_lock<std::mutex> lock(this->m_buffer);
    this->cv_put.wait(lock, [&]() { return jobs_buffer.size() < MAX_QUEUE; });
    this->jobs_buffer.push(job);
    this->cv_get.notify_all(); // riabilito/sveglio la get
}

std::string StringJobs::get()
{
    std::unique_lock<std::mutex> lock(this->m_buffer);
    this->cv_get.wait(lock, [&]() { return jobs_buffer.size() > 0; });
    std::string result = this->jobs_buffer.front();
    if (result.compare("CIAONE") != 0 && result.compare("CIAONE_FILE") != 0)
        this->jobs_buffer.pop();
    if (this->jobs_buffer.size() < MAX_QUEUE)
        this->cv_put.notify_all(); // riabilito/sveglio la put
    return result;
}