#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "HCTree.hpp"

using namespace std;
using namespace testing;

class SimpleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    SimpleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['h'] = 2;
        freqs['u'] = 9;
        freqs['m'] = 2;
        freqs['n'] = 2;
        freqs['k'] = 2;
        freqs['a'] = 3;
        freqs['p'] = 1;
        freqs['\''] = 1;
        tree.build(freqs);
    }
};

TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
    ostringstream os;
    tree.encode('h', os);
    tree.encode('u', os);
    tree.encode('m', os);
    tree.encode('u', os);
    tree.encode('h', os);
    tree.encode('u', os);
    tree.encode('m', os);
    tree.encode('u', os);
    tree.encode('n', os);
    tree.encode('u', os);
    tree.encode('k', os);
    tree.encode('u', os);
    tree.encode('n', os);
    tree.encode('u', os);
    tree.encode('k', os);
    tree.encode('a', os);
    tree.encode('p', os);
    tree.encode('u', os);
    tree.encode('a', os);
    tree.encode('\'', os);
    tree.encode('a', os);
    ASSERT_EQ(os.str(),
              "100011100100011100110101111011010111110111000010111001101");
}

TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
    istringstream is("11000");
    ASSERT_EQ(tree.decode(is), 'p');
}
