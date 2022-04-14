#include "Algorithm.hpp"
#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;


int main(int argc, char** argv) {
    vector<unordered_map<string, int>> Succ;
    // vector<int> A;
    unordered_map<int, int> A;
    vector<int> depth_list;

    string input_file_name = argv[1];
    string output_file_name = argv[2];

    make_trie_file(Succ, input_file_name, depth_list);
    
    cout << "Trie created" << endl;
    
    int i = 1;
    DFS_A_array(Succ, A);

    cout << "Create A array" << endl;

    vector<int> failure_links(Succ.size());
    create_failure_links(Succ, failure_links);

    unordered_map<int, vector<int>> parent_children;
    create_parent_child_map(failure_links, parent_children);

    cout << "failure links created" << endl;

    auto start_time = steady_clock::now();

    Node* root = new Node;
    createFTtree(root, failure_links, parent_children);

    cout << "FTtree created" << endl;

    vector<vector<int>> sorted_tuples;
    unordered_map<int, int> node_index;

    DFS_branchless_interval(root, Succ, A, depth_list, sorted_tuples);
    sort_tuples(sorted_tuples, node_index);

    Succ.clear();
    // A.clear();
    depth_list.clear();

    cout << "branchless interval" << endl;

    // DFS_merge_branchless_sort(root);
    DFS_merge_branchles(root, node_index, sorted_tuples);
    sorted_tuples.clear();
    node_index.clear();
    
    cout << "merge branchless" << endl;

    BFS_merge_intervals(root, output_file_name, A);

    A.clear();

    auto end_time = steady_clock::now();

    cout << "Done" << endl;

    cout << "Elapsed time (milliseconds): " << duration_cast<chrono::milliseconds>(end_time - start_time).count() << endl;

    return 0;
}