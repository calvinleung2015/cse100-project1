#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "HCTree.hpp"

using namespace std;
using namespace testing;

TEST(SimpleHCNode, TEST_COMPARATOR1) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    HCNode* hcn1 = new HCNode(3, 'a');
    HCNode* hcn2 = new HCNode(1, 'b');
    HCNode* hcn3 = new HCNode(2, 'c');
    pq.push(hcn1);
    pq.push(hcn2);
    pq.push(hcn3);
    ASSERT_EQ(pq.top()->count, 1);
}

TEST(SimpleHCNode, TEST_COMPARATOR2) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    HCNode* hcn1 = new HCNode(1, 'a');
    HCNode* hcn2 = new HCNode(1, 'b');
    HCNode* hcn3 = new HCNode(1, 'c');
    pq.push(hcn1);
    pq.push(hcn2);
    pq.push(hcn3);
    ASSERT_EQ(pq.top()->symbol, 'c');
}

TEST(SimpleHCNode, TEST_COMPARATOR3) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    HCNode* hcn1 = new HCNode(2, 'a');
    HCNode* hcn2 = new HCNode(1, 'b');
    HCNode* hcn3 = new HCNode(1, 'c');
    pq.push(hcn1);
    pq.push(hcn2);
    pq.push(hcn3);
    ASSERT_EQ(pq.top()->symbol, 'c');
}

TEST(MyTest, TheTest) {
    cout << "Hello World!" << endl;
}