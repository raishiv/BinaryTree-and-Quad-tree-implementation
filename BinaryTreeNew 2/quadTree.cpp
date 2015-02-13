//
//  quadTree.cpp
//  BinaryTreeNew
//
//  Created by Shiv chandra Kumar on 11/10/14.
//  Copyright (c) 2014 Shiv chandra Kumar. All rights reserved.
//

#include "quadTree.h"
#include <stddef.h>
#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
using namespace std;

Quad::Quad(void){
    root = NULL;
}
bool Quad::insert(record city_record){
    record *city_record_ptr = new record;
    city_record_ptr->data = city_record.data;
    city_record_ptr->x_cord = city_record.x_cord;
    city_record_ptr->y_cord = city_record.y_cord;
    
    return(insert(city_record_ptr,root,0,0,16383,16383));
}

bool Quad::insert(record* city_record,quad_node* &node,int x1,int y1,int x2,int y2){
    //NW =1, NE =2, SW =3 , SE = 4
    if(node == NULL){
        node = new quad_node();
        node->NW_node = NULL;
        node->NE_node = NULL;
        node->SW_node = NULL;
        node->SE_node = NULL;
        node->value = new record();
        node->is_leaf = false;
        node->is_empty = true;
    }
    record* existing_record ;
    int quadrant = 0;
    bool result = false;
    quadrant = evaluate_quadrant(city_record,x1,y1,x2,y2);
    if(quadrant == 5){
        return false;
    }
    else if(quadrant == 1){  //northwestern quadrant
      
        /*check for existence of value if not present write
         value otherwise split the quadrant again. also assign 
         typical values of x and y cordinates accordingly*/
        x2 = (x1+x2)/2;
        y2 = (y1+y2)/2;
        if(node->NW_node == NULL){
            quad_node*  new_node;
            new_node = create_leaf_node(city_record);
            node->NW_node = new_node;
            result = true;
        }
        else{
            if(node->NW_node->is_leaf == true){
                existing_record = search(city_record->x_cord,city_record->y_cord);
                if(existing_record->data == city_record->data){
                    cout<<"Duplicate error: Record of this city is already there:"<<city_record->x_cord<<","<<city_record->y_cord<<","<<city_record->data<<endl;
                }
                else{
                    quad_node* temp_node = NULL;
                    temp_node = node->NW_node;
                    quad_node* new_node = create_new_quadnode();
                    node->NW_node = new_node;
                    insert(city_record,node->NW_node, x1, y1, x2, y2) ;
                    insert(temp_node->value,node->NW_node,x1, y1, x2, y2);
                }
            }
            else{
                insert(city_record,node->NW_node,x1,y1,x2,y2);
            }
        }
        
        
        
    }
    else if(quadrant == 2){//northeastern quadrant
        x1 = (x1+x2)/2;
        y2 = (y1+y2)/2;
        if(node->NE_node == NULL){
            quad_node*  new_node;
            new_node = create_leaf_node(city_record);
            node->NE_node = new_node;
            result = true;
        }
        else{
            if(node->NE_node->is_leaf == true){
                existing_record = search(city_record->x_cord,city_record->y_cord);
                if(existing_record->data == city_record->data){
                    cout<<"Duplicate error: Record of this city is already there:"<<city_record->x_cord<<","<<city_record->y_cord<<","<<city_record->data<<endl;
                }
                else{
                    quad_node* temp_node = NULL;
                    temp_node = node->NE_node;
                    quad_node* new_node = create_new_quadnode();
                    node->NE_node = new_node;
                    insert(city_record,new_node, x1, y1, x2, y2) ;
                    insert(temp_node->value,new_node,x1, y1, x2, y2);
                }
            }
            else{
                insert(city_record,node->NE_node,x1,y1,x2,y2);
            }
        }
        
        
    }
    else if(quadrant == 3){ //southwestern quadrant
        x2 = (x1+x2)/2;
        y1 = (y1+y2)/2;
        if(node->SW_node == NULL){
            quad_node*  new_node;
            new_node = create_leaf_node(city_record);
            node->SW_node = new_node;
            result = true;
        }
        else{
            if(node->SW_node->is_leaf == true){
                existing_record = search(city_record->x_cord,city_record->y_cord);
                if(existing_record->data == city_record->data){
                    cout<<"Duplicate error: Record of this city is already there:"<<city_record->x_cord<<","<<city_record->y_cord<<","<<city_record->data<<endl;
                }
                else{
                    quad_node* temp_node = NULL;
                    temp_node = node->SW_node;
                    quad_node* new_node = create_new_quadnode();
                    node->SW_node = new_node;
                    insert(city_record,new_node, x1, y1, x2, y2);
                    insert(temp_node->value,new_node,x1, y1, x2, y2);
                }
            }
            else{
                insert(city_record,node->SW_node,x1,y1,x2,y2);
            }
        }
        
    }
    else if(quadrant == 4){ //southeastern quadrant
        x1 = (x1+x2)/2;
        y1 = (y1+y2)/2;
        if(node->SE_node == NULL){
            quad_node*  new_node;
            new_node = create_leaf_node(city_record);
            node->SE_node = new_node;
            result = true;
        }
        else{
            if(node->SE_node->is_leaf == true){
                existing_record = search(city_record->x_cord,city_record->y_cord);
                if(existing_record->data == city_record->data){
                    cout<<"Duplicate error: Record of this city is already there:"<<city_record->x_cord<<","<<city_record->y_cord<<","<<city_record->data<<endl;
                }
                else{
                    quad_node* temp_node = NULL;
                    temp_node = node->SE_node;
                    quad_node* new_node = create_new_quadnode();
                    node->SE_node = new_node;
                    result = insert(city_record,new_node, x1, y1, x2, y2);
                insert(temp_node->value,new_node,x1, y1, x2, y2);
                }
            }
            else{
                insert(city_record,node->SE_node,x1,y1,x2,y2);
            }
        }
    }
    
    return result;
}

//find quadrant from the given input
int Quad::evaluate_quadrant(record* city_record,int x1, int y1, int x2, int y2){
    int xmid = (x1+x2)/2;
    int ymid = (y1+y2)/2;
    if(city_record->x_cord < x1 || city_record->x_cord > x2 || city_record->y_cord < y1 || city_record->y_cord > y2){
        return 5;
    }
    if(city_record->x_cord < xmid && city_record->y_cord < ymid){
        return 1;
    }
    else if(city_record->x_cord > xmid && city_record->y_cord < ymid){
        return 2;
    }
    else if(city_record->x_cord < xmid && city_record->y_cord >ymid){
        return 3;
    }
    else if(city_record->x_cord > xmid && city_record->y_cord > ymid){
        return 4;
    }
    return 5;
}

//create new Internal node
Quad::quad_node* Quad::create_new_quadnode(void){
    quad_node* new_node = new quad_node();
    new_node->NW_node = NULL;
    new_node->NE_node = NULL;
    new_node->SE_node = NULL;
    new_node->SW_node = NULL;
    new_node->value = NULL;
    new_node->is_empty = true;
    new_node->is_leaf = false;
    return new_node;
}


//public method for removing a record
bool Quad::remove(record city_record){
    record *city_record_ptr = new record;
    city_record_ptr->data = city_record.data;
    city_record_ptr->x_cord = city_record.x_cord;
    city_record_ptr->y_cord = city_record.y_cord;
    return(remove(city_record_ptr,root,0,0,16383,16383));
}


//private method for removing a record
bool Quad::remove(record* city_record, quad_node* &node,int x1, int y1, int x2, int y2){
    bool result;
    int x_cord = city_record->x_cord;
    int y_cord = city_record->y_cord;
    string city_name = city_record->data;
    if(node == NULL){
        return false;
    }
    else{
        int quadrant ;
        quadrant = evaluate_quadrant(city_record, x1, y1, x2, y2);
        if(quadrant == 1){
            x2 = (x1+x2)/2;
            y2 = (y1+y2)/2;
            
            if(node->is_leaf == true && node->is_empty == true){
                result = false;
            }
            else if(node->is_leaf == true && node->value->data == city_name &&
                    node->value->x_cord == x_cord && node->value->y_cord == y_cord){
                node->is_empty = true;
                result = true;
            }
            else{
                result= remove(city_record,node->NW_node,x1,y1,x2,y2);
            }
        }
        
        else if(quadrant == 2){
            x1 = (x1+x2)/2;
            y2 = (y1+y2)/2;
            if(node->is_leaf == true && node->is_empty == true){
                result = false;
            }
            else if(node->is_leaf == true && node->value->data == city_name &&
                    node->value->x_cord == x_cord && node->value->y_cord == y_cord){
                node->is_empty = true;
                result = true;
            }
            else{
                result =remove(city_record,node->NE_node,x1,y1,x2,y2);
            }
        }
        
        else if(quadrant== 3){
            x2 = (x1+x2)/2;
            y1 = (y1+y2)/2;
            if(node->is_leaf == true && node->is_empty == true){
                result = false;
            }
            else if(node->is_leaf == true && node->value->data == city_name &&
                    node->value->x_cord == x_cord && node->value->y_cord == y_cord){
                node->is_empty = true;
                result = true;
            }
            else{
                result =remove(city_record,node->SW_node,x1,y1,x2,y2);
            }
        }
        
        else if(quadrant == 4){
            x1 = (x1+x2)/2;
            y1 = (y1+y2)/2;
            if(node->is_leaf == true && node->is_empty == true){
                result = false;
            }
            else if(node->is_leaf == true && node->value->data == city_name &&
                    node->value->x_cord == x_cord && node->value->y_cord == y_cord){
                node->is_empty = true;
                result = true;
            }
            else{
               result=  remove(city_record,node->SE_node,x1,y1,x2,y2);
            }
        }
        
        
    }
    
    return result;
}


//public method for printing quad tree used in Debug
void Quad::print(){
    print(root);
}


//private method for printing quad tree used in Debug
void Quad::print(quad_node* node){
    if(node == NULL){
        cout<<"There are No records to show"<<endl;
        return;
    }
    cout<<"I";
    if(node->NW_node != NULL){
        if(node->NW_node->is_leaf == false){
            print(node->NW_node);
            }
        else{
            if(node->NW_node->is_empty == false){
                cout<<node->NW_node->value->x_cord<<","<<node->NW_node->value->y_cord<<node->NW_node->value->data<<"|";
            }
            else{
            cout<<"E";
            }
        }
    }
    
    if(node->NE_node != NULL){
        if(node->NE_node->is_leaf == false){
            print(node->NE_node);
        }
        else{
            if(node->NE_node->is_empty == false){
                cout<<node->NE_node->value->x_cord<<","<<node->NE_node->value->y_cord<<node->NE_node->value->data<<"|";
            }
            else{
                cout<<"E";
            }
        }
    }
    
    if(node->SW_node != NULL){
        if(node->SW_node->is_leaf == false){
            print(node->SW_node);
        }
        else{
            if(node->SW_node->is_empty == false){
                cout<<node->SW_node->value->x_cord<<","<<node->SW_node->value->y_cord<<node->SW_node->value->data<<"|";
            }
            else{
                cout<<"E";
            }
        }
    }
    
    if(node->SE_node != NULL){
        if(node->SE_node->is_leaf == false){
            print(node->SE_node);
        }
        else{
            if(node->SE_node->is_empty == false){
                cout<<node->SE_node->value->x_cord<<","<<node->SE_node->value->y_cord<<node->SE_node->value->data<<"|";
            }
            else{
                cout<<"E";
            }
        }
    }
    
    
    return;
}





//method to create the leaf node
Quad::quad_node* Quad::create_leaf_node(record* city_record){
    quad_node* node;
    node = new quad_node();
    node->NW_node = NULL;
    node->NE_node = NULL;
    node->SW_node = NULL;
    node->SE_node = NULL;
    node->value = new record();
    node->value = city_record;
    node->is_leaf = true;
    node->is_empty = false;
    return node;
    
}



//public method for search in quad tree with x and y coordinate given
Quad::record* Quad::search(int x, int y){
    return(search(root,x,y,0,0,16383,16383));
}




//private method for the search
Quad::record* Quad::search(quad_node* node, int x, int y,int x1, int y1, int x2, int y2){
    record* city_record = new record;
    city_record->x_cord= x;
    city_record->y_cord = y;
    city_record->data = "";
    if(node == NULL){
        cout<<"There are no records";
    }
    
    else{
        int quadrant ;
        quadrant = evaluate_quadrant(city_record, x1, y1, x2, y2);
        if(quadrant == 1){
            x2 = (x1+x2)/2;
            y2 = (y1+y2)/2;
            
            if(node->is_leaf == true && node->value->x_cord == x && node->value->y_cord == y){
                city_record->data = node->value->data;
            }
            else if(node->is_leaf == false){
                city_record = search(node->NW_node,x ,y ,x1 ,y1 ,x2 ,y2);
            }
            else if(node->is_leaf == true && node->is_empty == true){
                cout<<"Not found"<<endl;
            }
        }
        
        else if(quadrant == 2){
            x1 = (x1+x2)/2;
            y2 = (y1+y2)/2;
            
            if(node->is_leaf == true && node->value->x_cord == x && node->value->y_cord == y){
                city_record->data = node->value->data;
            }
            else if(node->is_leaf == false){
                city_record = search(node->NE_node,x ,y ,x1 ,y1 ,x2 ,y2);
            }
            else if(node->is_leaf == true && node->is_empty == true){
                cout<<"Not found"<<endl;
            }
        }
        
        
       else if(quadrant == 3){
            x2 = (x1+x2)/2;
            y1 = (y1+y2)/2;
            
            if(node->is_leaf == true && node->value->x_cord == x && node->value->y_cord == y){
                city_record->data = node->value->data;
            }
            else if(node->is_leaf == false){
                city_record = search(node->SW_node,x ,y ,x1 ,y1 ,x2 ,y2);
            }
            else if(node->is_leaf == true && node->is_empty == true){
                cout<<"Not found"<<endl;
            }
        }
        
        
        else if(quadrant == 4){
            x1 = (x1+x2)/2;
            y1 = (y1+y2)/2;
            
            if(node->is_leaf == true && node->value->x_cord == x && node->value->y_cord == y){
                city_record->data = node->value->data;
            }
            else if(node->is_leaf == false){
                city_record =search(node->SE_node,x ,y ,x1 ,y1 ,x2 ,y2);
            }
            else if(node->is_leaf == true && node->is_empty == true){
                cout<<"Not found"<<endl;
            }
        }
    }
    
    return city_record;
}



//method for searching records inside a specified circle given the radius and origin cordinates coordinates.
void Quad::search_radius(int x,int y, int radius){
    search_radius(root, x, y, radius);
}
void Quad::search_radius(quad_node* node,int x, int y, int radius){
    if(node == NULL){
        
        return;
    }
    else if(node->is_leaf == true && node->is_empty == false){
        int x_value = node->value->x_cord;
        int y_value = node->value->y_cord;
        if((pow((x_value - x),2)+pow((y_value - y),2)) <= pow(radius,2)){
            cout<<"search inside radius, found city:"<<node->value->data<<","<<node->value->x_cord<<","<<node->value->y_cord<<endl;
        }
    }
    else if(node->is_leaf == false){
    search_radius(node->NW_node, x, y, radius);
    search_radius(node->NE_node, x, y, radius);
    search_radius(node->SW_node, x, y, radius);
    search_radius(node->SE_node, x, y, radius);
    }
}



//method to delete all the nodes from the quad tree
void Quad::makeNull(){
    return(makeNull(root));
}

void Quad::makeNull(quad_node* &node)
{
    if (node == NULL) {
        return;
    }
    makeNull(node->NW_node);
    makeNull(node->NE_node);
    makeNull(node->SW_node);
    makeNull(node->SE_node);
    if (node == root) {
        return;
    }else{
        delete node;
        node = NULL;
    }
}




