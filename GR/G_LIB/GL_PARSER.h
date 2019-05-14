#ifndef GL_PARSER_H_INCLUDED
#define GL_PARSER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h>

//rev 3

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
  int c = snprintf ( dat, 10, "%s%f", idt, data );
  out<<dat<<" ";
 }
     else{out<<a<<" ";}
}
if(!exist){
int c = snprintf ( dat, 10, "%s%f", idt, data );
  out<<dat<<" ";
}
const std::string tmp = out.str();
return tmp.c_str();

}

#endif // AXGL_H_INCLUDED
