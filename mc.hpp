#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include "zalg.cpp"
//using namespace std;

/*  set_save_category
 *  Description:    given the keyword and its category, fsave to total category.
 *  Input(s):       kw          -   keyword for searching
 *                  category    -   name of the categoty
 *                  status      -   0 if no force overload, 1 otherwise
 *  Output(s):      None
 *  Sideeffect(s):  None
 **/
// global variable searchMap
std::map<std::string, std::string> searchMap;
void set_save_category(std::string kw, std::string category, int status){
    if(searchMap.find(category) != searchMap.end()){
        if(status == 0){
            // kw already exists, set failed.
            return;
        }
        else{
            // force overlap, force set.
            searchMap.at(category) = kw;
            return;
        }
    }
    searchMap.insert(std::pair<std::string, std::string>(category, kw));
    return;
}
//-----------------------------------------------------------------------------------

bool find_by_kw(std::string cur_line, std::string kw){
    std::string P = kw;
    std::string T = cur_line;

    std::vector<int> outList = zalg_search(P, T);

    if(*(outList.begin()) == -1)    return false;
    else    return true;
}
 
void find_file(std::string filename){
    // Convert string to char* and Open the file
    int l1 = filename.length();
    char fileName[l1 + 1];
    strcpy(fileName, filename.c_str());

    // convert string to char* and Create Output file
    std::string newname = filename.append("_find.txt");
    int l2 = newname.length();
    char newName[l2 + 1];
    strcpy(newName, newname.c_str());
    FILE *op = fopen(newName, "w");
    
    
    // For each kw,
    std::map<std::string, std::string>::iterator it;
    int counter = 1;
    for(it = searchMap.begin(); it != searchMap.end(); ++it){
        // write a title for each category/kw
        std::string title = std::to_string(counter) + ". 以下是分类为" + (*it).first + "的基于" + (*it).second + "的弹幕:\n";
        int l3 = title.length();
        char Title[l3 + 1];
        strcpy(Title, title.c_str());
        fputs(Title, op);
        counter++;
        
        // open input file
        FILE *fp = fopen(fileName, "r");

        char cur_char = 'a';
        std::string cur_kw = (*it).second;

        while(cur_char != EOF){
            // for the whole input file
            std::string cur_line = "";
            // get current line
            while(cur_char != EOF){
                cur_char = getc(fp);
                if(cur_char == EOF) break;
                cur_line.append(1, cur_char);
                // continue append until cur line is fully captured
                if(cur_char == '\n'){
                    break;
                }  
            }
            if(cur_char == EOF) break;
            // start searching for current kw
            if(find_by_kw(cur_line, cur_kw)){
                cur_line = "        " + cur_line;
                int l4 = cur_line.length();
                char curLine[l4 + 1];
                strcpy(curLine, cur_line.c_str());
                fputs(curLine, op);
            }
        }
        // jump to top of the file to search again
        fclose(fp);
        //fseek(fp, 0, SEEK_SET);
    }
    // Close the file
    fclose(op);
    return;
}