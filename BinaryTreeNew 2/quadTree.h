//
//  quadTree.h
//  BinaryTreeNew
//
//  Created by Shiv chandra Kumar on 11/10/14.
//  Copyright (c) 2014 Shiv chandra Kumar. All rights reserved.
//

////create private classes for all directly usable methods from main and use only public methos.
//using concept of function overloading.
#ifndef __BinaryTreeNew__quadTree__
#define __BinaryTreeNew__quadTree__
#include <cstring>
#include <stdio.h>
#include <string>
#include <stddef.h>
using namespace std;
class Quad{
public:
    struct record{
        int x_cord;
        int y_cord;
        string data;
    };
    struct quad_node{
        quad_node* NW_node;
        quad_node* NE_node;
        quad_node* SW_node;
        quad_node* SE_node;
        record* value ;
        bool is_leaf;
        bool is_empty;
    };
    bool remove(record);
    bool insert(record);
    int evaluate_quadrant(record*,int,int,int,int);
    void print();
    void search_radius(int,int,int);
    record* search(int,int);
    //static Quad* getInstance();
    void makeNull();
    Quad();
    
private:
    
    quad_node* root  ;
    bool insert(record*,quad_node* &, int,int,int,int);
    quad_node* create_new_quadnode();
    quad_node* create_leaf_node(record*);
    bool remove(record*,quad_node* &, int,int,int,int);
    void print(quad_node*);
    record* search(quad_node*,int,int,int,int,int,int);
    void search_radius(quad_node*,int,int,int);
    void makeNull(quad_node* &);
    
};



#endif /* defined(__BinaryTreeNew__quadTree__) */
