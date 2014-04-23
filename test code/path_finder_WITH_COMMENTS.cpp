#include <iostream>
using namespace std;

#include "path_finder.hpp"
#include "priority_queue_set.hpp"

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


std::vector<sf::Vector2i> PathFinder::find_path(sf::Vector2i start, sf::Vector2i end){
    PriorityQueueSet<_Node::Ptr, std::hash<_Node::Ptr>, equal_shared_ptr<_Node>> open_list;
    PriorityQueueSet<_Node::Ptr, std::hash<_Node::Ptr>, equal_shared_ptr<_Node>> closed_list;

    _Node::Ptr start_node(new _Node(start));
    _Node::Ptr end_node(new _Node(end));

    start_node->f_cost = _compute_f_cost(*start_node, *end_node);

    open_list.add(start_node);
    _Node::Ptr current_node(nullptr);

    while (not open_list.empty()){

        /*
        cout << "looping through the open_list before pop" << endl;
        for (auto item : open_list){
            cout << "item is: " << item->coord.x << " " << item->coord.y << endl;
            if (item->parent)
                cout << "parent is: " << item->parent->coord.x << " " << item->parent->coord.y << endl;
            else
                cout << "no parent" << endl;
            cout << "g_score is: " << item->g_cost << " f_score is: " << item->f_cost << endl << endl;
        }
        */

        //if (open_list.empty()){
        //    cout << "open list is empty";
        //    break;
        //}
        //cout << "popping least item" << endl;

        current_node = open_list.pop_smallest();
        //cout << "done popping least item" << endl;
        closed_list.add(current_node);

        // reconstruct the path
        if (/**current_node == *end_node or */closed_list.has(end_node)){

            /*
            cout << "entering reconstruction" << endl;
            cout << "looping through the open_list inside reconstruction" << endl;
            for (auto& item : open_list){
                cout << "item is: " << item->coord.x << " " << item->coord.y << endl;
                cout << "parent is: " << item->parent->coord.x << " " << item->parent->coord.y << endl << endl;
            }
            */

            std::vector<sf::Vector2i> result;
            _Node::Ptr node = current_node;
            //cout << "entering while" << endl;
            while (node){
                //cout << "pushing: " << node->coord.x << " " << node->coord.y << endl;
                result.push_back(node->coord);
                node = node->parent;
            }
            //cout << "returning results" << endl;
            std::reverse(result.begin(), result.end());
            return std::move(result);
        }

        //cout << "current point is " << current_node->coord.x << " " << current_node->coord.y << endl << endl;
        auto neighbors = _get_neighbors(current_node->coord);
        for (auto neighbor : neighbors) {
            //cout << "neighbor: " << neighbor.x << " " << neighbor.y << endl;
            _Node::Ptr neighbor_node(new _Node(neighbor));
            neighbor_node->g_cost = _compute_g_cost(*current_node, *neighbor_node);
            neighbor_node->f_cost = _compute_f_cost(*neighbor_node, *end_node);
            neighbor_node->parent = current_node;

            /*
            cout << "my parent is " << neighbor_node->parent->coord.x << " " << neighbor_node->parent->coord.y << endl;
            cout << "g cost: " << neighbor_node->g_cost << endl;
            cout << "parent g cost: " << neighbor_node->parent->g_cost << endl;
            cout << "f cost: " << neighbor_node->f_cost << endl;
            */


            if (closed_list.has(neighbor_node)){
                //cout << "already in the closed list!" << endl << endl;
                continue;
            }


            if (not open_list.has(neighbor_node)){
                open_list.add(neighbor_node);
                //cout << "not yet on the open_list so add it" << endl;
            }

            else {
                auto other_node = open_list.find(neighbor_node);
                if ((*other_node)->g_cost > neighbor_node->g_cost){
                    int prev_g_cost = (*other_node)->g_cost;
                    (*other_node)->g_cost = neighbor_node->g_cost;
                    (*other_node)->parent = neighbor_node->parent;
                    (*other_node)->f_cost = _compute_f_cost(**other_node, *end_node);
                    /*
                    cout << "already on the open_list but the g cost is better from " <<
                    prev_g_cost << " it got lower to " <<  neighbor_node->g_cost;
                    auto replaced_node = open_list.find(neighbor_node);
                    cout << " and new g_cost in open_list is: " << (*replaced_node)->g_cost << endl;
                    */
                }
            }

            //cout << endl << endl;
        }
    }

    //cout << "returning empty path!" << endl;
    return std::vector<sf::Vector2i>();
} // end find_path()


} // end namespace sol
