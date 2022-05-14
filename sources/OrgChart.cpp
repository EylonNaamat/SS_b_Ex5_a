//
// Created by eylon on 5/11/22.
//
#include "OrgChart.hpp"
#include <exception>

namespace ariel{
//    std::string& OrgChart::Iterator::operator*() {
//        return this->_ptr->name;
//    }
//
//    bool OrgChart::Iterator::operator!=(OrgChart::Iterator& itr){
//        if(this->_ptr != itr._ptr){
//            return true;
//        }
//        return false;
//    }
//
//    int OrgChart::Iterator::operator->(){
//        return this->_ptr->subs.size();
//    }
//
//
//    OrgChart::Node* OrgChart::Iterator::get_ptr(){
//        return this->_ptr;
//    }
//
//    OrgChart::Iterator_Level_Order& OrgChart::Iterator_Level_Order::operator++(){
//        if(this->q.empty()){
//            this->_ptr = nullptr;
//        }else{
//            Node* tmp = this->q.front();
//            this->q.pop();
//            if(tmp->subs.size() != 0){
//                for(int i = 0; i < tmp->subs.size(); ++i){
//                    this->q.push(tmp->subs[(uint)i]);
//                }
//            }
//        }
//        return *this;
//    }
//
//    OrgChart::Iterator_Level_Order OrgChart::Iterator_Level_Order::operator++(int){
//        Iterator_Level_Order itr = *this;
//        if(this->q.empty()){
//            this->_ptr = nullptr;
//        }else{
//            Node* tmp = this->q.front();
//            this->q.pop();
//            if(tmp->subs.size() != 0){
//                for(int i = 0; i < tmp->subs.size(); ++i){
//                    this->q.push(tmp->subs[(uint)i]);
//                }
//            }
//        }
//        return itr;
//    }
//
//    OrgChart::Iterator_Level_Order OrgChart::begin_level_order(){
//        return OrgChart::Iterator_Level_Order(this->root);
//    }
//
//
//    OrgChart::Iterator_Level_Order OrgChart::end_level_order(){
//        return OrgChart::Iterator_Level_Order(nullptr);
//    }
//
//    OrgChart& OrgChart::add_root(std::string name){
//        if(this->root != nullptr){
//            this->root->name = name;
//        }else{
//            Node* tmp = new Node(name);
//            this->root = tmp;
//        }
//        return *this;
//    }
//
//    OrgChart::Node* OrgChart::find(std::string name){
//        Node* ans = nullptr;
//        for(Iterator_Level_Order itr = this->begin_level_order(); (itr != this->end_level_order()); ++itr){
//            if((*itr) == name){
//                ans = itr.get_ptr();
//                break;
//            }
//        }
//        return ans;
//    }
//
//    OrgChart& OrgChart::add_sub(std::string father, std::string name){
//        Node* tmp = find(father);
//        if(tmp == nullptr){
//            throw "father dont exist";
//        }
//        Node* new_member;
//        new_member->name = name;
//        tmp->subs.push_back(new_member);
//    }

    std::ostream& operator<<(std::ostream& os, OrgChart& org){
        std::string str = "";
        os << OrgChart::helper(str, "", org.root);
        return os;
    }

    std::string& OrgChart::helper(std::string& str, std::string prefix, OrgChart::Node* node){
        str += prefix;
        if(str.size() != 0){
            str += "-";
        }
        str += node->name;
        str += "\n";
        for(int i = 0; i < node->subs.size(); ++i){
             OrgChart::helper(str, prefix + "\t", node->subs[(uint)i]);
        }
        return str;
    }
}