//
// Created by eylon on 5/14/22.
//

#include "doctest.h"
#include "sources/OrgChart.hpp"
#include <iostream>

using namespace ariel;

TEST_CASE("add_root, add_sub tests - good cases"){
    OrgChart org;
    org.add_root("CEO");
    org.add_sub("CEO", "COO");
    org.add_sub("CEO", "CTO");
    org.add_sub("COO", "ASD");
    org.add_sub("COO", "LSD");
    org.add_sub("COO", "APP");
    org.add_sub("ASD", "ABC");

    auto itr = org.begin_level_order();
    CHECK((*itr) == "CEO");
    itr++;
    CHECK((*itr) == "COO");
    itr++;
    CHECK((*itr) == "CTO");
    itr++;
    CHECK((*itr) == "ASD");
    itr++;
    CHECK((*itr) == "LSD");
    itr++;
    CHECK((*itr) == "APP");
    itr++;
    CHECK((*itr) == "ABC");
    itr++;

    //changing the root name and checking if the orgchart stays the same
    org.add_root("eylon");
    auto itrr = org.begin_level_order();
    CHECK((*itrr) == "eylon");
    itrr++;
    CHECK((*itrr) == "COO");
    itrr++;
    CHECK((*itrr) == "CTO");
    itrr++;
    CHECK((*itrr) == "ASD");
    itrr++;
    CHECK((*itrr) == "LSD");
    itrr++;
    CHECK((*itrr) == "APP");
    itrr++;
    CHECK((*itrr) == "ABC");
    itrr++;

    // checking if we can apply function on function (testing the reference)
    OrgChart org2;
    org2.add_root("CEO").add_sub("CEO", "COO")
    .add_sub("CEO", "CTO")
    .add_sub("COO", "ASD")
    .add_sub("COO", "LSD")
    .add_sub("COO", "APP")
    .add_sub("ASD", "ABC");


    auto itr2 = org2.begin_level_order();
    CHECK((*itr2) == "CEO");
    itr2++;
    CHECK((*itr2) == "COO");
    itr2++;
    CHECK((*itr2) == "CTO");
    itr2++;
    CHECK((*itr2) == "ASD");
    itr2++;
    CHECK((*itr2) == "LSD");
    itr2++;
    CHECK((*itr2) == "APP");
    itr2++;
    CHECK((*itr2) == "ABC");
    itr2++;

    // adding sub to org and check if add
    org2.add_sub("ABC", "DEF");
    itr2 = org2.begin_level_order();
    CHECK((*itr2) == "CEO");
    itr2++;
    CHECK((*itr2) == "COO");
    itr2++;
    CHECK((*itr2) == "CTO");
    itr2++;
    CHECK((*itr2) == "ASD");
    itr2++;
    CHECK((*itr2) == "LSD");
    itr2++;
    CHECK((*itr2) == "APP");
    itr2++;
    CHECK((*itr2) == "ABC");
    itr2++;
    CHECK((*itr2) == "DEF");
    itr2++;

}


TEST_CASE("add_root, add_sub tests - bad cases"){
    OrgChart org;

    //trying to add_sub without a root
    CHECK_THROWS(org.add_sub("CEO", "CTO"));

    org.add_root("eylon");
    //trying to add sub to non exist field
    CHECK_THROWS(org.add_sub("CTO", "COO"));

}

TEST_CASE("iterators - good cases"){
    // making an org like linkedlist, thus, preorder and level order should be the same, and reverse level order be like level order
    OrgChart org;
    org.add_root("eylon");
    org.add_sub("eylon", "naamat");
    org.add_sub("naamat", "cpp");
    org.add_sub("cpp", "class");
    org.add_sub("class", "cs");
    org.add_sub("cs", "degree");

    std::vector<std::string> level_order;
    for(auto itr_level = org.begin_level_order(); itr_level != OrgChart::end_level_order(); ++itr_level){
        level_order.push_back((*itr_level));
    }
    std::vector<std::string> reverse_level_order;
    for(auto itr_reverse = org.begin_reverse_order(); itr_reverse != OrgChart::end_reverse_order(); ++itr_reverse){
        reverse_level_order.push_back((*itr_reverse));
    }
    std::vector<std::string> preorder;
    for(auto itr_pre = org.begin_preorder(); itr_pre != OrgChart::end_preorder(); ++itr_pre){
        preorder.push_back((*itr_pre));
    }

    // checking if the size is the same
    CHECK(level_order.size() == reverse_level_order.size());
    CHECK(level_order.size() == preorder.size());
    CHECK(reverse_level_order.size() == preorder.size());

    for(int i = 0; i < level_order.size(); ++i){
        CHECK(level_order[(uint)i] == preorder[(uint)i]);
        CHECK(level_order[(uint)i] == reverse_level_order[reverse_level_order.size()-1-(uint)i]);
    }

    OrgChart org2;
    org2.add_root("CEO")
            .add_sub("CEO", "HEADANDSHOULDERS")
            .add_sub("CEO", "CTO")
            .add_sub("CEO", "COO")
            .add_sub("CTO", "ABC")
            .add_sub("CTO", "DEF")
            .add_sub("COO", "GHI")
            .add_sub("COO", "JKL")
            .add_sub("ABC", "MNO")
            .add_sub("ABC", "PQR")
            .add_sub("DEF", "STU")
            .add_sub("DEF", "VWX")
            .add_sub("MNO", "YZ");



    std::vector<std::string> vec_level{"CEO", "HEADANDSHOULDERS", "CTO", "COO", "ABC", "DEF", "GHI", "JKL", "MNO", "PQR", "STU", "VWX", "YZ"};
    std::vector<std::string> vec_reverse{"YZ", "MNO", "PQR", "STU", "VWX", "ABC", "DEF", "GHI", "JKL", "HEADANDSHOULDERS", "CTO", "COO", "CEO"};
    std::vector<std::string> vec_pre{"CEO", "HEADANDSHOULDERS", "CTO", "ABC", "MNO", "YZ", "PQR", "DEF", "STU", "VWX", "COO", "GHI", "JKL"};

    int i = 0;
    for(auto element : org2){
        CHECK(element == vec_level[(uint)i]);
        ++i;
    }
    i = 0;
    for(auto itr = org2.begin_level_order(); itr != OrgChart::end_level_order(); ++itr){
        CHECK((*itr) == vec_level[(uint)i]);
        ++i;
    }
    i = 0;
    for(auto itr = org2.begin_reverse_order(); itr != OrgChart::end_reverse_order(); ++itr){
        CHECK((*itr) == vec_reverse[(uint)i]);
        ++i;
    }
    i = 0;
    for(auto itr = org2.begin_preorder(); itr != OrgChart::end_preorder(); ++itr){
        CHECK((*itr) == vec_pre[(uint)i]);
        ++i;
    }




}