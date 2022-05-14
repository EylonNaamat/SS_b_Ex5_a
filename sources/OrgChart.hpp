//
// Created by eylon on 5/11/22.
//
#include <vector>
#include <string>
#include <queue>
#include <exception>
#include <iostream>
#include <stack>

namespace ariel{
    class OrgChart{
    public:
        struct Node{
            std::string name;
            std::vector<Node*> subs;
            int size;
            Node(std::string name): name(name), size(name.length()){}
        };
    private:
        Node* root = nullptr;

    public:
        OrgChart(){
            this->root = nullptr;
        }
        ~OrgChart(){}

        class Iterator{
            protected:
                Node *_ptr;
            public:
                std::string &operator*(){
                    return this->_ptr->name;
                }
                bool operator!=(const Iterator& itr) const {
                    if(this->_ptr != itr._ptr){
                        return true;
                    }
                    return false;
                }
                std::string* operator->(){
                    return &(this->_ptr->name);
                }
                Node* get_ptr(){
                    return this->_ptr;
                }
        };

        /* level order iterator */
        class Iterator_Level_Order : public Iterator{
            private:
                std::queue<Node*> q;
            public:
                Iterator_Level_Order(Node* ptr){
                    if(ptr == nullptr){
                        this->_ptr = ptr;
                    }else{
                        this->q.push(ptr);
                        this->_ptr = ptr;
                    }
                }
                Iterator_Level_Order& operator++(){
                    if(this->q.empty()){
                        this->_ptr = nullptr;
                    }else{
                        Node* tmp = this->q.front();
                        this->q.pop();
                        if(tmp->subs.size() != 0){
                            for(int i = 0; i < tmp->subs.size(); ++i){
                                this->q.push(tmp->subs[(uint)i]);
                            }
                        }
                        this->_ptr = this->q.front();
                    }
                    return *this;
                }
                Iterator_Level_Order operator++(int){
                    Iterator_Level_Order itr = *this;
                    if(this->q.empty()){
                        this->_ptr = nullptr;
                    }else{
                        Node* tmp = this->q.front();
                        this->q.pop();
                        if(tmp->subs.size() != 0){
                            for(int i = 0; i < tmp->subs.size(); ++i){
                                this->q.push(tmp->subs[(uint)i]);
                            }
                        }
                        this->_ptr = this->q.front();
                    }
                    return itr;
                }
        };

        /* reverse level order iterator */
        class Iterator_Reverse_Level_Order: public Iterator{
            private:
                std::queue<Node*> q;
                std::stack<Node*> stk;
            public:
                Iterator_Reverse_Level_Order(Node* ptr){
                    if(ptr == nullptr){
                        this->_ptr = nullptr;
                    }else{
                        this->q.push(ptr);
                        while(!this->q.empty()){
                            Node* tmp = this->q.front();
                            this->stk.push(q.front());
                            this->q.pop();
                            if(tmp->subs.size() != 0){
                                for(int i = tmp->subs.size()-1; i >=0; --i){
                                    this->q.push(tmp->subs[(uint)i]);
                                }
                            }
                        }
                        this->_ptr = this->stk.top();
                        this->stk.pop();
//                        std::cout << "eylon" << std::endl;
//                        while(!this->stk.empty()){
//                            std::cout << this->stk.top()->name << std::endl;
//                            this->stk.pop();
//                        }
                    }
                }

                Iterator_Reverse_Level_Order &operator++(){
                    if(this->stk.empty()){
                        this->_ptr = nullptr;
                    }else{
                        this->_ptr = this->stk.top();
                        this->stk.pop();
                    }
                    return *this;
                }
                Iterator_Reverse_Level_Order operator++(int){
                    Iterator_Reverse_Level_Order itr = *this;
                    if(this->stk.empty()){
                        this->_ptr = nullptr;
                    }else{

                        this->stk.pop();
                        this->_ptr = this->stk.top();
                    }
                    return itr;
                }
        };

        /* preorder iterator */
        class Iterator_Preorder: public Iterator{
            private :
                std::stack<Node*> stk;
            public:
                Iterator_Preorder(Node* ptr){
                    if(ptr == nullptr){
                        this->_ptr = ptr;
                    }else{
                        this->stk.push(ptr);
                        this->_ptr = ptr;
                    }
                }
                Iterator_Preorder &operator++(){
                    if(stk.empty()){
                        this->_ptr = nullptr;
                    }else{
                        Node* tmp = this->stk.top();
                        this->stk.pop();
                        for(int i = tmp->subs.size()-1; i>=0; --i){
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
                Iterator_Preorder operator++(int){
                    Iterator_Preorder itr = *this;
                    if(stk.empty()){
                        this->_ptr = nullptr;
                    }else{
                        Node* tmp = this->stk.top();
                        this->stk.pop();
                        for(int i = tmp->subs.size()-1; i>=0; --i){
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
        };


        /* regular iterator which is by default level_order */
        Iterator_Level_Order begin(){
            return Iterator_Level_Order(this->root);
        }

        Iterator_Level_Order end(){
            return Iterator_Level_Order(nullptr);
        }

        /* level order iterator begin and end */
        Iterator_Level_Order begin_level_order(){
            return Iterator_Level_Order(this->root);
        }
        Iterator_Level_Order end_level_order(){
            return Iterator_Level_Order(nullptr);
        }

        /* revers level order iterator begin and end */
        Iterator_Reverse_Level_Order begin_reverse_order(){
            return Iterator_Reverse_Level_Order(this->root);
        }
        Iterator_Reverse_Level_Order end_reverse_order(){
            return Iterator_Reverse_Level_Order(nullptr);
        }

        /* preorder iterator begin and end */
        Iterator_Preorder begin_preorder(){
            return Iterator_Preorder(this->root);
        }
        Iterator_Preorder end_preorder(){
            return Iterator_Preorder(nullptr);
        }


        OrgChart& add_root(std::string name){
            if(this->root != nullptr){
                this->root->name = name;
            }else{
                Node* tmp = new Node(name);
                this->root = tmp;
            }
            return *this;
        }
        OrgChart& add_sub(std::string father, std::string name){
            Node* tmp = find(father);
            if(tmp == nullptr){
                throw "father dont exist";
            }
            Node* new_member = new Node(name);
            tmp->subs.push_back(new_member);
            tmp->size++;
            return *this;
        }
        Node* find(std::string name){
            Node* ans = nullptr;
            int i = 0;
            for(Iterator_Level_Order itr = this->begin_level_order(); (itr != this->end_level_order()); ++itr){
                i++;
                if((*itr) == name){
                    ans = itr.get_ptr();
                    break;
                }
            }
            return ans;
        }

        friend std::ostream& operator<<(std::ostream& os, OrgChart& org);
        static std::string& helper(std::string& str, std::string prefix, OrgChart::Node* node);
    };
};
