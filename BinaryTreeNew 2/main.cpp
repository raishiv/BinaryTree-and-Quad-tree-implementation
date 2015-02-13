

//

//  main.cpp

//  BinaryTreeNew

//

//  Created by Shiv chandra Kumar on 11/8/14.

//  Copyright (c) 2014 Shiv chandra Kumar. All rights reserved.

//

#include "quadTree.h"

#include "Bst.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;
//create instance of binary search tree and quad tree;
Bst* bst = new Bst();
Quad* quad = new Quad();

//get command one by one and execute it.
void dealing(vector<string> input)
{
    
    string word = input[0];
    Quad::record quad_record;
    Bst::record bst_record;
    
    
    //insert node into two trees
    if (word == "insert")
    {
        
        int x = atoi(input[1].c_str());
        int y = atoi(input[2].c_str());
        string name = input[3];
        if(x >=0 && y >=0 && x <= 16383 && y<= 16383){
        quad_record.data = name;
        quad_record.x_cord = x;
        quad_record.y_cord = y;
        bst_record.x_cord = x;
        bst_record.y_cord = y;
        bst_record.data = name;
        quad->insert(quad_record);
        bst->insert(bst_record);
        
        }
        else{
            cout<<"Error:can not enter this value,"<<x<<","<<y<<endl;
            //can not enter negative and out of bound values
        }
        
    }
    if(word == "debug"){
        //bst->print_tree();
        quad->print();//print quad tree in preorder traversal
    }
    
    //search record of city from Binary search tree
    if (word == "find")
    {
        string name = input[1];
        bst->search(name);
    }
    
    //remove records from the tree
    //if "remove cityname" is the command then remove the city record from binary search tree
    // and get coordinates of the city and then selete it from the quad tree as well.
    if(word == "remove"){
        if(input.size()== 2){

            Bst::record bst_record1 ;
            bst_record1.data = input[1];
            bst_record1.x_cord = 0;
            bst_record1.y_cord = 0;
            int x_coordinate;
            int y_coordinate;
            bst->remove_data(bst_record1,x_coordinate,y_coordinate);
            Quad::record quad_record1;
            quad_record1.data = input[1];
            quad_record1.x_cord = x_coordinate;
            quad_record1.y_cord = y_coordinate;
            quad->remove(quad_record1);
        }
        else if(input.size() ==3){
            
            
            Quad::record* quad_record1;
            int x = atoi(input[1].c_str());
            int y = atoi(input[2].c_str());
            if(x>=0 && y >=0){
                quad_record1 = quad->search(x,y);
                Quad::record quad_record2;
                string city = quad_record1->data;
                quad_record2.data = quad_record1->data;
                quad_record2.x_cord = quad_record1->x_cord;
                quad_record2.y_cord = quad_record1->y_cord;
                quad->remove(quad_record2);
                int x_cord;
                int y_cord;
                
                Bst::record bst_record2;
                bst_record2.data = city;
                bst_record2.x_cord = x;
                bst_record2.y_cord = y;
                bst->remove_data(bst_record2, x_cord, y_cord);
            }
            else{
                cout<<"error:invalid coordinates for search."<<"x:"<<x<<"y:"<<y<<endl;
            }
            
            
            
            
        }
    }
    
    //search in a binary search tree and print the record
    if(word == "search"){
        int x = atoi(input[1].c_str());
        int y = atoi(input[2].c_str());
        int r = atoi(input[3].c_str());
        if(x>=0 && y >= 0 && x <= 16383 && y <= 16383 && r >= 0){
            quad->search_radius(x, y, r);
        }
        else{
            cout<<"error:incorrect values for search:"<<x<<","<<y<<","<<r<<endl;
        }

    }
    if(word == "makenull"){
        bst->makeNull();
        quad->makeNull();
    }
    
}


int main(int argc, const char * argv[]) {
    
    
    
    string input;
    vector<string> commandLine;
    ifstream commandfile;
    commandfile.open(argv[1]);
    while (getline(commandfile, input))
    {
        istringstream istr(input);
        while( !istr.eof() )
        {
            string tmp_s;
            istr >> tmp_s;
            commandLine.push_back(tmp_s);
        }
        dealing(commandLine);//take one line command at a time and run it
        commandLine.clear();//clear the vector before getting next command
    }
    
}
