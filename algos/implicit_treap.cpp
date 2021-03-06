#include <iostream>
#include <vector>
#include <string>

typedef long long ll;

using namespace std;

struct node {
  ll x, y, sz, sum;
  node *l, *r;
  node() {}
  node(ll _x) {
    x = _x;
    y = (rand() << 16) + rand();
    sz = 1;
    sum = 0;
    l = r = nullptr;
  }
  static ll get_sum(node *p) {
    return p ? p->sum : 0;
  }
  static void upd_sum(node *p) {
    p->sum = p->x + get_sum(p->l) + get_sum(p->r);
  }
  static ll get_size(node *p) {
    return p ? p->sz : 0;
  }
  static void upd_size(node *p) {
    p->sz = 1 + get_size(p->l) + get_size(p->r);
  }
  static pair <node*, node*> split(node *p, ll x) {
    if (!p) return {};
    if (get_size(p->l) + 1 <= x) {
      pair <node*, node*> q = split(p->r, x - get_size(p->l) - 1);
      p->r = q.first;
      upd_size(p), upd_sum(p);
      return { p, q.second };
    }
    pair <node*, node*> q = split(p->l, x);
    p->l = q.second;
    upd_size(p), upd_sum(p);
    return { q.first, p };
  }
  static node* merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;
    if (l->y > r->y) {
      l->r = merge(l->r, r);
      upd_size(l), upd_sum(l);
      return l;
    }
    r->l = merge(l, r->l);
    upd_size(r), upd_sum(r);
    return r;
  }
  static void insert(ll val, ll x, node* &root) {
    pair <node*, node*> q = split(root, x);
    node *t = new node(val);
    root = merge(q.first, merge(t, q.second));
  }
  static node* cut(ll l, ll r, node* &root) {
    pair <node*, node*> q1 = split(root, r);
    pair <node*, node*> q2 = split(q1.first, l - 1);
    root = merge(q2.first, q1.second);
    return q2.second;
  }
  static void paste(node* p, ll pos, node* &root) {
    pair <node*, node*> q = split(root, pos - 1);
    root = merge(q.first, merge(p, q.second));
  }
  static ll get(ll l, ll r, node *root) {
    if (l > r) return 0;
    node *p = cut(l, r, root);
    ll ans = p->sum;
    paste(p, l, root);
    return ans;
  }
  static void write(node* p) {
    if (!p) return;
    write(p->l);
    cout << p->x << " ";
    write(p->r);
  }
};

int main() {
  ll q;
  cin >> q;
  node *T = 0;
  while (q--) {
    string s;
    cin >> s;
    if (s == "cutandpaste") {
      int l, r, pos;
      cin >> l >> r >> pos;
      node *tmp = node::cut(l, r, T);
      node::paste(tmp, pos, T);
    }
    if (s == "sum") {
      int l, r;
      cin >> l >> r;
      cout << node::get(l, r, T) << '\n';
    }
    if (s == "insert") {
      int val, pos;
      cin >> val >> pos;
      node::insert(val, pos - 1, T);
    }
    if (s == "erase") {
      int l, r;
      cin >> l >> r;
      node::cut(l, r, T);
    }
    if (s == "write") {
      node::write(T);
      cout << '\n';
    }
    cout << "OK" << '\n';
  }
  return 0;
}
