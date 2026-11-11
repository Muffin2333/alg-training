/*
 * 蓝桥杯2024C++研究生组A题
 * 考点：自定义运算符
 * 题面：在蓝桥王国，数字的大小不仅仅取决于它们的数值大小，还取决于它们所形成的“封闭图形”的个数。
 封闭图形是指数字中完全封闭的空间，例如数字 1、2、3、5、7 都没有形成封闭图形，而数字 0、4、6、9 分别形成了 1 个封闭图形，数字 8 则形成了 2个封闭图形。值得注意的是，封闭图形的个数是可以累加的。
 例如，对于数字68，由于 6 形成了 1 个封闭图形，而 8 形成了 2 个，所以 68 形成的封闭图形的个数总共为 3。

 在比较两个数的大小时，如果它们的封闭图形个数不同，那么封闭图形个数较多的数更大。

 例如，数字 41 和数字 18，它们对应的封闭图形的个数分别为 1 和 2，因此数字 41 小于数组 18。如果两个数的封闭图形个数相同，那么数值较大的数更大。

 例如，数字 14 和数字 41，它们的封闭图形的个数都是 1，但 14 < 41，所以数字 14 小于数字 41。

 如果两个数字的封闭图形个数和数值都相同，那么这两个数字被认为是相等的。

 小蓝对蓝桥王国的数字大小规则十分感兴趣。现在，他将给定你 n 个数a1, a2, . . . , an，请你按照蓝桥王国的数字大小规则，
 将这 n 数从小到大排序，并输出排序后结果。
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
static int close_area_count[] = {1, 0, 0, 0, 1, 0, 1, 0, 2, 1};
struct Node {
    int value;
    int area_count;

    static Node Build(int value) {
        return Node {value, generate_area_count(value)};
    }

    bool operator <(const Node& rsh) const {
        return area_count == rsh.area_count ? value < rsh.value : area_count < rsh.area_count;
    }

    static int generate_area_count(int p) {
        auto count = 0;
        while (p > 0) {
            count += close_area_count[p % 10];
            p /= 10;
        }
        return count;
    }
};

void test() {
    assert(Node::generate_area_count(20) == 1);
    assert(Node::generate_area_count(84) == 3);
    assert(Node::generate_area_count(18) == 2);
    assert(Node::Build(29) < Node::Build(18));

}

int main() {
    // test();
    int n;
    std::cin >> n ;
    auto vec = std::vector<Node>(n);
    for(int i = 0; i < n; i++) {
        int tmp;
        std::cin >> tmp;
        vec[i] = Node::Build(tmp);
    }
    std::sort(vec.begin(), vec.end());
    for (int i = 0; i < n; i++) {
        if (i) std::cout << " ";
        std::cout << vec[i].value;
    }
}
