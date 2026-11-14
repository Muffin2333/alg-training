/*
 * General purpose seg tree supports multi op
 */
#include <vector>
#include <cassert>
#include <iostream>
#define LCH(x) (x * 2 + 1) 
#define RCH(x) (x * 2 + 2)
// #define TEMPLATE1
#define TEMPLATE2
// #define TEMPLATE3
#define LLONG_MAX 9223372036854775807LL
using ll = long long;

struct Op {
    ll mul;
    ll add;
    Op& operator +=(const Op& rhs) {
        mul *= rhs.mul;
        add = add * rhs.mul + rhs.add;
        return *this;
    }
};

struct SegTree {
    std::vector<ll> data;
    std::vector<Op> ops;
    ll moder;
    SegTree(int size, ll input[], ll moder = LLONG_MAX):moder(moder) {
        data = std::vector<ll>(size * 4);
        ops = std::vector<Op>(size * 4);
        std::fill(ops.begin(), ops.end(), Op{1, 0});
        build(0, size - 1, 0, input);
    }
    
    void build(int cl, int cr, int id, ll input[]) {
        if (cl > cr) {
            return ;
        } 
        if (cl == cr) {
            data[id] = input[cl] % moder;
            return ;
        } 
        int mid = (cl + cr) / 2;
        build(cl, mid, LCH(id), input);
        build(mid + 1, cr, RCH(id), input);
        data[id] = (data[LCH(id)] + data[RCH(id)]) % moder;
    }
    
    ll query(int l, int r, int cl, int cr, int id) {
        if (l <= cl && r >= cr) {
            return data[id];
        } 
        push_down(cl, cr, id);
        int mid = (cl + cr) / 2;
        ll sum = 0;
        if (l <= mid) {
            sum += query(l, r, cl, mid, LCH(id)); 
        }
        if (r > mid) {
            sum += query(l, r, mid + 1, cr, RCH(id));
        }
        return sum % moder;
    }

    void apply_range(int l, int r, int cl, int cr, int id, Op op) {
        if (l <= cl && r >= cr) {
            apply_op(cl, cr, id, op);
            return ;
        }
        
        push_down(cl, cr, id); 
        int mid = (cl + cr) / 2;
        if (l <= mid) {
            apply_range(l, r, cl, mid, LCH(id), op);
        }
        if (r > mid) {
            apply_range(l, r, mid + 1, cr, RCH(id), op);
        }
        data[id] = data[LCH(id)] + data[RCH(id)];
    }
    
    void apply_op(int cl, int cr, int id, Op op) {
        data[id] = (((data[id] * op.mul) % moder) + (((cr - cl + 1) * op.add) % moder)) % moder;
        ops[id] += op;
    }
    
    void push_down(int cl, int cr, int id) {
        if (cl == cr) {
            return ;
        } 
        
        Op op = ops[id]; 
        if (op.mul == 1 && op.add == 0) {
            return ;
        }
        int mid = (cl + cr) / 2;
        apply_op(cl, mid, LCH(id), op);
        apply_op(mid + 1, cr, RCH(id), op);
        ops[id] = Op {1, 0};
   }
};

void test() {
    ll data[] = {1, 5, 4, 2, 3};
    SegTree seg = SegTree(5, data);
    seg.apply_range(1, 2, 0, 4, 0, Op {1, 2});
    seg.apply_range(0, 4, 0, 4, 0, Op {1, 1});
    assert(seg.query(1, 2, 0, 4, 0) == 15);
    assert(seg.query(0, 4, 0, 4, 0) == 24);
    ll data2[] = {1};
    SegTree seg2 = SegTree(1, data);
    assert(seg2.query(0, 0, 0, 0, 0) == 1);
}

int main() {
#ifdef TEMPLATE1
    int n, m;
    std::cin >> n >> m;
    auto initial = std::vector<ll>(n);
    for (int i = 0; i < n; i++) std::cin >> initial[i];
    SegTree seg = SegTree(n, initial.data());
    for (int i = 0; i < m; i++) {
        int op, lsh, rsh;
        ll k;
        std::cin >> op;
        switch (op)
        {
        case 1:
            std::cin >> lsh >> rsh >> k;
            seg.apply_range(lsh - 1, rsh - 1, 0, n - 1, 0, Op {1, k});
            break;
        case 2:
            std::cin >> lsh >> rsh;
            std::cout << seg.query(lsh - 1, rsh - 1, 0, n - 1, 0) << std::endl;
            break;
        default:
            break;
        }
    }
#endif
    
#ifdef TEMPLATE2 
    int n, m;
    std::cin >> n >> m;
    auto initial = std::vector<ll>(n);
    for (int i = 0; i < n; i++) initial[i] = i + 1;
    SegTree seg = SegTree(n, initial.data());
    for (int i = 0; i < m; i++) {
        int op, lsh, rsh;
        ll k;
        std::cin >> op;
        switch (op)
        {
        case 1:
            std::cin >> lsh >> rsh >> k;
            seg.apply_range(lsh - 1, rsh - 1, 0, n - 1, 0, Op {1, k});
            break;
        case 2:
            std::cin >> lsh >> rsh;
            std::cout << seg.query(lsh - 1, rsh - 1, 0, n - 1, 0) << std::endl;
            break;
        default:
            break;
        }
    }
#endif
}
