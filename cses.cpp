/* JAI MERE KHATU SHYAM */
/* CSES PROBLEMSET */
#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define MOD 1000000007
#define INF 1e18
#define pb push_back
#define ff first
#define ss second
#define endl "\n"

#define all(v) v.begin(),v.end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void stdInputOutput() {
#ifndef ONLINE_JUDGE

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}

#ifdef MISHRA_11
#include "DEBUG.h"
#else
#define debug(x...)
#endif

//CPP Templates
/* ######################################################################################*/

/*###################### SEGMENT TREES TEMPLATE #############################################*/
template<typename Node, typename Update>
struct SegTree {
    vector<Node> tree;
    vector<ll> arr; // type may change
    int n;
    int s;
    SegTree(int a_len, vector<ll> &a) { // change if type updated
        arr = a;
        n = a_len;
        s = 1;
        while (s < 2 * n) {
            s = s << 1;
        }
        tree.resize(s); fill(all(tree), Node());
        build(0, n - 1, 1);
    }
    void build(int start, int end, int index)  // Never change this
    {
        if (start == end)   {
            tree[index] = Node(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(start, mid, 2 * index);
        build(mid + 1, end, 2 * index + 1);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }
    void update(int start, int end, int index, int query_index, Update &u)  // Never Change this
    {
        if (start == end) {
            u.apply(tree[index]);
            return;
        }
        int mid = (start + end) / 2;
        if (mid >= query_index)
            update(start, mid, 2 * index, query_index, u);
        else
            update(mid + 1, end, 2 * index + 1, query_index, u);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }
    Node query(int start, int end, int index, int left, int right) { // Never change this
        if (start > right || end < left)
            return Node();
        if (start >= left && end <= right)
            return tree[index];
        int mid = (start + end) / 2;
        Node l, r, ans;
        l = query(start, mid, 2 * index, left, right);
        r = query(mid + 1, end, 2 * index + 1, left, right);
        ans.merge(l, r);
        return ans;
    }
    void make_update(int index, ll val) {  // pass in as many parameters as required
        Update new_update = Update(val); // may change
        update(0, n - 1, 1, index, new_update);
    }
    Node make_query(int left, int right) {
        return query(0, n - 1, 1, left, right);
    }
};

struct Node1 {
    ll val; // may change
    Node1() { // Identity element
        val = 0;    // may change
    }
    Node1(ll p1) {  // Actual Node
        val = p1; // may change
    }
    void merge(Node1 &l, Node1 &r) { // Merge two child nodes
        val = l.val + r.val;  // may change
    }
};

struct Update1 {
    ll val; // may change
    Update1(ll p1) { // Actual Update
        val = p1; // may change
    }
    void apply(Node1 &a) { // apply update to given node
        a.val = val; // may change
    }
};

/*#################################################################################*/
// For interactive problems
ll query(int l, int r) {
    cout << "? " << l << " " << r << endl;
    ll x;
    cin >> x;
    return x;

}

int idx = 0;
void dfs(vector<int>& flatList, vector<int> adj[], int node, int par, vector<pair<int, int>>& index)
{

    index[node].ff = idx;
    flatList.pb(node);

    idx++;
    for (auto child : adj[node]) {
        if (par == child) continue;
        // cout << child << " ";

        debug(child)
        dfs(flatList, adj, child, node, index);


    }
    index[node].ss = idx;
    flatList.pb(node);
    idx++;


}

int32_t main() {
    stdInputOutput();
    fastio;

    ll n, q;
    cin >> n >> q;
    vector<ll> v1(n + 1);
    for (auto i = 1; i <= n; ++i) {
        cin >> v1[i];
    }

    vector<int> adj[n + 1];
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    debug("Ayush")

    vector<int> flatList;
    vector<pair<int, int>> index(n + 1);

    dfs(flatList, adj, 1, 0, index);
    debug(flatList)
    vector<ll> segVec;
    vector<int> visited(n + 1, 0);
    for (auto it : flatList) {
        if (visited[it] == 0) {
            visited[it] = 1;
            segVec.pb(v1[it]);

        } else {segVec.pb(-v1[it]);}

    }
    debug(segVec)
    ll seg_Len = 2 * n;
    SegTree<Node1, Update1> seg(seg_Len, segVec);
    while (q--) {
        int choice;
        cin >> choice;

        if (choice == 1) {
            int node, val; cin >> node >>  val;
            seg.make_update(index[node].ff, val);
            seg.make_update(index[node].ss, (-1)*val);

        } else {
            int node;
            cin >> node;
            debug(index[node].ff)
            ll ans = seg.make_query(index[1].ff, index[node].ff).val;
            cout << ans << "\n";
        }
    }
    return 0;
}
