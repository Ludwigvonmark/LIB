//GCODE LIB
#ifndef GCL_H_INCLUDED
#define GCL_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include "AXMATH.h"

///REV 4
float GETGDS  (std::string id,std::string input )     {
    
    std::istringstream in(input);
    std::string item;
    
    float data;

for (int i=0;in;i++){
in>>item;
    if(item[0]==id[0]){
        item.erase(item.begin());
        std::istringstream(item)>>data;
        
    }

}
return data;

}

int GETGDSI  (std::string id,std::string input )     {
    
    std::istringstream in(input);
    std::string item;
    
    int data;

for (int i=0;in;i++){
in>>item;
    if(item[0]==id[0]){
        item.erase(item.begin());
        std::istringstream(item)>>data;
        
    }

}
return data;
}

float GETGDR  (std::string id,std::string input,float cur )     {
    
        std::istringstream in(input);
    std::string item;
    
    float data=cur;

for (int i=0;in;i++){
in>>item;
    if(item[0]==id[0]){
        item.erase(item.begin());
        std::istringstream(item)>>data;
        
    }

}
return data;
    
}

int GETGDR  (std::string id,std::string input,int cur )     {
    
        std::istringstream in(input);
    std::string item;
    
    int data=cur;

for (int i=0;in;i++){
in>>item;
    if(item[0]==id[0]){
        item.erase(item.begin());
        std::istringstream (item)>>data;
        
    }

}
return data;
    
}

bool GETC  (std::string cmd, std::string input )  {
    
bool out=false;
    
std::istringstream in(input);

std::string item;

for (int i=0;in;i++){
in>>item;

//debug
//std::cout<<"in:"<<item<<std::endl;
//debug

if(item==cmd){
    out=true;
    break;
}
    
    
}
return out;
    
}

std::string ADDGDS (std::string current,std::string id,float data){
    
bool old=false;

std::ostringstream out;

std::istringstream in(current);

//debug
//std::cout<<"AXGL_IN:"<<in.str()<<std::endl;
//debug

std::string item;

for (int i=0;in;i++){
in>>item;

//debug
//std::cout<<"in:"<<item<<std::endl;
//debug

if(item[0]==id[0]){
old =true;
out<<" "<<id<<data;
}
else{  out<<" "<<item;  }

item.clear();

}

if(!old){
out<<" "<<id<<data;}

out<<" \0";

//debug
//std::cout<<"AXGL_OUT:"<<out.str()<<std::endl;
//debug

return out.str(); 
    
}

std::string ADDGDS (std::string current,std::string id,int data){
    
bool old=false;

std::ostringstream out;

std::istringstream in(current);

//debug
//std::cout<<"AXGL_IN:"<<in.str()<<std::endl;
//debug

std::string item;

for (int i=0;in;i++){
in>>item;

//debug
//std::cout<<"in:"<<item<<std::endl;
//debug

if(item[0]==id[0]){
old =true;
out<<" "<<id<<data;
}
else{  out<<" "<<item;  }

item.clear();

}

if(!old){
out<<" "<<id<<data;}

out<<" \0";

//debug
//std::cout<<"AXGL_OUT:"<<out.str()<<std::endl;
//debug

return out.str(); 
    
}

///REV 4





//rev 3 LEGACY

char dat[10];
char idt[1];

float GETGDS  (std::string id,char* in )     {
float result;

std::stringstream inst;
inst<<in;
while (inst){
std::string a;
inst>>a;
     if (a.compare(0,1,id) == 0){
     a.erase(0,1);
     strcpy(dat, a.c_str());
         result=strtod (dat,0);

         return result; }
}}

float GETGDR  (std::string id,char* in,float cur )     {

float result;
std::stringstream inst;
inst<<in;
while (inst){
std::string a;
inst>>a;
     if (a.compare(0,1,id) == 0){
     a.erase(0,1);
     strcpy(dat, a.c_str());
result=strtod (dat,0);

         return result; }
}return cur;}


bool GETC  (std::string cmd,char* in )  {
std::stringstream inst;
inst<<in;
while (inst){
std::string a;
inst>>a;
     if (a.compare(cmd) == 0)return true;
    else return false;
}}



const char *ADDGDS (char* current,std::string id,float data){

///OLD ADDGS
char datt[10];
strcpy(idt, id.c_str());
bool exist=false;
std::stringstream in;
in<<current;
std::stringstream out;
while (in){
std::string a;
in>>a;
     if (a.compare(0,1,id) == 0){
     exist=true;
     a.clear();
  int c = snprintf ( datt, 10, "%s%f", idt, data );
  out<<datt<<" ";
 }
     else{out<<a<<" ";}
}
if(!exist){
int c = snprintf ( datt, 10, "%s%f", idt, data );
  out<<datt<<" ";
}
const std::string tmp = out.str();
return tmp.c_str();
///OLD ADDGS

}
//rev 3 LEGACY





#endif // AXGL_H_INCLUDED
