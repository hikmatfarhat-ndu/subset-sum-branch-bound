#include "Node.h"
#include <string>
#include <queue>
using namespace std;
extern int target;
extern vector<int> s;

void bfs(Node*& t, string& solution) {
    std::queue<Node*> q;

    q.push(t);
    while (!q.empty()) {
        Node* c = q.front();
        q.pop();
        if (c->next != s.end()) {
            if (c->sum + *c->next == target) {//found solution. stop
                solution = c->path + "," + to_string(*c->next);
                break;
            }
            if (c->sum + c->remainder < target) {//skip this branch no solution
                continue;
            }
            c->left = new Node;
            c->left->sum = c->sum + *c->next;
            c->left->next = c->next + 1;
            c->left->remainder = c->remainder - *c->next;
            c->left->path = c->path + "," + to_string(*c->next);
            c->right = new Node;
            c->right->sum = c->sum;
            c->right->next = c->next + 1;
            c->right->remainder = c->remainder - *c->next;
            c->right->path = c->path;
            if (c->left->sum < target)
                q.push(c->left);

            q.push(c->right);

        }

    }

}