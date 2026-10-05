#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <map>
#include <set>
#include <random>
#include <stack>
#include <cmath>

using namespace std;
using ll = long long;
using ld = long double;

const int max_bit = 30;
const int MAX_NODES = 12 * 1e6 + 10;

struct Node {
    int mex;
    int cnt;
    int l_node;
    int r_node;

    Node() : mex(0), cnt(0), l_node(0), r_node(0) {}
};

vector<Node> trie;

int newNode() {
    trie.emplace_back();
    return (int)trie.size() - 1;
}

void init() {
    trie.clear();
    trie.emplace_back();
    newNode();
}

void dop_merge(Node  &node, const Node &left, const Node &right, int sz) {
    node.cnt = min(sz, left.cnt) + min(sz, right.cnt);

    if(node.cnt == 2 * sz) {
        node.mex = 2 * sz;
    } else {
        node.mex = max(left.mex, right.mex);

        if(left.cnt == sz) {
            node.mex = max(node.mex, sz + right.mex);
        }

        if(right.cnt == sz) {
            node.mex = max(node.mex, sz + left.mex);
        }
    }
}

void dop_insert(int x) {
    int node = 1;
    stack<pair<int, int>> path;

    for(int bit = max_bit - 1; bit >= 0; bit--) {
        path.emplace(node, bit);
        if(x >> bit & 1) {
            if(!trie[node].r_node) {
                trie[node].r_node = newNode();
            }
            node = trie[node].r_node;
        } else {
            if (!trie[node].l_node) {
                trie[node].l_node = newNode();
            }
            node = trie[node].l_node;
        }
    }

    trie[node].cnt++;
    trie[node].mex = 1;

    while(!path.empty()) {
        auto [parent, bit] = path.top();
        path.pop();

        int sz = (1 << bit);
        Node &left = trie[trie[parent].l_node];
        Node &right = trie[trie[parent].r_node];

        dop_merge(trie[parent], left, right, sz);
    }
}

void del(int x) {
    int node = 1;
    stack<pair<int, int>> path;

    for(int bit = max_bit - 1; bit >= 0; bit--) {
        path.emplace(node, bit);
        if(x >> bit & 1) {
            node = trie[node].r_node;
        } else {
            node = trie[node].l_node;
        }
    }

    trie[node].cnt--;
    trie[node].mex = (trie[node].cnt > 0);

    while(!path.empty()) {
        auto [parent, bit] = path.top();
        path.pop();

        int sz = 1 << bit;
        Node &left = trie[trie[parent].l_node];
        Node &right = trie[trie[parent].r_node];

        dop_merge(trie[parent], left, right, sz);
    }
}

int main() {
    trie.reserve(MAX_NODES);

    int tt;
    cin >> tt;

    while(tt--) {
        int n, q;
        cin >> n >> q;

        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }

        init();
        for(int x : a) {
            dop_insert(x);
        }

        cout << trie[1].mex << '\n';

        while(q--) {
            int idx, val;
            cin >> idx >> val;
            idx--;

            del(a[idx]);
            dop_insert(val);
            a[idx] = val;

            cout << trie[1].mex << '\n';
        }
    }

    return 0;
}
