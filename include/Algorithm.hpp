#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

class Node 
{
private:
    int state;
    Node* parent_state;
    vector<Node* > children;
    bool visited;
    vector<vector<int>> branchless_tuples;
    vector<vector<int>> compact_rep;
    vector<vector<int>> union_intervals;
    bool startBranchless;
    bool removeNode;

public:
    void setState(int state);
    void setParent(Node* parent);
    void addChild(Node* child);
    void setVisited(bool visited);
    void addBranchlessSubpath(vector<int> subpath);
    void setBranchlessSubpath(vector<vector<int>> b_tuples);
    void setCompRep(vector<vector<int>> comp_rep);
    void setUnionIntervals(vector<vector<int>> merged_intervals);
    void setStartBranchless();
    void removeChildren();
    void setRemoveNode();       // is true when needs to be removed

    void clearData_Branchless();
    void clearCompRep();
    void clearUnion();

    int getState();
    Node* getParent();
    vector<Node* > getChildren();
    bool getVisited();
    vector<vector<int>> getSubpaths();
    void insertNode(Node* &node, int state, queue<Node* > &q_nodes);
    vector<vector<int>> getCompRep();
    vector<vector<int>> getUnionIntervals();
    bool StartBranchless();
    bool getRemoveNode();



    Node();
    Node(int state);
    Node(int state, Node* parent_state);
    Node(int state, Node* parent_state, vector<int> data);
    ~Node();
};

void make_trie_file(vector<unordered_map<string, int>> &Succ, string &file_name, vector<int> &depth_list);
bool state_present(unordered_map<string, int> &succ_state, string &a);
void create_failure_links(vector<unordered_map<string, int>> &trie, vector<int> &failure_links);
int target_by_failure(vector<unordered_map<string, int>> &trie, vector<int> &failure_links, int &num_state, string &a);
void DFS_A_array(vector<unordered_map<string, int>> &Succ, unordered_map<int, int> &A);
void createFTtree(Node* &root, vector<int> &failure_links, unordered_map<int, vector<int>> &parent_child_map);

void getInterval(Node* &node, vector<unordered_map<string, int>> &Succ, unordered_map<int, int> &A, vector<int> &interval);
void DFS_branchless_interval(Node* &root, vector<unordered_map<string, int>> &Succ, unordered_map<int, int> &A, vector<int> &depth, vector<vector<int>> &sorted_tuples);
void create_parent_child_map(vector<int> &failure_links, unordered_map<int, vector<int>> &map_parent_child);
void DFS_merge_branchless_sort (Node* &root);
void DFS_merge_branchles(Node* &root, unordered_map<int,int> &node_index, vector<vector<int>> &sorted_tuples);
void BFS_merge_intervals(Node* &node, string &file_name, unordered_map<int, int> &A);
void sort_tuples(vector<vector<int>> &sorted_tuples, unordered_map<int, int> &node_index);
void DFS_merge_intervals(Node* &root, string &file_name, unordered_map<int, int> &A);
void DFS_recursive(Node* &node, ofstream &out_file, unordered_map<int, int> &A, vector<stack<vector<int>>> &STACK, vector<vector<int>> &previous_vec);