//
// Created by asice-cloud on 24-8-12.
//

#include <shared_mutex>

class ReadWriteLock {
public:
    void lockRead() {
        mutex_.lock_shared();
    }

    void unlockRead() {
        mutex_.unlock_shared();
    }

    void lockWrite() {
        mutex_.lock();
    }

    void unlockWrite() {
        mutex_.unlock();
    }

private:
    std::shared_mutex mutex_;
};

