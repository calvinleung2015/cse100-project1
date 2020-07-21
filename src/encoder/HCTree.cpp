#include "HCTree.hpp"
#include <stack>
/* TODO: Delete all objects on the heap to avoid memory leaks. */
HCTree::~HCTree() {
    HCNode* curr = root;
    helper_delete(curr);
    root = NULL;
}
void HCTree::helper_delete(HCNode* curr) {
    if (curr == NULL) {
        return;
    }
    helper_delete(curr->c0);
    helper_delete(curr->c1);
    delete (curr);
}

/**
 * TODO: Build the HCTree from the given frequency vector. You can assume the
 * vector must have size 256 and each value at index i represents the frequency
 * of char with ASCII value i. Only non-zero frequency symbols should be used to
 * build the tree. The leaves vector must be updated so that it can be used in
 * encode() to improve performance.
 *
 * When building the HCTree, you should use the following tie-breaking rules to
 * match the output from reference solution in checkpoint:
 *
 *    1. HCNode with lower count should have higher priority. If count is the
 * same, then HCNode with a larger ascii value symbol should have higher
 * priority. (This should be already defined properly in the comparator in
 * HCNode.hpp)
 *    2. When popping two highest priority nodes from PQ, the higher priority
 * node will be the ‘c0’ child of the new parent HCNode.
 *    3. The symbol of any parent node should be taken from its 'c0' child.
 */
void HCTree::build(const vector<unsigned int>& freqs) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

    for (unsigned int i = 0; i < freqs.size(); i++) {
        if (freqs[i] != 0) {
            HCNode* new_node = new HCNode(freqs[i], (byte)i);
            leaves.at(i) = new_node;
            pq.push(new_node);
        }
    }

    while (pq.size() > 1) {
        HCNode* left = pq.top();
        pq.pop();
        HCNode* right = pq.top();
        pq.pop();
        unsigned int sum = left->count + right->count;

        HCNode* update_node = new HCNode(sum, left->symbol);
        update_node->c0 = left;
        left->p = update_node;
        update_node->c1 = right;
        right->p = update_node;
        pq.push(update_node);
    }
    root = pq.top();
    pq.pop();
}

/**
 * TODO: Write the encoding bits of the given symbol to the ostream. You should
 * write each encoding bit as ascii char either '0' or '1' to the ostream. You
 * must not perform a comprehensive search to find the encoding bits of the
 * given symbol, and you should use the leaves vector instead to achieve
 * efficient encoding. For this function to work, build() must be called before
 * to create the HCTree.
 */
// void HCTree::encode(byte symbol, BitOutputStream& out) const {}

/**
 * TODO: Write the encoding bits of the given symbol to ostream. You should
 * write each encoding bit as ascii char either '0' or '1' to the ostream. You
 * must not perform a comprehensive search to find the encoding bits of the
 * given symbol, and you should use the leaves vector instead to achieve
 * efficient encoding. For this function to work, build() must have been called
 * beforehand to create the HCTree.
 */
void HCTree::encode(byte symbol, ostream& out) const {
    stack<string> s;
    HCNode* leave = leaves.at(int(symbol));
    while (leave->p != NULL) {
        if (leave->p->c0 == leave) {
            s.push("0");
        }
        if (leave->p->c1 == leave) {
            s.push("1");
        }
        leave = leave->p;
    }

    while (s.size() != 0) {
        out << s.top();
        s.pop();
    }
}

/**
 * TODO: Decode the sequence of bits (represented as a char of either '0' or
 * '1') from the istream to return the coded symbol. For this function to work,
 * build() must have been called beforehand to create the HCTree.
 */
// byte HCTree::decode(BitInputStream& in) const { return ' '; }

/**
 * TODO: Decode the sequence of bits (represented as char of either '0' or '1')
 * from istream to return the coded symbol. For this function to work, build()
 * must have been called beforehand to create the HCTree.
 */
byte HCTree::decode(istream& in) const {
    HCNode* curr = root;

    while (1) {
        if (in.eof()) {
            break;
        }

        if (curr->c0 == NULL) {
            break;
        }
        char ch = in.get();

        if (ch == '1') {
            curr = curr->c1;
        }
        if (ch == '0') {
            curr = curr->c0;
        }
    }
    return curr->symbol;
}
