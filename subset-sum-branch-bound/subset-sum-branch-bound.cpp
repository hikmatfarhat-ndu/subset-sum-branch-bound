/*****************************************************************//**
 * @file   subset-sum-branch-bound.cpp
 * @brief  comparison of subset sum solution between trying all combinations
 * backracking and branch-and-bound
 * The main measure is the number of nodes created.
 * @author Hikmat Farhat
 * @date   May 2021
 *********************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <sstream>
#include <random>
#include <tuple>
#include "Node.h"

using namespace std;

int returns = 0;
random_device e;
uniform_int_distribution<> id(1, 1000);
vector<int> s;
int target = 0;
int Node::count = 0;
/**
 *  all()->void
 *  try all possible combinations until a solution is found
 * @param t
 * @param path
 * @param solution
 */
void all(Node*& t, string path, string& solution) {
    if (solution.size() > 0)return;
    if (t->next != s.end()) {
        if (t->sum + *t->next == target) {
            solution = path + "," + to_string(*t->next);
            return;
        }
        t->left = new Node;
        t->left->sum = t->sum + *t->next;
        t->left->next = t->next + 1;
      //  t->left->remainder = t->remainder - *t->next;
        t->right = new Node;
        t->right->sum = t->sum;
        t->right->next = t->next + 1;
       // t->right->remainder = t->remainder - *t->next;
        all(t->left, path + "," + to_string(*t->next), solution);

        all(t->right, path, solution);
    }
}

/**
 *  backtrack()->void
 * try all the combinations until a solution is found
 * With an additional constraint: if sum of node> target backtrack
 * @param t
 * @param path
 * @param solution
 */
void backtrack(Node*& t, string path, string& solution) {
    if (solution.size() > 0)return;
    if (t->next != s.end()) {
            if (t->sum + *t->next == target) {
                solution = path + "," + to_string(*t->next);
                return;
            }
            t->left = new Node;
            /* left branch includes this node */
            t->left->sum = t->sum + *t->next;
            t->left->next = t->next + 1;
            t->left->remainder = t->remainder - *t->next;
            t->right = new Node;
            /* right branch does not include this node */
            t->right->sum = t->sum;
            t->right->next = t->next + 1;
            t->right->remainder = t->remainder - *t->next;
            if (t->left->sum < target)
             backtrack(t->left, path + "," + to_string(*t->next), solution);

            backtrack(t->right, path, solution);
    }
}
/**
 *  bb()->void
 * try all combinations until a solution is found.
 * With two additional constraints
 * If sum of node >target backtrack
 * If sum of node + remainder < target backtrack
 * @param t
 * @param path
 * @param solution
 */
void bb(Node* &t,string path,string& solution) {
    if (solution.size()>0)return;
    if (t->next != s.end()) {
        if (t->sum + *t->next == target) {
            solution = path + "," + to_string(*t->next);
            return;
        }
        if (t->sum + t->remainder < target) {
            returns++;
            return;
        }
        t->left = new Node;
        t->left->sum = t->sum + *t->next;
        t->left->next = t->next + 1;
        t->left->remainder = t->remainder - *t->next;
        t->right = new Node;
        t->right->sum = t->sum;
        t->right->next = t->next + 1;
        t->right->remainder = t->remainder - *t->next;
        if (t->left->sum < target)
            bb(t->left, path + "," + to_string(*t->next), solution);

        bb(t->right, path, solution);
    }
}


int main()
{   
    
    for (int k = 0; k < 20; k++) {
        s.clear();
        Node::count = 0;
        returns = 0;
        std:: cout << " Trial " << k << endl;
        std::cout << "--------------------------\n";
        int set_size = 15;
       
        for (int i = 0; i < set_size; i++)
            s.push_back(id(e));
        
        std::sort(s.begin(), s.end(), std::greater<int>());
        int remainder = std::accumulate(s.begin(), s.end(), 0);
        target =remainder - id(e);
      
        Node* root;
        string solution = "";

        {
			root = new Node;
			root->remainder = std::accumulate(s.begin(), s.end(), 0);

			std::cout << "target =" << target << endl;

			root->sum = 0;
			root->next = s.begin();
            /* bb solution */
			bb(root, "", solution);

			int total{ 0 };
			if (solution.size() > 0) {

				string val;
				istringstream iss = istringstream(solution);
				solution[0] = '[';
				solution = solution + ']';
				std::cout << "DFS solution is-> " << solution << endl;
				while (getline(iss, val, ','))
                total += atoi(val.c_str());
        }
        std::cout << "nodes created DFS->" << Node::count << endl;
        //std::cout << "returns= " << returns << endl;
        if (total != 0 && total != target)std::cout << "error\n";
        }

        {
            Node::count = 0;
            root = new Node;
            solution = "";
            root->remainder = std::accumulate(s.begin(), s.end(), 0);

            root->sum = 0;
            root->next = s.begin();
            /* backtrack solution */
            backtrack(root, "", solution);
            
            if (solution.size() > 0) {
                solution[0] = '[';
                solution = solution + ']';
                std::cout << "backtrack solution is-> " << solution << endl;
            }
            std::cout << "nodes created backtrack->" << Node::count << endl;
        }
        {
            Node::count = 0;
            root = new Node;
            solution = "";
            root->remainder = std::accumulate(s.begin(), s.end(), 0);

            root->sum = 0;
            root->next = s.begin();
            /* all solution */
            all(root, "", solution);

            if (solution.size() > 0) {
                solution[0] = '[';
                solution = solution + ']';
                std::cout << "all solution is-> " << solution << endl;
            }
            std::cout << "nodes created all ->" << Node::count << endl;
        }
        std::cout << "--------------------------\n";

    }
   
    
}

