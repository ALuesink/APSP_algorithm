#include "Algorithm.hpp"
#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <boost/sort/spreadsort/spreadsort.hpp>


using namespace std;
// using namespace boost;

void getInterval(Node* &node, vector<unordered_map<string, int>> &Succ, unordered_map<int, int> &A, vector<int> &interval){
    queue<int> next_states;
    vector<int> index;
    int start_state = node->getState();
    next_states.push(start_state);
    while (!next_states.empty())
    {    
        int state = next_states.front();
        next_states.pop();
        if(Succ[state].empty()){
            int pos =A.at(state);
            index.push_back(pos);
        } else {
            for(auto const trans : Succ[state]){
                next_states.push(trans.second);
            }
        }
    }

    int min = *min_element(index.begin(), index.end());
    int max = *max_element(index.begin(), index.end());
    interval.push_back(min);
    interval.push_back(max); 
}


void DFS_branchless_interval(Node* &root, vector<unordered_map<string, int>> &Succ, unordered_map<int, int> &A, vector<int> &depth, vector<vector<int>> &sorted_tuples){
    vector<vector<int>> b_tuples = {};
    stack<Node*> S;
    S.push(root);
    
    while (!S.empty()){
        Node* node = S.top();
        S.pop();
        int num_state = node->getState();
        // cout << "State: " << num_state << endl;
        if(!node->getVisited()){
            node->setVisited(true);
            vector<Node*> list_children = node->getChildren();
            if (num_state != 0){
                Node* parent = node->getParent();

                if (list_children.size() == 0 && A.count(num_state) == 0){
                    node->setRemoveNode();
                    if (parent->getChildren().size() == 1){
                        parent->setRemoveNode();
                        parent->setBranchlessSubpath({});
                        b_tuples.clear();
                    }
                } else{
                    vector<int> interval;
                    getInterval(node, Succ, A, interval);
                    interval.push_back(depth[num_state]);

                    if (list_children.size() == 1){
                        node->setStartBranchless();
                    }
                    
                    b_tuples.push_back(interval);
                    
                    if (!node->StartBranchless()){
                        node->setBranchlessSubpath(b_tuples);
                        for (vector<int> tuple : b_tuples){
                            tuple.insert(tuple.begin(), node->getState());
                            sorted_tuples.push_back(tuple);
                        }
                        b_tuples.clear();
                    }

                }
            }
            for (Node* child : list_children){
                S.push(child);
            }
        }
    } 
}

void sort_tuples(vector<vector<int>> &sorted_tuples, unordered_map<int, int> &node_index){
    sort(sorted_tuples.begin(), sorted_tuples.end());
    int num_state = 0;
    int i = 0;
    for(vector<int> tuple : sorted_tuples){
        if(tuple[0] != num_state){
            node_index.insert({tuple[0], i});
            num_state++;
            i++;
        } else{
            i++;
        }
    }
}


void DFS_merge_branchles(Node* &root, unordered_map<int,int> &node_index, vector<vector<int>> &sorted_tuples){
    stack<Node*> S;
    S.push(root);
    while (!S.empty()){
        Node* node = S.top();
        S.pop();
        // cout << "State: " << node->getState() << endl;
        if (!node->getRemoveNode()){
            int num_state = node->getState();
            
            queue<vector<int>> b_tuples;

            int index = node_index[num_state];
            bool start = true;
            
            if (index > 0 || num_state == 1){
                // cout << "State: " << node->getState() << endl;
                while(start){
                    b_tuples.push(sorted_tuples[index]);
                    index++;
                    if(index >= sorted_tuples.size() || sorted_tuples[index][0] != num_state){
                        start = false;
                    }
                }

                int min_element = 0;
                int max_element = 0;
                vector<vector<vector<int>>> clusters;
                vector<vector<int>> indiv_cluster;
                
                            
                int num_tuple = 0;
                while(!b_tuples.empty()){        // loop to get clusters within branchless subpaths
                    vector<int> subpath;
                    subpath = b_tuples.front();
                    subpath.erase(subpath.begin());
                    b_tuples.pop();
                    num_tuple++;
                    if (subpath[0] <= max_element){
                        if (indiv_cluster.empty()){
                            indiv_cluster.push_back({min_element, max_element});
                        }
                        if (indiv_cluster.back()[0] == subpath[0] && indiv_cluster.back()[1] == subpath[1] && indiv_cluster.size() > 1){
                            indiv_cluster.pop_back();
                        }
                        if (subpath[0] > max_element){
                            max_element = subpath[1];
                            indiv_cluster[0] = {min_element, max_element};
                        }
                        indiv_cluster.push_back(subpath);
                    } else {
                        if(!indiv_cluster.empty()){
                            clusters.push_back(indiv_cluster);
                        }
                        min_element = subpath[0];
                        max_element = subpath[1];
                        indiv_cluster = {};
                        indiv_cluster.push_back({min_element, max_element});
                        indiv_cluster.push_back(subpath);
                    }
                    
                    if(b_tuples.empty()){
                        clusters.push_back(indiv_cluster);
                    }
                    
                }
                indiv_cluster.clear();

                vector<vector<int>> vector_stack;
                vector<vector<int>> comp_rep;

                for (int i = 0; i < clusters.size(); i++){              // loop to get compact representation
                    // cout << "Cluster: " << i << endl;
                    vector<vector<int>> cluster = clusters[i];
                    int min = cluster[0][0];
                    int max = cluster[0][1];
                    int k = min;
                    cluster.erase(cluster.begin());
                    for ( ; k <= max; k++){
                        while(!cluster.empty()){
                            vector<int> subpath = cluster[0];
                            if(subpath[0] == k){
                                if(k != min){
                                    vector_stack.insert(vector_stack.begin(), {subpath[1],subpath[2]});
                                } else {
                                    vector_stack.push_back({subpath[1],subpath[2]});
                                }
                                cluster.erase(cluster.begin());
                            } else {
                                break;
                            }
                        }
                        int max_label = 0;
                        while(!vector_stack.empty()){
                            vector<int> int_label = vector_stack[0];
                            if (k <= int_label[0] && int_label[1] > max_label){
                                comp_rep.push_back({k, int_label[1]});
                                max_label = int_label[1];
                            }
                            if (k == int_label[0]){
                                vector_stack.erase(vector_stack.begin());
                            } else {
                                break;
                            }
                        }
                    }
                }
                
                vector_stack.clear();
                node->setCompRep(comp_rep);
                comp_rep.clear();
            }
            node->clearData_Branchless();

            vector<Node*> list_children;
            list_children = node->getChildren();
            for (Node* child : list_children){
                S.push(child);
            }
            list_children.clear();
        }
    }
}


vector<vector<int>> mergeCompRep(vector<vector<int>> &u_set, vector<vector<int>> &v_set){
    vector<vector<int>> merged_intervals;
    int n = 0;
    int m = 0;
    while (n < u_set.size() || m < v_set.size()) {
        
        if (n == u_set.size()){
            vector<int> m_interval = v_set[m];
            merged_intervals.push_back(m_interval);
            m++;
        } else if (m == v_set.size()) {
            vector<int> n_interval = u_set[n];
            merged_intervals.push_back(n_interval);
            n++;
        } else {
            vector<int> n_interval = u_set[n];
            vector<int> m_interval = v_set[m];
    
            if (n_interval[0] > m_interval[0]){
                merged_intervals.push_back(m_interval);
                m++;
            } else if (n_interval[0] < m_interval[0]){
                merged_intervals.push_back(n_interval);
                n++;
            } else if (n_interval[0] == m_interval[0]){
                if (n_interval[1] >= m_interval[1]){
                    merged_intervals.push_back(n_interval);
                } else {
                    merged_intervals.push_back(m_interval);
                }
                m++;
                n++;
            } else if (n == u_set.size()) {
                merged_intervals.push_back(m_interval);
                m++;
            } else if (m == v_set.size()) {
                merged_intervals.push_back(n_interval);
                n++;
            }
        }
    }
    return merged_intervals;
}


void BFS_merge_intervals (Node* &node, string &file_name, unordered_map<int, int> &A){
    ofstream out_file;
    out_file.open(file_name);
    out_file << "String a - string b: depth" << endl;
    
    vector<vector<int>> u_comp_rep;
    queue<Node*> Q;
    Q.push(node);
    while (!Q.empty()){
        Node* current_node = Q.front();
        Q.pop();
        vector<Node*> list_children = current_node->getChildren();
        
        for (Node* child : list_children) {
            if (!child->getRemoveNode()){
                // cout << "current state: " << child->getState() << "\t parent state: " << current_node->getState() << endl;
                Q.push(child);
                
                if (!child->StartBranchless()){
                    vector<vector<int>> merged_intervals;
                    vector<vector<int>> u_comp_rep;
                    vector<vector<int>> v_comp_rep = child->getCompRep();

                    u_comp_rep = current_node->getUnionIntervals();
                    merged_intervals = mergeCompRep(u_comp_rep, v_comp_rep);

                    child->setUnionIntervals(merged_intervals);
                    child->clearCompRep();

                } else {
                    child->setUnionIntervals(current_node->getUnionIntervals());
                }
                if (child->getChildren().size() == 0){
                    for (vector<int> int_label : child->getUnionIntervals()){
                        int state = child->getState();
                        int index = A.at(state);

                        out_file << index << " - " << int_label[0] << ": " << int_label[1] << endl;
                        // cout << state << " - " << int_label[0] << ": " << int_label[1] << endl;

                    }
                }
            }
        }
        current_node->clearUnion();
    }
    out_file.close();
}

void DFS_merge_intervals(Node* &root, string &file_name, unordered_map<int, int> &A){
    stack<Node*> S;
    S.push(root);
    while(!S.empty()){
        Node* current_node = S.top();
        S.pop();
        cout << "Current node: " << current_node->getState() << endl;

        if(!current_node->getRemoveNode()){


            vector<Node*> list_children = current_node->getChildren();
            for(Node* child : list_children){
                if(!child->getRemoveNode()){
                    S.push(child);
                }
            }
            list_children.clear();
        }
    }
}