#include <iostream>
#include <string>
#include "HashMap.h"
#include <thread>
#include <vector>

void normal_testHashMap() {
    HashMap<std::string, int> map;

    // 测试插入
    map.put("asice", 17);
    map.put("winter", 19);
    map.put("charlotte", 19);
    map.put("dream", 19);

    // 测试获取
    int value;
    if (map.get("winter", value)) {
        std::cout << "Value for 'winter': " << value << std::endl;
    } else {
        std::cout << "Key 'winter' not found" << std::endl;
    }

    std::cout << "Size: " << map.getSize() << std::endl;

    // 测试删除
    if (map.remove("dream")) {
        std::cout << "Key 'dream' removed successfully" << std::endl;
    } else {
        std::cout << "Failed to remove key 'odream'" << std::endl;
    }

    std::cout << "Size after removal: " << map.getSize() << std::endl;

    // 测试更新
    map.put("winter", 22);
    if (map.get("winter", value)) {
        std::cout << "Updated value for 'winter': " << value << std::endl;
    }

    // 测试大量插入以触发树化和扩容
    for (int i = 0; i < 100; i++) {
        map.put("key" + std::to_string(i), i);
    }

    std::cout << "Size after adding 100 elements: " << map.getSize() << std::endl;

    // 测试获取不存在的键
    if (!map.get("nonexistent", value)) {
        std::cout << "Key 'nonexistent' not found, as expected" << std::endl;
    }
}

namespace safe
{
    void testConcurrentInsert(HashMap<std::string, int>& map, int start, int end) {
        for (int i = start; i < end; ++i) {
            map.put("key" + std::to_string(i), i);
        }
    }

    void testConcurrentGet(HashMap<std::string, int>& map, int start, int end) {
        int value;
        for (int i = start; i < end; ++i) {
            map.get("key" + std::to_string(i), value);
        }
    }

    void testConcurrentRemove(HashMap<std::string, int>& map, int start, int end) {
        for (int i = start; i < end; ++i) {
            map.remove("key" + std::to_string(i));
        }
    }

    void testThreadSafety() {
        HashMap<std::string, int> map;

        // 创建线程进行并发插入
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back(testConcurrentInsert, std::ref(map), i * 100, (i + 1) * 100);
        }
        for (auto& thread : threads) {
            thread.join();
        }

        std::cout << "Size after concurrent insert: " << map.getSize() << std::endl;

        // 创建线程进行并发读取
        threads.clear();
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back(testConcurrentGet, std::ref(map), i * 100, (i + 1) * 100);
        }
        for (auto& thread : threads) {
            thread.join();
        }

        // 创建线程进行并发删除
        threads.clear();
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back(testConcurrentRemove, std::ref(map), i * 100, (i + 1) * 100);
        }
        for (auto& thread : threads) {
            thread.join();
        }

        std::cout << "Size after concurrent remove: " << map.getSize() << std::endl;
    }
}


int main() {
    normal_testHashMap();
    std::cout<<'\n';
    safe::testThreadSafety();
    return 0;
}