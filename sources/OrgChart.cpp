//
// Created by eylon on 5/11/22.
//
#include "OrgChart.hpp"

namespace ariel{

    /*
     * implementation of * operator
     * return the nodes name
     */
    std::string&  OrgChart::Iterator::operator*() const{
        return this->_ptr->name;
    }

    /*
     * implementation of != operator if the pointers arent the same return true, else false
     */
    bool OrgChart::Iterator::operator!=(const Iterator& itr) const{
        bool ans = false;
        if(this->_ptr != itr._ptr){
            ans = true;
        }
        return ans;
    }

    /**
     * this function implements the -> operator, return the address of the nodes name
     * @return
     */
    std::string* OrgChart::Iterator::operator->() const{
        return &(this->_ptr->name);
    }

    /**
     * this function is a getter for the pointer in Iterator
     * @return
     */
    OrgChart::Node* OrgChart::Iterator::get_ptr() const{
        return this->_ptr;
    }

    /* ******************** */
    /* Level_Order_Iterator */
    /* ******************** */

    /**
     * this function if the prefix++
     * in this function we first check if the q is empty, if so the pointer is nullptr
     * else, we pop the queue and check if now the queue is empty, if so the pointer is nullptr
     * else, the pointer is the first element in the queue
     * @return
     */
    OrgChart::Iterator_Level_Order& OrgChart::Iterator_Level_Order::operator++(){
        if(this->q.empty()){
            this->_ptr = nullptr;
        }else{
            Node* tmp = this->q.front();
            this->q.pop();
            for(int i = 0; i < tmp->subs.size(); ++i){
                this->q.push(tmp->subs[(uint)i]);
            }
            if(this->q.empty()){
                this->_ptr = nullptr;
            }else{
                this->_ptr = this->q.front();
            }
        }
        return *this;
    }

    /**
     * his function if the postfix++
     * first we save the iterator
     * in this function we first check if the q is empty, if so the pointer is nullptr
     * else, we pop the queue and check if now the queue is empty, if so the pointer is nullptr
     * else, the pointer is the first element in the queue
     * and return the iterator we saved
     * @return
     */
    OrgChart::Iterator_Level_Order OrgChart::Iterator_Level_Order::operator++(int){
        OrgChart::Iterator_Level_Order itr = *this;
        if(this->q.empty()){
            this->_ptr = nullptr;
        }else{
            Node* tmp = this->q.front();
            this->q.pop();
            for(int i = 0; i < tmp->subs.size(); ++i){
                this->q.push(tmp->subs[(uint)i]);
            }
            if(this->q.empty()){
                this->_ptr = nullptr;
            }else{
                this->_ptr = this->q.front();
            }
        }
        return itr;
    }

    /* ********************** */
    /* Reverse_Order_Iterator */
    /* ********************** */

    /**
     * his function if the prefix++
     * in this function we first check if the stack is empty, if so the pointer is nullptr
     * else, we pop the queue and check if now the stack is empty, if so the pointer is nullptr
     * else, the pointer is the first element in the stack
     * @return
     */
    OrgChart::Iterator_Reverse_Level_Order& OrgChart::Iterator_Reverse_Level_Order::operator++(){
        if(this->stk.empty()){
            this->_ptr = nullptr;
        }else{
            this->stk.pop();
            if(this->stk.empty()){
                this->_ptr = nullptr;
            }else{
                this->_ptr = this->stk.top();
            }
        }
        return *this;
    }

    /**
     * his function if the postfix++
     * first we save the iterator
     * in this function we first check if the stack is empty, if so the pointer is nullptr
     * else, we pop the queue and check if now the stack is empty, if so the pointer is nullptr
     * else, the pointer is the first element in the stack
     * and return the iterator we saved
     * @return
     */
    OrgChart::Iterator_Reverse_Level_Order OrgChart::Iterator_Reverse_Level_Order::operator++(int){
        OrgChart::Iterator_Reverse_Level_Order itr = *this;
        if(this->stk.empty()){
            this->_ptr = nullptr;
        }else{
            this->stk.pop();
            if(this->stk.empty()){
                this->_ptr = nullptr;
            }else{
                this->_ptr = this->stk.top();
            }
        }
        return itr;
    }

    /* ***************** */
    /* PreOrder_Iterator */
    /* ***************** */

    /**
     * this is the prefix++
     * in this function we first check if the stack is empty if so, the pointer is nullptr
     * else, we save the top of the sack and then pop the stack
     * we go through all the child of the top of the stack from right to left, and insert the child to the stack
     * if the stack is empty it means there are no child so the pointer is nullptr
     * else, the pointer is the top of the stack
     * @return
     */
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

    /**
     * this is the postfix++
     * first we save the iterator
     * in this function we first check if the stack is empty if so, the pointer is nullptr
     * else, we save the top of the sack and then pop the stack
     * we go through all the child of the top of the stack from right to left, and insert the child to the stack
     * if the stack is empty it means there are no child so the pointer is nullptr
     * else, the pointer is the top of the stack
     * and return the iterator we saved
     * @return
     */
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
        return itr;
    }

    /* *********** */
    /* Begin / End */
    /* *********** */

    /**
     * this function tells the iterator where to begin, we send root to level order iterator
     * @return
     */
    OrgChart::Iterator_Level_Order OrgChart::begin(){
        if(this->root == nullptr){
            throw "nullptr";
        }
        return OrgChart::Iterator_Level_Order(this->root);
    }

    /**
     * this function tells the iterator where to stop, we send nullptr to level order iterator
     * @return
     */
    OrgChart::Iterator_Level_Order OrgChart::end(){
        if(this->root == nullptr){
            throw "nullptr";
        }
        return OrgChart::Iterator_Level_Order(nullptr);
    }

    /**
     * this function tells the iterator where to begin, we send root to level order iterator
     * @return
     */
    OrgChart::Iterator_Level_Order OrgChart::begin_level_order(){
        if(this->root == nullptr){
            throw "nullptr";
        }
        return OrgChart::Iterator_Level_Order(this->root);
    }

    /**
     * this function tells the iterator where to stop, we send nullptr to level order iterator
     * @return
     */
    OrgChart::Iterator_Level_Order OrgChart::end_level_order(){
        if(this->root == nullptr){
            throw "nullptr";
        }
        return OrgChart::Iterator_Level_Order(nullptr);
    }

    /**
     * this function tells the iterator where to begin, we send root to reverse level order iterator
     * @return
     */
    OrgChart::Iterator_Reverse_Level_Order OrgChart::begin_reverse_order(){
        if(this->root == nullptr){
            throw "nullptr";
        }
        return OrgChart::Iterator_Reverse_Level_Order(this->root);
    }

    /**
     * this function tells the iterator where to stop, we send nullptr to reverse level order iterator
     * @return
     */
    OrgChart::Iterator_Reverse_Level_Order OrgChart::reverse_order(){
        if(this->root == nullptr){
            throw "nullptr";
        }
        return OrgChart::Iterator_Reverse_Level_Order(nullptr);
    }

    /**
     * this function tells the iterator where to begin, we send root to preorder iterator
     * @return
     */
    OrgChart::Iterator_Preorder OrgChart::begin_preorder(){
        if(this->root == nullptr){
            throw "nullptr";
        }
        return OrgChart::Iterator_Preorder(this->root);
    }

    /**
     * this function tells the iterator where to stop, we send nullptr to preorder iterator
     * @return
     */
    OrgChart::Iterator_Preorder OrgChart::end_preorder(){
        if(this->root == nullptr){
            throw "nullptr";
        }
        return OrgChart::Iterator_Preorder(nullptr);
    }

    /* ****************** */
    /* OrgChart Functions */
    /* ****************** */

    /**
     * this function adds a root to the organization
     * if the root is nullptr it means that the organization is empty, so we create a new node with the name we got
     * and sets him as the root
     * else, the organization isnt empty so we replace the name of the root
     * @param name
     * @return
     */
    OrgChart& OrgChart::add_root(const std::string& name){
        if(name.empty() || name == "\n" || name == "\t" || name == "\r"){
            throw "cant have empty name";
        }
        if(this->root != nullptr){
            this->root->name = name;
        }else{
            this->root = new OrgChart::Node(name);
        }
        return *this;
    }

    /**
     * this function adds a child to a node
     * first we search for the father in the organization
     * if we didnt find him we throw exception
     * else, we create a new node with the name we got and add him to the father vector
     * @param father
     * @param name
     * @return
     */
    OrgChart& OrgChart::add_sub(const std::string& father, const std::string& name){
        if(name.empty() || name == "\n" || name == "\t" || name == "\r"){
            throw "cant have empty name";
        }
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


    /**
     * this function implements the << operator
     * we use a helper function and return os
     * @param os
     * @param org
     * @return
     */
    std::ostream& operator<<(std::ostream& os, OrgChart& org){
        if(org.root == nullptr){
            throw "org is empty!!!";
        }
        std::string str;
        os << OrgChart::helper(str, "", org.root);
        return os;
    }

    /**
     * this is a helper function to the << operator
     * we go recursively on the organization and add the names to a string
     * in the next format:
     * root
     *      -child1
     *      -child1
     *              -child2
     *              -child2
     *      -child1
     * all the children are printed from left to right and with a tab before
     * at the end we return the string we created and send it to os
     * @param str
     * @param prefix
     * @param node
     * @return
     */
    std::string& OrgChart::helper(std::string& str, const std::string& prefix, OrgChart::Node* node){
        str += prefix;
        if(!str.empty()){
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