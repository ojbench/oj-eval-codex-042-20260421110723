#ifndef SPEEDCIRCULARLIST_SOLUTION_H
#define SPEEDCIRCULARLIST_SOLUTION_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

constexpr int s_prime = 31;

inline int log2(int x) {
    int ans = 0;
    while (x != 1) {
        x /= 2;
        ++ans;
    }
    return ans;
}

template<typename T, int b_prime>
class SpeedCircularLinkedList {
public:
    struct Node {
        std::map<std::string, T> kv_map;
        int bound = 0;
        Node* next = nullptr;
        Node** fast_search_list = nullptr;

        Node(int bound_in, int fast_search_list_size) {
            bound = bound_in;
            next = nullptr;
            if (fast_search_list_size > 0) {
                fast_search_list = new Node*[fast_search_list_size];
                for (int i = 0; i < fast_search_list_size; ++i) fast_search_list[i] = nullptr;
            } else {
                fast_search_list = nullptr;
            }
        }

        ~Node() {
            if (fast_search_list) {
                delete [] fast_search_list;
                fast_search_list = nullptr;
            }
        }
    };

private:
    Node* head = nullptr;
    int fast_search_list_size = 0;
    int list_size = 0;

    static int GetHashCode(std::string str) {
        long long ans = 0;
        for (auto& ch : str) {
            ans = (ans * s_prime + ch) % b_prime;
        }
        return static_cast<int>((ans + b_prime) % b_prime);
    }

    void BuildFastSearchList() {
        if (!head || list_size <= 1 || fast_search_list_size <= 0) return;
        std::vector<Node*> nodes;
        nodes.reserve(list_size);
        Node* cur = head;
        for (int i = 0; i < list_size; ++i) {
            nodes.push_back(cur);
            cur = cur->next;
        }
        for (int i = 0; i < list_size; ++i) {
            nodes[i]->fast_search_list[0] = nodes[(i + 1) % list_size];
        }
        for (int k = 1; k < fast_search_list_size; ++k) {
            for (int i = 0; i < list_size; ++i) {
                Node* prev = nodes[i]->fast_search_list[k - 1];
                nodes[i]->fast_search_list[k] = prev ? prev->fast_search_list[k - 1] : nullptr;
            }
        }
    }

    Node* find_node_by_code(int code) const {
        if (!head) return nullptr;
        if (code <= head->bound) return head;
        Node* cur = head;
        if (fast_search_list_size <= 0 || list_size <= 1) {
            // Fallback to linear scan
            cur = head->next;
            while (cur != head && cur->bound < code) cur = cur->next;
            return cur;
        }
        for (int k = fast_search_list_size - 1; k >= 0; --k) {
            Node* nxt = cur->fast_search_list[k];
            if (nxt && nxt != head && nxt->bound < code) {
                cur = nxt;
            }
        }
        return cur->next; // first node with bound >= code
    }

public:
    explicit SpeedCircularLinkedList(std::vector<int> node_bounds) {
        list_size = static_cast<int>(node_bounds.size());
        if (list_size == 0) {
            head = nullptr;
            fast_search_list_size = 0;
            return;
        }
        fast_search_list_size = log2(list_size);

        // Create nodes
        std::vector<Node*> nodes;
        nodes.reserve(list_size);
        for (int i = 0; i < list_size; ++i) {
            nodes.push_back(new Node(node_bounds[i], fast_search_list_size));
        }
        // Link circularly
        for (int i = 0; i < list_size; ++i) {
            nodes[i]->next = nodes[(i + 1) % list_size];
        }
        head = nodes[0];

        BuildFastSearchList();
    }

    ~SpeedCircularLinkedList() {
        if (!head) return;
        Node* cur = head;
        for (int i = 0; i < list_size; ++i) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = nullptr;
        list_size = 0;
        fast_search_list_size = 0;
    }

    void put(std::string str, T value) {
        int code = GetHashCode(str);
        // 请不要修改上面这行代码
        if (!head) return;
        Node* node = find_node_by_code(code);
        node->kv_map[str] = value;
    }

    T get(std::string str) {
        int code = GetHashCode(str);
        // 请不要修改上面这行代码
        if (!head) return T();
        Node* node = find_node_by_code(code);
        auto it = node->kv_map.find(str);
        if (it != node->kv_map.end()) return it->second;
        return T(); // 返回T类型默认构造函数产生的值
    }

    void print() {
        if (!head) return;
        Node* cur = head;
        for (int i = 0; i < list_size; ++i) {
            std::cout << "[Node] Bound = " << cur->bound << ", kv_map_size = " << cur->kv_map.size() << '\n';
            cur = cur->next;
        }
    }

    int size() const { return list_size; }
};

#endif // SPEEDCIRCULARLIST_SOLUTION_H

