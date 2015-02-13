//
//  Bst.cpp
//  BinaryTreeNew
//
//  Created by Shiv chandra Kumar on 11/8/14.
//  Copyright (c) 2014 Shiv chandra Kumar. All rights reserved.
//

#include "Bst.h"
#include <stddef.h>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
//constructor
Bst::Bst(void){
    root_node = NULL;
}


//create a new Internal node whenever this method is called from any other methods.
Bst::Bst_Node* Bst::create_new_node(record* data){
    Bst_Node* new_node = new Bst_Node();
    new_node->data = new record();
    new_node->data->data = data->data;
    new_node->data->x_cord = data->x_cord;
    new_node->data->y_cord = data->y_cord;
    new_node->left_node = NULL;
    new_node->right_node = NULL;
    return new_node;
}

//private method for insert
bool Bst::insert(record data){
    record* dataptr = new record;
    dataptr->data = data.data;
    dataptr->x_cord = data.x_cord;
    dataptr->y_cord = data.y_cord;
    return(insert_into_bst(root_node, dataptr));
    
}

//Public method for inserting a record
bool Bst::insert_into_bst(Bst_Node* &root_node,record* data){
    bool result = false;
    if(!search(data->data)){
    
    if(root_node == NULL){
        root_node = create_new_node(data);
    }
    else if(root_node->data->data > data->data){
        result = insert_into_bst(root_node->left_node , data);
    }
    else{
        result = insert_into_bst(root_node->right_node , data);
    }
    }
    else{
        cout<<"The above search shows the there already exist a city with same name.record added succesfully for:"<<data->data<<","<<data->x_cord<<","<<data->y_cord<<endl;
    }
    
    return result;
}

//printing the Binary search tree in Inorder traversal for cross checking.
void Bst::print_tree_bst(Bst_Node* root_node){
    if(root_node == NULL){
        return;
    }
    if(root_node->left_node != NULL){
    print_tree_bst(root_node->left_node);
    }
    cout<<root_node->data->x_cord<<","<<root_node->data->y_cord<<","<<root_node->data->data<<endl;
    if(root_node->right_node != NULL){
    print_tree_bst(root_node->right_node);
    }
}

//public method for printing the Binary search tree.
void Bst::print_tree(){
    print_tree_bst(root_node);
    return;
}


//Public method for Search by name of city from a binary search tree
bool Bst::search(string city_name){
    return(search(root_node,city_name));
}


//Private function the same search method
bool Bst::search(Bst_Node* node,string city_name){
    bool result = false;
    if(node ==  NULL){
        return false;
    }
    else if(node->data->data > city_name){
        result = search(node->left_node,city_name);
    }
    else if(node->data->data < city_name){
        result = search(node->right_node,city_name);
    }
    else{
        cout<<endl;
        cout<<"searc complete for city:"<<city_name<<",cordinates are:"<<node->data->x_cord<<","<<node->data->y_cord<<endl;
        return true;
    }
    
    return result;
}



//delete entire tree
void Bst::makeNull(){
    return(makeNull(root_node,root_node));
}


//private method of deleting tree
void Bst::makeNull(Bst_Node* &node,Bst_Node* parent){
    if (node == NULL) {
        
        return;
    }
            makeNull(node->left_node,node);
            makeNull(node->right_node,node);
            delete node->data;
            node->data = NULL;
            delete node;
            node = NULL;
    
        return;
}




//methods for removing record from the Binary search tree

bool Bst::remove_data(record instance,int &x_coordinate,int &y_coordinate){
    record* dataptr = new record;
    dataptr->data = instance.data;
    dataptr->x_cord = instance.x_cord;
    dataptr->y_cord = instance.y_cord;
    return(remove_data(root_node,dataptr,root_node,x_coordinate,y_coordinate));
}



bool Bst::remove_data(Bst_Node* node,record* data,Bst_Node* parent,int &x_coordinate, int &y_coordinate){
    bool set = false;
    int x;
    int y;
 if (node == NULL) {
     return  false;
 }
 if (node->data->data > data->data) {
     remove_data(node->left_node, data,node,x_coordinate,y_coordinate);
 }else if(node->data->data < data->data){
     remove_data(node->right_node,data,node,x_coordinate,y_coordinate);
 }
 else{
 if ((node->left_node != NULL) && (node->right_node != NULL)){
      x = node->data->x_cord;
      y = node->data->y_cord;
     set = true;
     node->data = find_min(node->right_node);
     data = node->data;
     remove_data(node->right_node,data,node,x_coordinate,y_coordinate);
 }
 else if(node->left_node == NULL && node->right_node != NULL){
     if(set == false){
     x_coordinate = node->data->x_cord;
     y_coordinate = node->data->y_cord;
     }
     Bst_Node* temp_node = new Bst_Node;
     temp_node =  node->right_node;
     node->data->data = node->right_node->data->data;
     
     
     delete temp_node;
     node->right_node = NULL;
 }
 else if(node->right_node == NULL && node->left_node != NULL){
     if(set== false){
     x_coordinate = node->data->x_cord;
     y_coordinate = node->data->y_cord;
     }
     Bst_Node* temp_node = new Bst_Node;
     temp_node =  node->left_node;
     node->data->data = node->left_node->data->data;
     node->data->x_cord = node->left_node->data->x_cord;
     node->data->y_cord = node->left_node->data->y_cord;
     
     delete temp_node;
     node->left_node = NULL;
 }
 else if(node->right_node == NULL && node->left_node == NULL){
     string child;
     if(set == false){
     x_coordinate = node->data->x_cord;
     y_coordinate = node->data->y_cord;
     }
     if(parent->left_node->data->data == node->data->data){
         child = "left";
     }
     else{
         child = "right";
     }
     Bst_Node* temp_node = new Bst_Node;
     temp_node = node;
     delete temp_node;
     if(child == "right"){
         parent->right_node = NULL;
     }
     else{
         parent->left_node = NULL;
     }
}
     
}
    if(set == true){
        x_coordinate = x;
        y_coordinate = y;
    }
 return true;
}


//find minimum node method used inside remove method of the tree for removal of node which has two children
Bst::record* Bst::find_min(Bst_Node* node){
 if (node == NULL) {
 return NULL;
 }
 if (node->left_node == NULL) {
 return node->data;
 }
 return (find_min(node->left_node));
}
