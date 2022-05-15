//
// Created by eylon on 5/11/22.
//
#include "OrgChart.hpp"
#include <exception>

namespace ariel{

    std::string&  OrgChart::Iterator::operator*(){
        return this->_ptr->name;
    }

    bool OrgChart::Iterator::operator!=(const Iterator& itr){
        bool ans = false;
        if(this->_ptr != itr._ptr){
            ans = true;
        }
        return ans;
    }

    std::string* OrgChart::Iterator::operator->(){
        return &(this->_ptr->name);
    }

    OrgChart::Node* OrgChart::Iterator::get_ptr(){
        return this->_ptr;
    }

    OrgChart::Iterator_Level_Order& OrgChart::Iterator_Level_Order::operator++(){
        if(this->q.empty()){
            this->_ptr = nullptr;
        }else{
            this->q.pop();
            if(this->q.empty()){
                this->_ptr = nullptr;
            }else{
                this->_ptr = this->q.front();
            }
        }
        return *this;
    }

    OrgChart::Iterator_Level_Order OrgChart::Iterator_Level_Order::operator++(int){
        OrgChart::Iterator_Level_Order itr = *this;
        if(this->q.empty()){
            this->_ptr = nullptr;
        }else{
            this->q.pop();
            if(this->q.empty()){
                this->_ptr = nullptr;
            }else{
                this->_ptr = this->q.front();
            }
        }
        return itr;
    }

    OrgChart::Iterator_Reverse_Level_Order& OrgChart::Iterator_Reverse_Level_Order::operator++(){
        if(this->stk.empty()){
            this->_ptr = nullptr;
        }else{
            this->_ptr = this->stk.top();
            this->stk.pop();
        }
        return *this;
    }

    OrgChart::Iterator_Reverse_Level_Order OrgChart::Iterator_Reverse_Level_Order::operator++(int){
        OrgChart::Iterator_Reverse_Level_Order itr = *this;
        if(this->stk.empty()){
            this->_ptr = nullptr;
        }else{

            this->stk.pop();
            this->_ptr = this->stk.top();
        }
        return itr;
    }

    OrgChart::Iterator_Preorder& OrgChart::Iterator_Preorder::operator++(){
        if(this->stk.empty()){
            this->_ptr = nullptr;
        }else{
            Node* tmp = this->stk.top();
            this->stk.pop();
            for(int i = (int)tmp->subs.size()-1; i >= 0; --i){
                this->stk.push(tmp->subs[(uint)i]);
            }
            if(this->stk.empty()){
                this->_ptr = nullptr;
            }else{
                this->_ptr = this->stk.top();
            }
        }
        return *this;
    }
    OrgChart::Iterator_Preorder OrgChart::Iterator_Preorder::operator++(int){
        OrgChart::Iterator_Preorder itr = *this;
        if(stk.empty()){
            this->_ptr = nullptr;
        }else{
            Node* tmp = this->stk.top();
            this->stk.pop();
            for(int i = (int)tmp->subs.size()-1; i >= 0; --i){
                this->stk.push(tmp->subs[(uint)i]);
            }
            if(this->stk.empty()){
                this->_ptr = nullptr;
            }else{
                this->_ptr = this->stk.top();
            }
        }
        return *this;
    }

    OrgChart::Iterator_Level_Order OrgChart::begin(){
        return OrgChart::Iterator_Level_Order(this->root);
    }

    OrgChart::Iterator_Level_Order OrgChart::end(){
        return OrgChart::Iterator_Level_Order(nullptr);
    }

    OrgChart::Iterator_Level_Order OrgChart::begin_level_order(){
        return OrgChart::Iterator_Level_Order(this->root);
    }

    OrgChart::Iterator_Level_Order OrgChart::end_level_order(){
        return OrgChart::Iterator_Level_Order(nullptr);
    }

    OrgChart::Iterator_Reverse_Level_Order OrgChart::begin_reverse_order(){
        return OrgChart::Iterator_Reverse_Level_Order(this->root);
    }

    OrgChart::Iterator_Reverse_Level_Order OrgChart::end_reverse_order(){
        return OrgChart::Iterator_Reverse_Level_Order(nullptr);
    }

    OrgChart::Iterator_Preorder OrgChart::begin_preorder(){
        return OrgChart::Iterator_Preorder(this->root);
    }

    OrgChart::Iterator_Preorder OrgChart::end_preorder(){
        return OrgChart::Iterator_Preorder(nullptr);
    }

    OrgChart& OrgChart::add_root(const std::string& name){
        if(this->root != nullptr){
            this->root->name = name;
        }else{
            this->root = new OrgChart::Node(name);
        }
        return *this;
    }


    OrgChart& OrgChart::add_sub(const std::string& father, const std::string& name){
        OrgChart::Node* tmp = nullptr;
        for(auto itr = this->begin(); itr != OrgChart::end(); ++itr){
            if((*itr) == father){
                tmp = itr.get_ptr();
            }
        }

        if(tmp == nullptr){
            throw "father dont exist";
        }
        OrgChart::Node* new_member = new OrgChart::Node(name);
        tmp->subs.push_back(new_member);
        return *this;
    }


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