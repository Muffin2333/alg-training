/*
 * 2024研究生组B题
 * 考点：区间加法，线段树
 *
 */
#include <cmath>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <pthread.h>
#include <string>
#include <vector>
// #define DEBUG

using ll = long long;
enum OpType {
    None, Add, Mul
};
struct Op {
    OpType type;
    ll value;
    std::string to_string() {
        auto str = std::string("");
        switch (type) {
            case None:
                str = "N" + std::to_string(value);
                break;
            case Add:
                str = "A" + std::to_string(value);
                break;
            case Mul:
                str = "M" + std::to_string(value);
        }
        return str;
    }
};

struct SegTree {
    std::vector<ll> data;
    std::vector<Op> ops;

    SegTree(int size, int node[]) {
        data = std::vector<ll>(size * 4);
        ops = std::vector<Op>(size * 4);
        data[0] = build_tree(0, (size - 1) / 2, 1, node) + build_tree((size - 1) / 2 + 1, size - 1, 2, node);
    }

    void range_add(int l, int r, int cl, int cr, int node, int value) {
        if (l <= cl && r >= cr) {
            update_op(cl, cr, node, Op {Add, value});
            return ;
        }

        push_down(cl, cr, node);
        auto mid = (cl + cr) / 2;
        if (l <= mid) {
            range_add(l, r, cl, mid, node * 2 + 1, value);
        }
        if (r > mid) {
            range_add(l, r, mid + 1, cr, node * 2 + 2, value);
        }
        data[node] = data[node * 2 + 1] + data[node * 2 + 2];
    }

    void range_mul(int l, int r, int cl, int cr, int node, int value) {
        if (l <= cl && r >= cr) {
            update_op(cl, cr, node, Op {Mul, value});
            return ;
        }
        push_down(cl, cr, node);
        int mid = (cl + cr) / 2;
        if (l <= mid) {
            range_mul(l, r, cl, mid, node * 2 + 1, value);
        }
        if (r > mid) {
            range_mul(l, r, mid + 1, cr, node * 2 + 2, value);
        }
        data[node] = data[node * 2 + 1] + data[node * 2 + 2];
    }

    int query(int l, int r, int cl , int cr, int node) {
        if (l <= cl && r >= cr) {
            push_down(cl, cr, node);
            return data[node];
        }

        push_down(cl, cr, node);
        int ql, qr;
        auto mid = (cl + cr) / 2;
        if (l <= mid) {
            ql = query(l, r, mid, cr, node * 2 + 1);
        }
        if (r > mid) {
            qr = query(l, r, mid + 1, cr, node * 2 + 2);
        }
        return ql + qr;
    }

    void print(bool op = false) {
        int acc = 0;
        int lev = 0;
        for(int i = 0; i < data.size(); i++) {
            if (acc == pow(2, lev)) {
                std::cout << std::endl;
                acc = 0;
                ++lev;
            }
            if (op) {
                printf("%s ", ops[i].to_string().c_str());
            }
            else {
                printf("%d ", (int)data[i]);
            }
            ++acc;
        }
        printf("\n");
    }

private:
    void push_down(int l, int r, int node) {
        update_op(l, r, node, Op {None, 0});
    }

    void update_op(int l, int r, int node, Op op) {
        auto old_op = ops[node];
        if (op.type == old_op.type) {
            switch (op.type) {
                case None:
                    break;
                case Add:
                    ops[node].value += op.value;
                    break;
                case Mul:
                    ops[node].value *= op.value;
            }
            return ;
        }
        apply_op(l, r, node, old_op);
        ops[node] = op;
        if (old_op.type != None && l != r) {
            auto mid = (l + r) / 2;
            update_op(l, mid, node * 2 + 1, old_op);
            update_op(mid + 1, r, node * 2 + 2, old_op);
        }
    }

    void apply_op(int l, int r, int node, Op op) {
        switch (op.type) {
            case None:
                break;
            case Add:
                data[node] += (r - l + 1) * op.value;
                break;
            case Mul:
                data[node] *= op.value;
                break;
        }
    }

    ll build_tree(int l, int r, int id, int node[]) {
        if (l > r) {
            return 0;
        }
        if (l == r) {
            data[id] = node[l];
            return data[id];
        }
        auto mid = (l + r) / 2;
        data[id] = build_tree(l, mid, id * 2 + 1, node) + build_tree(mid + 1, r, id * 2 + 2, node);
        return data[id];
    }
};

int main() {
    int data[7] = {1, 2, 5, 4, 3, 6, 7};
    auto t = SegTree(7, data);
    t.range_add(0, 4, 0, 7, 0, 5);
    t.range_add(0, 4, 0, 7, 0, 5);
    t.range_mul(0, 4, 0, 7, 0, 5);
    t.print();
    t.print(true);
}
