//
//  Bst.h
//  BinaryTreeNew
//
//  Created by Shiv chandra Kumar on 11/8/14.
//  Copyright (c) 2014 Shiv chandra Kumar. All rights reserved.
//

#ifndef __BinaryTreeNew__Bst__
#define __BinaryTreeNew__Bst__

#include <stdio.h>
#include <string>

#include <stddef.h>
using namespace std;

//create private classes for all directly usable methods from main and use only public methos.
//using concept of function overloading.
class Bst{
public:
    struct record{
        int x_cord;
        int y_cord;
        string data;
    };
    bool insert(record);
    void print_tree();
    void remove(record*);
    bool remove_data(record,int &,int &);
    bool search(string);
    void makeNull();
    Bst();
    struct Bst_Node{
        record* data;
        Bst_Node *left_node;
        Bst_Node *right_node;
    };
private:
    bool search(Bst_Node*,string);
    Bst_Node *root_node;
    bool insert_into_bst(Bst_Node* &,record*);
    Bst_Node* create_new_node(record*);
    void print_tree_bst(Bst_Node*);
    bool remove_data(Bst_Node*, record*,Bst_Node*,int &,int &);
    record* find_min(Bst_Node*);
    void makeNull(Bst_Node* &,Bst_Node*);
};

#endif /* defined(__BinaryTreeNew__Bst__) */