#include "Algorithm.hpp"

using namespace std;

Node::Node()
{
    children = {};
    compact_rep = {};
    visited = false;
    branchless_tuples = {};
    compact_rep = {};
    union_intervals = {};
    startBranchless = false;
    removeNode = false;
}

Node::Node(int new_state)
{
    state = new_state;
    children = {};
    compact_rep = {};
    visited = false;
    branchless_tuples = {};
    compact_rep = {};
    union_intervals = {};
    startBranchless = false;
    removeNode = false;
}

Node::Node(int new_state, Node* parent){
    state = new_state;
    parent_state = parent;
    children = {};
    compact_rep = {};
    visited = false;
    branchless_tuples = {};
    compact_rep = {};
    union_intervals = {};
    startBranchless = false;
    removeNode = false;
}

Node::Node(int new_state, Node* parent, vector<int> new_data) 
{
    state = new_state;
    parent_state = parent;
    children = {};
    compact_rep = {};
    visited = false;
    branchless_tuples = {};
    compact_rep = {};
    union_intervals = {};
    startBranchless = false;
    removeNode = false;
}

Node::~Node()
{
}

void Node::setState(int new_state){
    state = new_state;
}

void Node::setParent(Node* parent){
    parent_state = parent;
}

void Node::addChild(Node* child){
    children.push_back(child);
}

void Node::setVisited(bool new_visited){
    visited = new_visited;
}

void Node::addBranchlessSubpath(vector<int> tuple){
    branchless_tuples.push_back(tuple);
}

void Node::setBranchlessSubpath(vector<vector<int>> b_tuples){
    branchless_tuples = b_tuples;
}

void Node::setCompRep(vector<vector<int>> comp_rep){
    compact_rep = comp_rep;
}

void Node::setUnionIntervals(vector<vector<int>> merged_intervals){
    union_intervals = merged_intervals;
}

void Node::setStartBranchless(){
    startBranchless = true;
}

void Node::removeChildren(){
    children = {};
}

void Node::setRemoveNode(){
    removeNode = true;
}

void Node::clearData_Branchless(){
    branchless_tuples.clear();
}

void Node::clearCompRep(){
    compact_rep.clear();
}

void Node::clearUnion(){
    union_intervals.clear();
}


int Node::getState(){
    return state;
}

Node* Node::getParent(){
    return parent_state;
}

vector<Node* > Node::getChildren(){
    return children;
}

bool Node::getVisited(){
    return visited;
}

vector<vector<int>> Node::getSubpaths(){
    return branchless_tuples;
}

vector<vector<int>> Node::getCompRep(){
    return compact_rep;
}

vector<vector<int>> Node::getUnionIntervals(){
    return union_intervals;
}

bool Node::StartBranchless(){
    return startBranchless;
}

bool Node::getRemoveNode(){
    return removeNode;
}

void Node::insertNode(Node* &node, int new_state, queue<Node* > &q_nodes){
    Node* new_node = new Node(new_state, node);
    vector<Node*> list_children = node->getChildren();
    list_children.push_back(new_node);
    node->children = list_children;
    q_nodes.push(new_node);
}

