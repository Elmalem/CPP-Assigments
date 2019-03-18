#include "Tree.hpp"
#include <iostream>

using namespace std;

ariel::Tree::Tree():_root(nullptr) {}
ariel::Tree::~Tree(){
  delete _root;
}

int ariel::Tree::root() {
    if(_root == nullptr) {cout<<"empty tree"<<endl;} //empty tree exception
    return _root->value();
}


int ariel::Tree::left(int i) {
    if(!contains(i)){
        cout<<"error"<<endl;
    }
    return _root->left(i);
}


int ariel::Tree::right(int i) {
    if(!contains(i)){
        //לזרוק שגיאה
    }
    return _root->right(i);
}


int ariel::Tree::size() {
    if(_root == nullptr) return 0;
    return _root->size();
}



bool ariel::Tree::contains(int i) {
    if(_root == nullptr) return false;
    else return _root->contains(i);
}



int ariel::Tree::parent(int i) {
    if(_root == nullptr||_root->value()==i) {}//no such element exception
    else return _root->parent(i);
}


ariel::Tree& ariel::Tree::insert(int i) {
    if(contains(i)) {cout<<"already exist"<<endl;}//throws already exsists exception
    if(_root == nullptr) _root = new TreeNode(i);
    else _root = _root->insert(i);
    return *this;
}



ariel::Tree& ariel::Tree::remove(int i) {
    if(!contains(i))//לזרוק שגיאה
    {std::cout<<"error,i not exist in this tree"<<std::endl;}
    else{
    ariel::TreeNode* deleted = _root->getByValue(i);
    _root = _root->remove(i);
    deleted->RemoveChild();
    delete deleted;
    }
    return *this;
}

void ariel::Tree::print() {
    if(_root!= nullptr) {
        _root->print();
        std::cout<<std::endl;
    }
    else std::cout<<"Empty Tree"<<std::endl;
}


ariel::TreeNode::TreeNode(int val):_value(val),_right(nullptr),_left(nullptr) {}
ariel::TreeNode::~TreeNode(){
  delete _right;
  delete _left;
}
int ariel::TreeNode::value() {return _value;}

bool ariel::TreeNode::contains(int i) {
    if(_value==i) return true;
    else if(i<_value){
        if(_left== nullptr) return false;
        else return _left->contains(i);
    }
    else{
        if(_right == nullptr) return false;
        else return _right->contains(i);
    }
}

int ariel::TreeNode::size() {
    int leftCount = 0;
    int rightCount = 0;
    if(_left!= nullptr) leftCount = _left->size();
    if(_right!= nullptr) rightCount = _right->size();
    return leftCount+rightCount+1;
}

ariel::TreeNode* ariel::TreeNode::insert(int i) {
    if(i<_value){
        if(_left == nullptr) _left = new TreeNode(i);
        else _left = _left->insert(i);
    }
    else{
        if(_right == nullptr) _right = new TreeNode(i);
        else _right = _right->insert(i);
    }
    return this;
}

ariel::TreeNode* ariel::TreeNode::remove(int i) {
    if(i<_value) _left = _left->remove(i);
    else if(i>_value) _right = _right->remove(i);
    else{
        if(_left == nullptr) return _right;
        else if(_right == nullptr) return  _left;
        else{
            int minVal = _right->minVal();
            _value = minVal;
            _right = _right->remove(minVal);
        }
    }
    return this;
}


int ariel::TreeNode::minVal() {
    if(_left == nullptr) return _value;
    else return _left->minVal();
}


int ariel::TreeNode::parent(int i) {
    if(i<_value){
        if(_left->value() == i) return _value;
        else return _left->parent(i);
    }
    else{
        if(_right->value() == i) return _value;
        else return _right->parent(i);
    }
}

int ariel::TreeNode::left(int i) {
    if(_value == i) return _left->_value;
    else if(i<_value) return _left->left(i);
    else return _right->left(i);
}

int ariel::TreeNode::right(int i) {
    if(_value == i) return _right->_value;
    else if(i<_value) return _left->right(i);
    else return _right->right(i);
}

ariel::TreeNode* ariel::TreeNode::getByValue(int i) {
    if(i==_value) return this;
    else if(i<_value) return _left->getByValue(i);
    else return _right->getByValue(i);
}

void ariel::TreeNode::print() {
    if(_left!= nullptr) _left->print();
    std::cout<<_value<<",";
    if(_right!= nullptr) _right->print();
}


void ariel::TreeNode::RemoveChild() {
    _left= nullptr;
    _right= nullptr;
}
