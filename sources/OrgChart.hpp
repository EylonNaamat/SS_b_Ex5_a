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
                std::string&  operator*();
                bool operator!=(const Iterator& itr);
                std::string* operator->();
                Node* get_ptr();
        };

        /* level order iterator */
        class Iterator_Level_Order : public Iterator{
            private:
                std::queue<Node*> q_tmp;
                std::queue<Node*> q;
            public:
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
                Iterator_Level_Order& operator++();
                Iterator_Level_Order operator++(int);
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
                    }
                }

                Iterator_Reverse_Level_Order& operator++();
                Iterator_Reverse_Level_Order operator++(int);
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
                Iterator_Preorder& operator++();
                Iterator_Preorder operator++(int);
        };


        /* regular iterator which is by default level_order */
        Iterator_Level_Order begin();
        static Iterator_Level_Order end();

        /* level order iterator begin and end */
        Iterator_Level_Order begin_level_order();
        static Iterator_Level_Order end_level_order();

        /* revers level order iterator begin and end */
        Iterator_Reverse_Level_Order begin_reverse_order();
        static Iterator_Reverse_Level_Order end_reverse_order();

        /* preorder iterator begin and end */
        Iterator_Preorder begin_preorder();
        static Iterator_Preorder end_preorder();


        OrgChart& add_root(const std::string& name);
        OrgChart& add_sub(const std::string& father, const std::string& name);


        friend std::ostream& operator<<(std::ostream& os, OrgChart& org);
        static std::string& helper(std::string& str, std::string prefix, OrgChart::Node* node);
    };
};
