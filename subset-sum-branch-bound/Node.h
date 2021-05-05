#pragma once
#include <string>
#include <vector>
using namespace std;

struct Node {
    static int count;
    Node* left;
    Node* right;
    int sum;
    int remainder;
    string path;
    vector<int>::iterator next;
    Node(Node* l = nullptr, Node* r = nullptr, int s = 0, int _r = 0)
        :left(l), right(r), sum(s), remainder(_r), path("") {
        count++;
    }
};