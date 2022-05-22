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
        /* defining a node struct that has a name and a vector of his "childs" */
        struct Node{
            std::string name;
            std::vector<Node*> subs;
            Node(const std::string& name): name(name){}
        };
    private:
        /* a pointer to the root of the organization */
        Node* root = nullptr;

    public:
        /* constructor sets the root to be nullptr */
        OrgChart(){
            this->root = nullptr;
        }

        /* copy constructor, delete the original OrgChart and then copies the other organization */
        OrgChart(OrgChart& org){
            deleteOrg(this->root);
            copy(org);
        }

        /* moving constructor */
        OrgChart(OrgChart&& org) noexcept{
            this->root = org.root;
            deleteOrg(org.root);
            org.root = nullptr;
        }


        /* destructor, deletes the original organization and sets the root to nullptr */
        ~OrgChart(){
            deleteOrg(this->root);
            this->root = nullptr;
        }

        /* this function gets a node and deletes all his children and him */
        void deleteOrg(Node* node){
            if(node == nullptr){
                return;
            }
            for(int i = 0; i < node->subs.size(); ++i){
                deleteOrg(node->subs[(uint)i]);
            }
            delete node;
        }

        /* operator= if the org isnt null, delete the original org and copy the other to it */
        OrgChart& operator=(const OrgChart& org){
            if(this != &org){
                deleteOrg(this->root);
                copy(org);
            }
            return *this;
        }

        /* moving operator= */
        OrgChart& operator=(OrgChart&& org)noexcept{
            this->root = org.root;
            deleteOrg(org.root);
            org.root = nullptr;
            return *this;
        }

        /* this function gets an organization and copies it to current organization */
        void copy(const OrgChart& org){
            if(org.root != nullptr){
                this->root = new Node(org.root->name);
                copy_helper(this->root, org.root);
            }
        }

        /* this function gets two nodes and copies it */
        void copy_helper(Node* curr, Node* from){
            for(int i = 0; i < from->subs.size(); ++i){
                Node* new_node = new Node(from->subs[(uint)i]->name);
                curr->subs.push_back(new_node);
                copy_helper(curr->subs[(uint)i], from->subs[(uint)i]);
            }
        }

        /* iterator class which all the 3 iterators will inherit from */
        class Iterator{
        public:
            Node* _ptr;
            std::string&  operator*() const;
            bool operator!=(const Iterator& itr) const;
            std::string* operator->() const;
            Node* get_ptr() const;
        };

        /* level order iterator */
        /* this iterator inherits from Iterator and has a queue which orders all the nodes in the organization in level order */
        class Iterator_Level_Order : public Iterator{
        private:
            std::queue<Node*> q;
        public:
            /* the constructor gets a pointer to a node and fills the queue in the level order */
            /*
             * this constructor gets a pointer to node and enters him into a queue
             * as long as the queue isnt empty, we take out the first element, inset him into another queue,
             * and then inserting all his child into the first queue
             */
            Iterator_Level_Order(Node* ptr): Iterator(){
                if(ptr == nullptr){
                    this->_ptr = nullptr;
                }else{
                    this->q.push(ptr);
                    this->_ptr = this->q.front();
                }

            }
            Iterator_Level_Order& operator++();
            Iterator_Level_Order operator++(int);
        };

        /* reverse level order iterator */
        /* this iterator inherits from Iterator and has a stack which orders all the nodes in the organization in reverse level order */
        class Iterator_Reverse_Level_Order: public Iterator{
        private:
            std::queue<Node*> q;
            std::stack<Node*> stk;
        public:
            /*
             * this constructor gets a pointer to node and fills the stack in reverse level order.
             * in this constructor we use a queue like level order but in this time we insert the childs of a node
             * from right to left into the queue.
             * in order to make this a reverse level order each iteration we pop the queue we insert the node to a stack
             */
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
        /* this iterator inherits from Iterator and has a stack which orders all the nodes in the organization in preorder */
        class Iterator_Preorder: public Iterator{
        private :
            std::stack<Node*> stk;
        public:
            /*
             * this constructor gets a pointer to node and enter him into a stack, in this iterator,
             * we change the stack when we do ++
             */
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
        Iterator_Level_Order end();

        /* level order iterator begin and end */
        Iterator_Level_Order begin_level_order();
        Iterator_Level_Order end_level_order();

        /* revers level order iterator begin and end */
        Iterator_Reverse_Level_Order begin_reverse_order();
        Iterator_Reverse_Level_Order reverse_order();

        /* preorder iterator begin and end */
        Iterator_Preorder begin_preorder();
        Iterator_Preorder end_preorder();

        OrgChart& add_root(const std::string& name);
        OrgChart& add_sub(const std::string& father, const std::string& name);


        friend std::ostream& operator<<(std::ostream& os, OrgChart& org);
        static std::string& helper(std::string& str, const std::string& prefix, OrgChart::Node* node);
    };
};