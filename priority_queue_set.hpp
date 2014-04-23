#ifndef SOL_PRIORITY_QUEUE_SET_HPP
#define SOL_PRIORITY_QUEUE_SET_HPP


#include <unordered_set>
#include <deque>
#include <functional>
#include <algorithm>
#include <iostream>



namespace sol{


template <typename T, typename Hasher = std::hash<T>, typename EqualTo = std::equal_to<T>>
class PriorityQueueSet{
public:
    PriorityQueueSet(){}
    //PriorityQueueSet(Hasher hasher, EqualTo equal_to): _set(5, hasher, equal_to) {}

    using iterator = typename std::deque<T>::iterator;

    iterator begin();
    iterator end();

    bool    add(const T& item);
    T       pop_smallest(); // returns the item; not suitable for large data items
    typename std::unordered_set<T, Hasher, EqualTo>::iterator find(const T& item);
    bool    has(const T& item);
    bool    empty();

private:
    std::deque<T>           _deque;
    std::unordered_set<T, Hasher, EqualTo>   _set;
};


template <typename T, typename Hasher, typename EqualTo>
typename PriorityQueueSet<T, Hasher, EqualTo>::iterator PriorityQueueSet<T, Hasher, EqualTo>::begin(){
    return _deque.begin();
}

template <typename T, typename Hasher, typename EqualTo>
typename PriorityQueueSet<T, Hasher, EqualTo>::iterator PriorityQueueSet<T, Hasher, EqualTo>::end(){
    return _deque.end();
}

template <typename T, typename Hasher, typename EqualTo>
bool PriorityQueueSet<T, Hasher, EqualTo>::add(const T& item){
    if (not _set.count(item)){
        _deque.push_back(item);
        std::push_heap(_deque.begin(), _deque.end(), std::greater<T>());
        _set.insert(item);
        return true;
    }
    else if (item < *_set.find(item)){
        _set.erase(item);
        _set.insert(item);
        _deque.erase(std::find(_deque.begin(), _deque.end(), item));
        _deque.push_back(item);
        std::make_heap(_deque.begin(), _deque.end(), std::greater<T>());
        return true;
    }

    return false;
}

template <typename T, typename Hasher, typename EqualTo>
T PriorityQueueSet<T, Hasher, EqualTo>::pop_smallest(){
    std::pop_heap(_deque.begin(), _deque.end(), std::greater<T>());
    auto item = _deque.back();
    _deque.pop_back();
    //std::cout << "returning " << item.coord.x << " " << item.coord.y << std::endl;
    //if (item.parent)
    //std::cout << "its parent is " << item.parent->coord.x << " " << item.parent->coord.y << std::endl;
    return item;
}

template <typename T, typename Hasher, typename EqualTo>
typename std::unordered_set<T, Hasher, EqualTo>::iterator PriorityQueueSet<T, Hasher, EqualTo>::find(const T& item){
    return _set.find(item);
}

template <typename T, typename Hasher, typename EqualTo>
bool PriorityQueueSet<T, Hasher, EqualTo>::has(const T& item){
    return _set.count(item);
}

template <typename T, typename Hasher, typename EqualTo>
bool PriorityQueueSet<T, Hasher, EqualTo>::empty(){
    return _deque.empty();
}


} // end namespace sol


#endif // SOL_PRIORITY_QUEUE_SET_HPP
