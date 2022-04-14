#include "Algorithm.hpp"
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <iostream>
#include <fstream>


using namespace std;

// Check if the state is already present
bool state_present(unordered_map<string, int> &succ_state, string &a){
    if(succ_state.find(a) != succ_state.end()){
        return true;
    } else {
        return false;
    }
}

unordered_map<string, int> insert_trans(unordered_map<string, int> &old, string &a, int &state){
    unordered_map<string, int> temp ({{a,state}});
    temp.insert(old.begin(), old.end());
    return temp;
}

void make_trie_file(vector<unordered_map<string, int>> &Succ, string &file_name, vector<int> &depth_list){
    ifstream input_file;
    input_file.open(file_name);
    char char_letter;
    bool start_trie = true;
    
    int num_state = 0;
    int num_succ = 1;
    int depth = 1;
    depth_list.push_back(0);

    while (input_file.get(char_letter)){
        string a(1, char_letter);
        if (a == ">"){
            start_trie = false;
        }
        if (start_trie && a != "\r"){
            // add letter to trie
            if (a == "\n") {                                                // end of string, add empty map
                unordered_map<string, int> temp;
                Succ.insert(Succ.begin() + num_state, temp);
                temp.clear();
                depth = 1;
                num_state = 0;
                // cout << "Add end of string \n";
            } else {
                if (Succ.empty() or num_state >= Succ.size()) {                 // add new transition to trie
                    // cout << "Extend trie \n";
                    unordered_map<string, int> temp;
                    temp.insert({a,num_succ});
                    Succ.insert(Succ.begin() + num_state, temp);
                    temp.clear();
                    // cout << "Extend: Succ[" << num_state << "] = {(" << a << ": " << Succ[num_state][a] << ")} \n";
                    num_state = num_succ;
                    num_succ++;
                    depth_list.push_back(depth);
                    depth++;
                } else {                  
                    if (state_present(Succ[num_state], a) == false){      // add a new transistion to existing state - checks if the transition is present
                        // cout << "Add new transition to existing state \n";
                        
                        unordered_map<string, int> temp = Succ[num_state];
                        temp.insert(temp.begin(), {a,num_succ});
                        Succ.at(num_state) = temp;


                        // cout << "New state: Succ[" << num_state << "] = {(" << a << ": " << Succ[num_state][a] << ")} \n";  
                        num_state = num_succ;
                        num_succ++;
                        depth_list.push_back(depth);
                        depth++;
                    } else {                                                    // state + transistion is already present
                        // cout << "Add existing state \n";
                        // cout << "Existing: Succ[" << num_state << "] = {(" << a << ": " << Succ[num_state][a] << ")} \n";
                        unordered_map<string, int> state_table;
                        state_table = Succ[num_state];
                        num_state = state_table[a];
                        state_table.clear();
                        depth++;
                    }
                }
            }
        }
        if (a == "\n"){
            start_trie = true;
        }
    }
    input_file.close();

    // Add last node - end of the file
    unordered_map<string, int> end_map;
    Succ.insert(Succ.begin() + num_succ, end_map);
    end_map.clear();
}

int target_by_failure(vector<unordered_map<string, int>> &trie, vector<int> &failure_links, int &p, string &a){
    bool root_state = false;
    while (p != -1 and state_present(trie[p], a) != true){
        p = failure_links[p];
    }
    if (p == -1)     // root state is state -1
    {
        int fail_state = 0;
        return fail_state;
    } else {            // return the state that matches the state and letter
        int fail_state = trie[p][a];
        return fail_state;
    }
}

void create_failure_links(vector<unordered_map<string, int>> &trie, vector<int> &failure_links){
    // vector<int> failure_links(trie.size());
    failure_links[0] = -1;

    queue<int> F;
    F.push(0);                                      // add root state to queue

    while (!F.empty()) {
        int t = F.front();                          // get the first state in the queue
        F.pop();
        unordered_map<string, int>* temp_map;
        temp_map = &trie[t];                         // get all the transitions of state t
        for (auto const &pair: *temp_map) {          // for each pair (a,p) of the transisitions of state t
            string a = pair.first;
            int p = pair.second;
            // cout << "state: " << p << "\n";
            if (t == 0){                            // state 0 is root state
                failure_links[p] = 0;
            } else{                                 // for all non-root transitions 
                int fail_t = failure_links[t];     
                int fail_state = target_by_failure(trie, failure_links, fail_t, a);         // get the failure link for state p
                failure_links[p] = fail_state;
            }
            F.push(p);                              // add state p to the queue
        }        
    }
}

void create_parent_child_map(vector<int> &failure_links, unordered_map<int, vector<int>> &map_parent_child){
    for(int i = 1; i < failure_links.size(); i++){  ///skip root
        if (map_parent_child.find(failure_links[i]) == map_parent_child.end()){
            map_parent_child[failure_links[i]] = {i};
        } else{
            map_parent_child[failure_links[i]].push_back(i);
        }   
    }
}

void DFS_A_array(vector<unordered_map<string, int>> &Succ, unordered_map<int, int> &A){
    int i = 1;
    stack<int> S;
    S.push(0);

    while (!S.empty()){
        int num_state = S.top();
        S.pop();
        // cout << "State: " << num_state << endl;
        unordered_map<string, int> state = Succ[num_state];

        if (Succ[num_state].empty()){
                A.insert({num_state, i});
                i++;
        }

        for(auto const goto_trans : state){
            // string letter = goto_trans.first;
            int next_state = goto_trans.second;
            S.push(next_state);
        }
    }
}


void createFTtree(Node* &root, vector<int> &failure_links, unordered_map<int, vector<int>> &parent_child_map){
    root->setState(0);
    root->setParent(NULL);

    queue<int> q_states;
    q_states.push(0);

    queue<Node *> q_nodes;
    q_nodes.push(root);
    while (!q_states.empty())
    {
        int parent_state = q_states.front();
        q_states.pop();

        Node* current_node = q_nodes.front();
        q_nodes.pop();

        vector<int> list_children = parent_child_map[parent_state];
        for (int child : list_children){
            q_states.push(child);
            current_node->insertNode(current_node, child, q_nodes);
        }
        
    }
}

//TODO: failure links to hashmap parent:{children}
// 