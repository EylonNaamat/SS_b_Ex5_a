//
// Created by eylon on 5/21/22.
//
#include "sources/OrgChart.hpp"
#include <iostream>
using namespace ariel;


int main(){

    OrgChart org;
    org.add_root("CEO")
        .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
        .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
        .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
        .add_sub("CEO", "HEADANDSHOULDERS")
        .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
        .add_sub("COO", "VP_BI")      // Now the VP_BI is subordinate to the COO
        .add_sub("CFO", "LIRON")
        .add_sub("VP_SW", "EYLON")
        .add_sub("VP_SW", "NAAMAT");

    char y_n;
    std::cout << "Do You Want To See The Default Organization?" << std::endl;
    std::cout << "y for yes, n for no" << std::endl;
    std::cin >> y_n;
    if(y_n == 'y'){
        std::cout << org << std::endl;
    }

    OrgChart org2;
    std::cout << "Do You Want To Build An Organization?" << std::endl;
    std::cout << "y for yes, n for no" << std::endl;
    std::cin >> y_n;
    if(y_n == 'y'){
        std::string root = "";
        std::string father = "";
        std::string son = "";
        std::cout << "Enter Root" << std::endl;
        std::cin >> root;
        org2.add_root(root);
        while(father != "no"){
            std::cout << "Enter Father" << std::endl;
            std::cin >> father;
            std::cout << "Enter Son" << std::endl;
            std::cin >> son;
            if(father != "no"){
                try{
                    org2.add_sub(father, son);
                }catch(...) {
                    std::cout << "Father Dont Exist" << std::endl;
                }
            }
        }
        std::cout << org2 << std::endl;
    }

    std::string which_iter = "";
    while(which_iter != "stop"){
        std::cout << "Insert The Iterator You Want Or stop To Quit\n";
        std::cin >> which_iter;
        if(which_iter == "level_order"){
            std::string command = "";
            while(command != "stop"){
                std::cout << "Insert The Function You Want To Test" << std::endl;
                std::cout << "The Functions Are:" << std::endl;
                std::cout << "add_root\n" << "add_sub\n" << "*\n" << "->\n" << "pre++\n" << "post++\n" << "print\n" << "stop" << std::endl;
                std::cin >> command;
                if(command == "add_root"){
                    std::string new_root = "";
                    std::cout << "Enter Root" << std::endl;
                    std::cin >> new_root;
                    org.add_root(new_root);
                    std::cout << org << std::endl;
                }else if(command == "add_sub"){
                    std::string new_father = "";
                    std::string new_son = "";
                    std::cout << "Enter Father" << std::endl;
                    std::cin >> new_father;
                    std::cout << "Enter Son" << std::endl;
                    std::cin >> new_son;
                    try{
                        org.add_sub(new_father, new_son);
                        std::cout << org << std::endl;
                    }catch(...){
                        std::cout << "Father Dont Exist" << std::endl;
                    }
                }else if(command == "*"){
                    for(auto itr = org.begin_level_order(); itr != org.end_level_order(); ++itr){
                        std::cout << (*itr) << " ";
                    }
                    std::cout << std::endl;
                }else if(command == "->"){
                    for(auto itr = org.begin_level_order(); itr != org.end_level_order(); ++itr){
                        std::cout << itr->size() << " ";
                    }
                    std::cout << std::endl;
                }else if(command == "pre++"){
                    auto itr = org.begin_level_order();
                    std::cout << (*(++itr)) << std::endl;
                }else if(command == "post++"){
                    auto itr = org.begin_level_order();
                    std::cout << (*(itr++)) << std::endl;
                }else if(command == "print"){
                    std::cout << org << std::endl;
                }else if(command == "stop"){
                    break;
                }
            }
        }else if(which_iter == "reverse_level_order"){
            std::string command = "";
            while(command != "stop"){
                std::cout << "Insert The Function You Want To Test" << std::endl;
                std::cout << "The Functions Are:" << std::endl;
                std::cout << "add_root\n" << "add_sub\n" << "*\n" << "->\n" << "pre++\n" << "post++\n" << "print\n" << "stop" << std::endl;
                std::cin >> command;
                if(command == "add_root"){
                    std::string new_root = "";
                    std::cout << "Enter Root" << std::endl;
                    std::cin >> new_root;
                    org.add_root(new_root);
                    std::cout << org << std::endl;
                }else if(command == "add_sub"){
                    std::string new_father = "";
                    std::string new_son = "";
                    std::cout << "Enter Father" << std::endl;
                    std::cin >> new_father;
                    std::cout << "Enter Son" << std::endl;
                    std::cin >> new_son;
                    try{
                        org.add_sub(new_father, new_son);
                        std::cout << org << std::endl;
                    }catch(...){
                        std::cout << "Father Dont Exist" << std::endl;
                    }
                }else if(command == "*"){
                    for(auto itr = org.begin_reverse_order(); itr != org.reverse_order(); ++itr){
                        std::cout << (*itr) << " ";
                    }
                    std::cout << std::endl;
                }else if(command == "->"){
                    for(auto itr = org.begin_reverse_order(); itr != org.reverse_order(); ++itr){
                        std::cout << itr->size() <<" ";
                    }
                    std::cout << std::endl;
                }else if(command == "pre++"){
                    auto itr = org.begin_reverse_order();
                    std::cout << (*(++itr)) << std::endl;
                }else if(command == "post++"){
                    auto itr = org.begin_reverse_order();
                    std::cout << (*(itr++)) << std::endl;
                }else if(command == "print"){
                    std::cout << org << std::endl;
                }else if(command == "stop"){
                    break;
                }
            }
        }else if(which_iter == "preorder"){
            std::string command = "";
            while(command != "stop"){
                std::cout << "Insert The Function You Want To Test" << std::endl;
                std::cout << "The Functions Are:" << std::endl;
                std::cout << "add_root\n" << "add_sub\n" << "*\n" << "->\n" << "pre++\n" << "post++\n" << "print\n" << "stop" << std::endl;
                std::cin >> command;
                if(command == "add_root"){
                    std::string new_root = "";
                    std::cout << "Enter Root" << std::endl;
                    std::cin >> new_root;
                    org.add_root(new_root);
                    std::cout << org << std::endl;
                }else if(command == "add_sub"){
                    std::string new_father = "";
                    std::string new_son = "";
                    std::cout << "Enter Father" << std::endl;
                    std::cin >> new_father;
                    std::cout << "Enter Son" << std::endl;
                    std::cin >> new_son;
                    try{
                        org.add_sub(new_father, new_son);
                        std::cout << org << std::endl;
                    }catch(...){
                        std::cout << "Father Dont Exist" << std::endl;
                    }
                }else if(command == "*"){
                    for(auto itr = org.begin_preorder(); itr != org.end_preorder(); ++itr){
                        std::cout << (*itr) << " ";
                    }
                    std::cout << std::endl;
                }else if(command == "->"){
                    for(auto itr = org.begin_preorder(); itr != org.end_preorder(); ++itr){
                        std::cout << itr->size() << " ";
                    }
                    std::cout << std::endl;
                }else if(command == "pre++"){
                    auto itr = org.begin_preorder();
                    std::cout << (*(++itr)) << std::endl;
                }else if(command == "post++"){
                    auto itr = org.begin_preorder();
                    std::cout << (*(itr++)) << std::endl;
                }else if(command == "print"){
                    std::cout << org << std::endl;
                }else if(command == "stop"){
                    break;
                }
            }
        }
    }
    return 0;
}
