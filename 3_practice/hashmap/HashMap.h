#include <vector>
#include <list>
#include <functional>
#include"ReadWriteLock.h"
#include "RBtree.h"  

// 每个Bucket可以是一个链表或者红黑树
template<typename K, typename V>
struct Bucket {
    enum class Type { LIST, TREE };
    Type type;
    union {
        std::list<std::pair<K, V>>* list;
        RBTree<K, V>* tree;
    };

    Bucket() : type(Type::LIST), list(new std::list<std::pair<K, V>>) {}
    ~Bucket() {
        if (type == Type::LIST) delete list;
        else delete tree;
    }
};

template<typename K, typename V>
class HashMap {
private:
    static const size_t INITIAL_CAPACITY = 16;
    static const size_t TREEIFY_THRESHOLD = 8;
    static const size_t UNTREEIFY_THRESHOLD = 6;
    static constexpr double LOAD_FACTOR = 0.75;

    std::vector<Bucket<K, V>> buckets;
    size_t size;
    size_t capacity;
    mutable ReadWriteLock rwLock;

    size_t hash(const K& key) const {
        size_t hashValue = std::hash<K>{}(key);
        hashValue ^= (hashValue >> 20) ^ (hashValue >> 12);
        return (hashValue ^ (hashValue >> 7) ^ (hashValue >> 4)) % capacity;
    }

    void resize() {
        size_t oldCapacity = capacity;
        capacity *= 2;
        std::vector<Bucket<K, V>> newBuckets(capacity);

        for (auto& oldBucket : buckets) {
            if (oldBucket.type == Bucket<K, V>::Type::LIST) {
                for (const auto& pair : *oldBucket.list) {
                    size_t newHash = hash(pair.first);
                    newBuckets[newHash].list->push_back(pair);
                }
            } else {
                oldBucket.tree->inorderTraversal([this, &newBuckets](const K& key, const V& value) {
                    size_t newHash = hash(key);
                    newBuckets[newHash].list->push_back({key, value});
                });
            }
        }

        buckets = std::move(newBuckets);
    }

    void treeifyBucket(Bucket<K, V>& bucket) {
        RBTree<K, V>* tree = new RBTree<K, V>();
        for (const auto& pair : *bucket.list) {
            tree->insert(pair.first, pair.second);
        }
        delete bucket.list;
        bucket.tree = tree;
        bucket.type = Bucket<K, V>::Type::TREE;
    }

    void untreeifyBucket(Bucket<K, V>& bucket) {
        std::list<std::pair<K, V>>* list = new std::list<std::pair<K, V>>();
        bucket.tree->inorderTraversal([list](const K& key, const V& value) {
            list->push_back({key, value});
        });
        delete bucket.tree;
        bucket.list = list;
        bucket.type = Bucket<K, V>::Type::LIST;
    }

public:
    HashMap() : buckets(INITIAL_CAPACITY), size(0), capacity(INITIAL_CAPACITY) {}

    void put(const K& key, const V& value) {
        rwLock.lockWrite();
        if (size >= capacity * LOAD_FACTOR) {
            resize();
        }

        size_t h = hash(key);
        Bucket<K, V>& bucket = buckets[h];

        if (bucket.type == Bucket<K, V>::Type::LIST) {
            for (auto& pair : *bucket.list) {
                if (pair.first == key) {
                    pair.second = value;
                    rwLock.unlockWrite();
                    return;
                }
            }
            bucket.list->push_back({key, value});
            size++;

            if (bucket.list->size() >= TREEIFY_THRESHOLD) {
                treeifyBucket(bucket);
            }
        } else {
            V oldValue;
            if (bucket.tree->find(key, oldValue)) {
                bucket.tree->remove(key);
                size--;
            }
            bucket.tree->insert(key, value);
            size++;
        }
        rwLock.unlockWrite();
    }

    bool get(const K& key, V& value) const {
        rwLock.lockRead();
        size_t h = hash(key);
        const Bucket<K, V>& bucket = buckets[h];

        if (bucket.type == Bucket<K, V>::Type::LIST) {
            for (const auto& pair : *bucket.list) {
                if (pair.first == key) {
                    value = pair.second;
                    rwLock.unlockRead();
                    return true;
                }
            }
        } else {
            bool found = bucket.tree->find(key, value);
            rwLock.unlockRead();
            return found;
        }
        rwLock.unlockRead();
        return false;
    }

    bool remove(const K& key) {
        rwLock.lockWrite();
        size_t h = hash(key);
        Bucket<K, V>& bucket = buckets[h];

        if (bucket.type == Bucket<K, V>::Type::LIST) {
            for (auto it = bucket.list->begin(); it != bucket.list->end(); ++it) {
                if (it->first == key) {
                    bucket.list->erase(it);
                    size--;
                    rwLock.unlockWrite();
                    return true;
                }
            }
        } else {
            if (bucket.tree->remove(key)) {
                size--;
                if (bucket.tree->getSize() <= UNTREEIFY_THRESHOLD) {
                    untreeifyBucket(bucket);
                }
                rwLock.unlockWrite();
                return true;
            }
        }
        rwLock.unlockWrite();
        return false;
    }

    size_t getSize() const {
        rwLock.lockRead();
        size_t currentSize = size;
        rwLock.unlockRead();
        return currentSize;
    }

    bool isEmpty() const {
        rwLock.lockRead();
        bool empty = size == 0;
        rwLock.unlockRead();
        return empty;
    }
    std::string isTree(){
        std::string res;
        for(auto& bucket : buckets){
            if(bucket.type == Bucket<K, V>::Type::LIST){
                return "false";
            }else{
                res = "true";
            }
        }
        return res;
    }
};
