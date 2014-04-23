#include <iostream>
using namespace std;

#include "path_finder.hpp"
#include "../priority_queue_set.hpp"

namespace sol{


bool _Node::operator==(const _Node& other) const {
    return coord == other.coord;
}

bool _Node::operator<(const _Node& other) const {
    return f_cost < other.f_cost;
}

bool _Node::operator>(const _Node& other) const {
    return f_cost > other.f_cost;
}


int PathFinder::_compute_g_cost(_Node& from, _Node& to) const{
    return _get_move_cost(from.coord, to.coord) + from.g_cost;
}

int PathFinder::_compute_f_cost(_Node& from, _Node& to) const{
    int f_cost = _get_heuristics_cost(from.coord, to.coord);
    f_cost += from.g_cost;
    return f_cost;
}


std::vector<sf::Vector2i> PathFinder::find_path(const sf::Vector2i& start, const sf::Vector2i& goal){
    PriorityQueueSet<_Node::Ptr, std::hash<_Node::Ptr>, equal_shared_ptr<_Node>> open_list;
    PriorityQueueSet<_Node::Ptr, std::hash<_Node::Ptr>, equal_shared_ptr<_Node>> closed_list;

    _Node::Ptr start_node(new _Node(start));
    _Node::Ptr end_node(new _Node(goal));

    start_node->f_cost = _compute_f_cost(*start_node, *end_node);

    open_list.add(start_node);
    _Node::Ptr current_node(nullptr);

    while (not open_list.empty()){

        current_node = open_list.pop_smallest();
        closed_list.add(current_node);

        if (/**current_node == *end_node or */closed_list.has(end_node)){

            std::vector<sf::Vector2i> result;
            _Node::Ptr node = current_node;
            while (node){
                result.push_back(node->coord);
                node = node->parent;
            }
            std::reverse(result.begin(), result.end());
            return std::move(result);
        }

        auto neighbors = _get_neighbors(current_node->coord);
        for (auto neighbor : neighbors) {
            _Node::Ptr neighbor_node(new _Node(neighbor));
            neighbor_node->g_cost = _compute_g_cost(*current_node, *neighbor_node);
            neighbor_node->f_cost = _compute_f_cost(*neighbor_node, *end_node);
            neighbor_node->parent = current_node;

            if (closed_list.has(neighbor_node)){
                continue;
            }

            if (not open_list.has(neighbor_node)){
                open_list.add(neighbor_node);
            }

            else {
                auto other_node = open_list.find(neighbor_node);
                if ((*other_node)->g_cost > neighbor_node->g_cost){
                    //int prev_g_cost = (*other_node)->g_cost;
                    (*other_node)->g_cost = neighbor_node->g_cost;
                    (*other_node)->parent = neighbor_node->parent;
                    (*other_node)->f_cost = _compute_f_cost(**other_node, *end_node);
                }
            }
        }
    }

    return std::vector<sf::Vector2i>();
} // end find_path()


} // end namespace sol
