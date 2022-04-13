#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Node 
{
private:
    int state;
    Node* parent_state;
    vector<Node* > children;
    vector<int> data;
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
    void setData(vector<int> new_data);
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

    int getState();
    Node* getParent();
    vector<Node* > getChildren();
    vector<int> getData();
    bool getVisited();
    vector<vector<int>> getSubpaths();
    void insertNode(Node* &node, int state, queue<Node* > &q_nodes);
    vector<vector<int>> getCompRep();
    vector<vector<int>> getUnionIntervals();
    bool getStartBranchless();
    bool getRemoveNode();

    // void DFS(Node* &node);


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
// vector<int> getArray(vector<unordered_map<string,int>> &Succ);
void DFS_A_array(vector<unordered_map<string, int>> &Succ, unordered_map<int, int> &A);
void createFTtree(Node* &node, vector<int> &failure_links);

void getInterval(Node* &node, vector<unordered_map<string, int>> &Succ, unordered_map<int, int> &A, vector<int> &interval);
void DFS_branchless_interval(Node* &root, vector<unordered_map<string, int>> &Succ, unordered_map<int, int> &A, vector<int> &depth);
void DFS_merge_branchless_sort (Node* &root);
void BFS_merge_intervals(Node* &node, string &file_name, unordered_map<int, int> &A);
void sort_tuples(vector<vector<int>> &sorted_tuples, unordered_map<int, int> &node_index);



