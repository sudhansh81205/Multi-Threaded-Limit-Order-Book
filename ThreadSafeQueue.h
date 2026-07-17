#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

template<typename T>
class ThreadSafeQueue
{
private:
    queue<T> q;
    mutex mtx;
    condition_variable cv;

public:
    void push(const T& item)
    {
        lock_guard<mutex> lock(mtx);
        q.push(item);
        cv.notify_one();
    }

    T pop()
    {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [this]
        {
            return !q.empty();
        });

        T item = q.front();
        q.pop();

        return item;
    }

    bool empty()
    {
        lock_guard<mutex> lock(mtx);
        return q.empty();
    }
};

#endif