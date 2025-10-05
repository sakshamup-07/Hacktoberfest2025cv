#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
    int capacity;
    list<pair<int,int>> dq; // key,value
    unordered_map<int, list<pair<int,int>>::iterator> mp;
public:
    LRUCache(int cap): capacity(cap) {}
    int get(int key) {
        if (mp.find(key)==mp.end()) return -1;
        auto it = mp[key];
        int val = it->second;
        dq.erase(it);
        dq.push_front({key,val});
        mp[key]=dq.begin();
        return val;
    }
    void put(int key,int value) {
        if (mp.find(key)!=mp.end()) dq.erase(mp[key]);
        else if (dq.size()==capacity) {
            auto last=dq.back(); dq.pop_back();
            mp.erase(last.first);
        }
        dq.push_front({key,value});
        mp[key]=dq.begin();
    }
};

int main() {
    LRUCache cache(3);
    cache.put(1,10);
    cache.put(2,20);
    cache.put(3,30);
    cout<<cache.get(1)<<endl;
    cache.put(4,40);
    cout<<cache.get(2)<<endl; // should be -1
}
