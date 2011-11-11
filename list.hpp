#ifndef LIST_HPP
#define LIST_HPP

#include <vector>
#include <map>

#error unused

template<typename T> class vList
{
private:
    vector<T> _items;
public:
    vList();
    vList<T>& Add(T item)
    {
        _items.push_back(T);
        return *this;
    }
    vList<T>& operator()(T item)
    {
        return Add(item);
    }
    operator vector<T>()
    {
        return _items;
    }
};

template<typename K, typename V> class mList
{
private:
    map<K,V> _items;
public:
    mList();
    mList<K,V>& Add(K key, V val)
    {
        _items[key]=val;
        return *this;
    }
    mList<K,V>& operator()(K key, V val)
    {
        return Add(key,val);
    }
    operator map<K,V>()
    {
        return _items;
    }
};

#endif // LIST_HPP
