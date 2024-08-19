
#include <mutex>
#include <condition_variable>
class ReadWriteLock {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int readers = 0;
    bool writer = false;

public:
    void lockRead() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !writer; });
        readers++;
    }

    void unlockRead() {
        std::lock_guard<std::mutex> lock(mtx);
        readers--;
        if (readers == 0) cv.notify_all();
    }

    void lockWrite() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !writer && readers == 0; });
        writer = true;
    }

    void unlockWrite() {
        std::lock_guard<std::mutex> lock(mtx);
        writer = false;
        cv.notify_all();
    }
};