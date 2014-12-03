class LRUCache{
public:
    struct CacheNode {
        int key;
        int value;
        CacheNode(int k, int v):key(k),value(v){}
    };
    
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    //note: need update  CacheMap & CacheList
    int get(int key) {
        //exist
        if(CacheMap.find(key) != CacheMap.end())
        {
            CacheList.splice(CacheList.begin(), CacheList, CacheMap[key]);
            CacheMap[key] = CacheList.begin();
            return CacheMap[key]->value;
        }    
        else
            return -1;
    }
    
    void set(int key, int value) {
        //exits
        if(CacheMap.find(key) != CacheMap.end())
        {
            CacheMap[key]->value = value;//set value
            CacheList.splice(CacheList.begin(), CacheList, CacheMap[key]);//move node
            CacheMap[key] = CacheList.begin();//update map
        }
        else {
            //list is full
            if(CacheList.size() == capacity)
            {
                CacheMap.erase(CacheList.back().key);//erase map
                CacheList.pop_back();//pop list
            }
            CacheList.insert(CacheList.begin(), CacheNode(key, value));
            CacheMap[key] = CacheList.begin();//update map
        }
    }
private:
    int capacity;
    list<CacheNode> CacheList;
    unordered_map<int, list<CacheNode>::iterator > CacheMap;
};
