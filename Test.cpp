#include <iostream>
#include <vector>


struct Node
{
    int state;
    // Node* parent;
    // vector<Node* > child;
    // vector<int> data;
    
    // void set_state(int);
    // void new_node(int, Node, vector<int>);
};

// void Node::set_state(int state){
//     state = state;
// }

// Node *new_node(int state, vector<int> data){
//     // state = state;
//     // parent = parent;
//     // data = data;

//     Node *temp = new Node;
//     temp->state = state;
//     temp->data = data;
//     return temp;
// }

    // Node *root = new_node(0, {1,1,1});
    // Node *n1 = new_node(10, {2,2,2});
    // Node *n2 = new_node(20, {3,3,3});
    // Node *n3 = new_node(30, {4,4,4});
    // Node *n4 = new_node(40, {5,5,5});

    // root->child.push_back(n1);
    // root->child.push_back(n2);
    // root->child.push_back(n3);
    // n3->child.push_back(n4);

    // Node *root = new_node(0, {});
    // for (int i = 0; i < 10; i++)
    // {
    //     int state = 10 * i;
    //     vector<int> data = {i,i,i};
    //     Node *temp_node = new_node(state, data);

    //     root->child.push_back(temp_node);
    // }
    
    // for (int i = 0; i < root->child.size(); i++)
    // {
    //     cout << root->child[i]->state << "\n";
    // }
    
    // // cout << root->child;




// else if (same_level){
//         vector<Node*> list_children = node->getChildren();
//         Node* new_node = new Node(new_state, node);
//         list_children.push_back(new_node);
//         node->children = list_children;
//     } else {        // add new node to correct parent
//         vector<Node*> list_children_p = node->getChildren();
//         for (Node* node : list_children_p){
//             if (node->getState() == parent_state){
//                 Node* new_node = new Node(new_state, node);
//                 vector<Node*> list_children = node->getChildren();
//                 list_children.push_back(new_node);
//                 node->children = list_children;
//             }
//         }



        // for (int i = 0; i < failure_links.size(); i++)
        // {   
        //     int num_state = i+1;
        //     if (failure_links[i] == parent_state)
        //     {
        //         cout << "state: " << num_state << " parent state: " << parent_state << "\n";
        //         q_states.push(num_state);

        //         current_node->insertNode(current_node, num_state, q_nodes);
        //     }   
        // }



// void DFS_merge_branchless_old (Node* &node){
//     // cout << "parent state: " << node->getState() << endl;
//     vector<Node*> list_children = node->getChildren();
//     // cout << "num children: " << list_children.size() << endl;
//     for (Node* child : list_children){
//         cout << "state: " << child->getState() << endl;
//         vector<vector<int>> comp_rep = {};
//         vector<vector<int>> b_tuples = child->getSubpaths();
        
//         sort(b_tuples.begin(), b_tuples.end());
        
//         vector<vector<vector<int>>> list_comp_rep;

//         for (vector<int> subpath : b_tuples){
//             vector<vector<int>> temp_comp_rep;
//             for (int i = subpath[0]; i <= subpath[1]; i++){
//                 temp_comp_rep.push_back({i,subpath[2]});
//             }
//             list_comp_rep.push_back(temp_comp_rep);
//         }

//         if (list_comp_rep.empty()){
//             comp_rep = {};
//         } else if (list_comp_rep.size() != 1){
//             int i = 0;
//             while (i < list_comp_rep.size()){
//                 if (comp_rep.empty()){
//                     comp_rep = mergeCompRep(list_comp_rep[i], list_comp_rep[i+1]);
//                     i = i + 2;
//                 } else {
//                     comp_rep = mergeCompRep(comp_rep, list_comp_rep[i]);
//                     i++;
//                 }
//             }
//         } else {
//             comp_rep = list_comp_rep[0];
//         }
//         child->setCompRep(comp_rep);
        
//         DFS_merge_branchless_old(child);
//     }
// }

// void getCompactRep(vector<vector<int>> b_subpaths){

// }


// void make_trie(vector<unordered_map<string, int>> &Succ, vector<string> list_strings, vector<int> &depth_list){
//     int num_state = 0;
//     int num_succ = 1;
//     int depth = 1;
//     depth_list.push_back(0);
//     for (string x : list_strings){
//         for (int i = 0; i <= x.size(); i++) {
//             string a;
//             a = x[i];

//             // cout << "string: " << x << " - letter: " << a << "\n";
//             // cout << "num_state: " << num_state << " - num_succ: " << num_succ << "\n";
            
//             if (i == x.size()) {                                                // end of string, add empty map
//                 unordered_map<string, int> temp_map;
//                 Succ.insert(Succ.begin() + num_state, temp_map);
//                 temp_map.clear();
//                 depth = 1;
//                 num_state = 0;
//                 // cout << "Add end of string \n";
//             } else {
//                 if (Succ.empty() or num_state >= Succ.size()) {                 // add new transition to trie
//                     // cout << "Extend trie \n";
//                     unordered_map<string, int> temp_map;
//                     temp_map.insert({a,num_succ});
//                     Succ.insert(Succ.begin() + num_state, temp_map);
//                     temp_map.clear();
//                     // cout << "Extend: Succ[" << num_state << "] = {(" << a << ": " << Succ[num_state][a] << ")} \n";
//                     num_state = num_succ;
//                     num_succ++;
//                     depth_list.push_back(depth);
//                     depth++;
//                 } else {                  
//                     if (state_present(Succ[num_state], a) == false){      // add a new transistion to existing state - checks if the transition is present
//                         // cout << "Add new transition to existing state \n";
                        
//                         unordered_map<string, int> temp = Succ[num_state];
//                         temp.insert(temp.begin(), {a,num_succ});
//                         Succ.at(num_state) = temp;


//                         // cout << "New state: Succ[" << num_state << "] = {(" << a << ": " << Succ[num_state][a] << ")} \n";  
//                         num_state = num_succ;
//                         num_succ++;
//                         depth_list.push_back(depth);
//                         depth++;
//                     } else {                                                    // state + transistion is already present
//                         // cout << "Add existing state \n";
//                         // cout << "Existing: Succ[" << num_state << "] = {(" << a << ": " << Succ[num_state][a] << ")} \n";
//                         unordered_map<string, int> state_table;
//                         state_table = Succ[num_state];
//                         num_state = state_table[a];
//                         state_table.clear();
//                         depth++;
//                     }
//                 }
//             }
//             // cout << "----- \n";
//         }    
//     }
// }

// void A_array_old(vector<unordered_map<string, int>> Succ, int num_state, unordered_map<int, int> &A, int &i){
//     vector<string> keys;
//     for(auto const next_state : Succ[num_state]){
//         keys.push_back(next_state.first);
//     }
//     sort(keys.begin(), keys.end());
//     for (string letter : keys) {
//         int state = Succ[num_state][letter];
//         // cout << state << endl;
//         if(Succ[state].empty()) {
//             // cout << "State added to A: " << state << endl;
//             // A.push_back(state);
//             A.insert({state, i});
//             i++;
//         }
//         A_array_old(Succ, state, A, i);
//     }
// }
