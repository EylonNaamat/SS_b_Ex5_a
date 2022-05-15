//
// Created by eylon on 5/11/22.
//
#include "OrgChart.hpp"
#include <exception>

namespace ariel{

    std::string&  OrgChart::Iterator::operator*(){
        return this->_ptr->name;
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