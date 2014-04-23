#include <iostream>
#include <memory>

#include "../priority_queue_set.hpp"
#include "../path_finder.hpp"

using namespace std;


template <typename T>
class equal_node{
public:
bool operator()(const std::shared_ptr<T>& left, const std::shared_ptr<T>& right) const{
  return *left == *right;
}
};


bool shared_node_equal_to(const std::shared_ptr<sol::_Node>& left, const std::shared_ptr<sol::_Node>& right){
    return *left == *right;
}

int main(void){
    sol::PriorityQueueSet<int> que;
    que.add(60);
    que.add(60);
    que.add(2);
    que.add(89);
    que.add(90);
    que.add(55);
    que.add(3);
    que.add(55);

    for (auto& item : que)
        std::cout << item << " ";
    std::cout << std::endl << "smallest: " << que.pop_smallest() << std::endl;
    for (auto& item : que)
        std::cout << item << " ";
    std::cout << std::endl << "smallest: " << que.pop_smallest() << std::endl;
    for (auto& item : que)
        std::cout << item << " ";
    std::cout << std::endl << "smallest: " << que.pop_smallest() << std::endl;
    for (auto& item : que)
        std::cout << item << " ";
    std::cout << std::endl << std::endl;



/*
    sol::PriorityQueueSet<shared_ptr<sol::_Node>,
        std::function<size_t(std::shared_ptr<sol::_Node>&)>,
        std::function<bool(std::shared_ptr<sol::_Node>&, std::shared_ptr<sol::_Node>&)>>
        open_list(std::hash<shared_ptr<sol::_Node>>, shared_node_equal_to);
*/
    sol::PriorityQueueSet<shared_ptr<sol::_Node>, std::hash<shared_ptr<sol::_Node>>,
    equal_node<sol::_Node>> open_list;

    open_list.add(shared_ptr<sol::_Node>(new sol::_Node(sf::Vector2i(20, 20))));
    open_list.add(shared_ptr<sol::_Node>(new sol::_Node(sf::Vector2i(20, 20))));
    open_list.add(shared_ptr<sol::_Node>(new sol::_Node(sf::Vector2i(19, 20))));
    shared_ptr<sol::_Node> n(new sol::_Node(sf::Vector2i(16, 20)));
    n->f_cost = 200;
    open_list.add(n);
    shared_ptr<sol::_Node> k(new sol::_Node(sf::Vector2i(16, 20)));
    k->f_cost = 20;
    open_list.add(k);

    auto item = *open_list.find(k);
    cout << "test find: " << item->f_cost << endl;


    for (auto& item : open_list)
        std::cout << item->coord.x << " " << item->coord.y << " " << item->f_cost << std::endl;

}
