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
            Node(const std::string& name): name(name){}
        };
    private:
        Node* root = nullptr;

    public:
        OrgChart(){
            this->root = nullptr;
        }

//        OrgChart(OrgChart& org){
//            deleteOrg();
//            copy(org);
//        }

//        OrgChart(OrgChart&& org) noexcept{
//            this->root = org.root;
//            org.root = nullptr;
//        }

//        ~OrgChart(){
//            deleteOrg();
//        }

//        void deleteOrg(){
//            if(this->root != nullptr){
//                for(Iterator_Level_Order itr = this->begin_level_order(); itr != OrgChart::end_level_order(); ++itr){
//                    Node* tmp = itr.get_ptr();
//                    delete tmp;
//                }
//            }
//        }

//        OrgChart& operator=(const OrgChart& org){
//            if(this != &org){
//                deleteOrg();
//                copy(org);
//            }
//            return *this;
//        }

//        OrgChart& operator=(OrgChart&& org)noexcept{
//            this->root = org.root;
//            org.root = nullptr;
//            return *this;
//        }
//
//        void copy(const OrgChart& org){
//            if(org.root != nullptr){
//                this->root = new Node(org.root->name);
//                copy_helper(this->root, org.root);
//            }
//        }
//
//        void copy_helper(Node* curr, Node* from){
//            for(uint i = 0; i < from->subs.size(); ++i){
//                Node* new_node = new Node(from->subs[i]->name);
//                curr->subs.push_back(new_node);
//                copy_helper(curr->subs[i], from->subs[i]);
//            }
//        }

        class Iterator{
            public:
                Node* _ptr;
                std::string&  operator*() const{
                    return this->_ptr->name;
                }
                bool operator!=(const Iterator& itr) const {
                    bool ans = false;
                    if(this->_ptr != itr._ptr){
                        ans = true;
                    }
                    return ans;
                }
                std::string* operator->() const {
                    return &(this->_ptr->name);
                }
                Node* get_ptr() const {
                    return this->_ptr;
                }
        };

        /* level order iterator */
        class Iterator_Level_Order : public Iterator{
            private:
                std::queue<Node*> q_tmp;
                std::queue<Node*> q;
            public:
//                Iterator_Level_Order(Node* ptr): Iterator(){
//                    if(!this->q.empty()){
//                        while(!this->q.empty()){
//                            this->q.pop();
//                        }
//                    }
//                    if(ptr == nullptr){
//                        this->_ptr = ptr;
//                    }else{
//                        this->q.push(ptr);
//                        this->_ptr = ptr;
//                    }
//                }
//                Iterator_Level_Order& operator++(){
//                    if(this->q.empty()){
//                        this->_ptr = nullptr;
//                    }else{
//                        Node* tmp = this->q.front();
//                        this->q.pop();
//                        if(!tmp->subs.empty()){
//                            for(int i = 0; i < tmp->subs.size(); ++i){
//                                this->q.push(tmp->subs[(uint)i]);
////                                std::cout << "the childs are " << tmp->subs[(uint)i]->name;
//                            }
////                            std::cout << "\n";
//                        }
//
//                        this->_ptr = this->q.front();
////                        std::cout << "now ptr is " << this->_ptr->name << std::endl;
//                    }
//                    return *this;
//                }
//                Iterator_Level_Order operator++(int){
//                    Iterator_Level_Order itr = *this;
//                    if(this->q.empty()){
//                        this->_ptr = nullptr;
//                    }else{
//                        Node* tmp = this->q.front();
//                        this->q.pop();
//                        if(!tmp->subs.empty()){
//                            for(int i = 0; i < tmp->subs.size(); ++i){
//                                this->q.push(tmp->subs[(uint)i]);
////                                std::cout << "the childs are " << tmp->subs[(uint)i]->name;
//                            }
////                            std::cout << "\n";
//                        }
//                        this->_ptr = this->q.front();
//                    }
//                    return itr;
//                }


            Iterator_Level_Order(Node* ptr): Iterator(){
                if(!this->q_tmp.empty()){
                    while(!this->q_tmp.empty()){
                        this->q_tmp.pop();
                    }
                }
                if(ptr == nullptr){
                    this->_ptr = ptr;
                }else{
                    this->q_tmp.push(ptr);
                    while(!this->q_tmp.empty()){
                        Node* tmp = this->q_tmp.front();
                        this->q.push(tmp);
                        this->q_tmp.pop();
                        for(int i = 0; i < tmp->subs.size(); ++i){
                            this->q_tmp.push(tmp->subs[(uint)i]);
                        }
                    }
                    this->_ptr = this->q.front();
                }
            }
            Iterator_Level_Order& operator++(){
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
            Iterator_Level_Order operator++(int){
                Iterator_Level_Order itr = *this;
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
        };

        /* reverse level order iterator */
        class Iterator_Reverse_Level_Order: public Iterator{
            private:
                std::queue<Node*> q;
                std::stack<Node*> stk;
            public:
                Iterator_Reverse_Level_Order(Node* ptr): Iterator(){
                    if(!this->q.empty()){
                        while(!this->q.empty()){
                            this->q.pop();
                        }
                    }
                    if(!this->stk.empty()){
                        while(!this->stk.empty()){
                            this->stk.pop();
                        }
                    }
                    if(ptr == nullptr){
                        this->_ptr = nullptr;
                    }else{
                        this->q.push(ptr);
                        while(!this->q.empty()){
                            Node* tmp = this->q.front();
                            this->stk.push(q.front());
                            this->q.pop();
                            if(!tmp->subs.empty()){
                                for(int i = (int)tmp->subs.size()-1; i >= 0; --i){
                                    this->q.push(tmp->subs[(uint)i]);
                                }
                            }
                        }
                        this->_ptr = this->stk.top();
                        this->stk.pop();
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
                Iterator_Preorder(Node* ptr): Iterator(){
                    if(!this->stk.empty()){
                        while(!this->stk.empty()){
                            this->stk.pop();
                        }
                    }
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
                Iterator_Preorder operator++(int){
                    Iterator_Preorder itr = *this;
                    if(stk.empty()){
                        this->_ptr = nullptr;
                    }else{
                        Node* tmp = this->stk.top();
                        this->stk.pop();
                        for(uint i = tmp->subs.size()-1; i >= 0; --i){
                            this->stk.push(tmp->subs[i]);
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

        static Iterator_Level_Order end(){
            return Iterator_Level_Order(nullptr);
        }

        /* level order iterator begin and end */
        Iterator_Level_Order begin_level_order(){
            return Iterator_Level_Order(this->root);
        }
        static Iterator_Level_Order end_level_order(){
            return Iterator_Level_Order(nullptr);
        }

        /* revers level order iterator begin and end */
        Iterator_Reverse_Level_Order begin_reverse_order(){
            return Iterator_Reverse_Level_Order(this->root);
        }
        static Iterator_Reverse_Level_Order end_reverse_order(){
            return Iterator_Reverse_Level_Order(nullptr);
        }

        /* preorder iterator begin and end */
        Iterator_Preorder begin_preorder(){
            return Iterator_Preorder(this->root);
        }
        static Iterator_Preorder end_preorder(){
            return Iterator_Preorder(nullptr);
        }


        OrgChart& add_root(const std::string& name){
            if(this->root != nullptr){
                this->root->name = name;
            }else{
                this->root = new Node(name);
            }
            return *this;
        }
        OrgChart& add_sub(const std::string& father, const std::string& name){
            Node* tmp = find(father);
            if(tmp == nullptr){
                throw "father dont exist";
            }
            Node* new_member = new Node(name);
            tmp->subs.push_back(new_member);
            return *this;

        }

        Node* find(const std::string& name){
//            Node* ans = nullptr;
//                for(Iterator_Level_Order itr = this->begin_level_order(); itr != OrgChart::end_level_order(); ++itr){
//                    if((*itr) == name){
//                        return itr.get_ptr();
////                        ans = itr.get_ptr();
////                        break;
//                    }
//                }
                for(auto itr = this->begin(); itr != OrgChart::end(); ++itr){
                    if((*itr) == name){
                        return itr.get_ptr();
                    }
                }
            return nullptr;
        }

        friend std::ostream& operator<<(std::ostream& os, OrgChart& org);
        static std::string& helper(std::string& str, std::string prefix, OrgChart::Node* node);
    };
};
