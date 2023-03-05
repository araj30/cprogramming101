 /*************************************************************************
 * Anya Rajan, arajan2
 * 2022 Spring CSE101 PA7
 * Order.cpp
 * Order.cpp is the client file for the Dictionary ADT
 * *************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<iomanip>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {
   // pseudo from tantalo
   int line_count;
   size_t begin, end, line_length;
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;
	
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   Dictionary D;
   // read each line of input file, then count and print tokens 
   line_count = 0;
   int count = 0;
   while( getline(in, line) )  {
      line_count++;
      line_length = line.length();
      
      // get tokens in this line
      // token_count = 0;
      tokenBuffer = "";

      // get first token
      begin = min(line.find_first_not_of(" ", 0), line_length);
      end = min(line.find_first_of(" ", begin), line_length);
      token = line.substr(begin, end-begin);
      
      while( token!="" ){  // we have a token
         // update token buffer
         tokenBuffer += "   "+token;
         // token_count++;

         // get next token
         begin = min(line.find_first_not_of(" ", end+1), line_length);
         end = min(line.find_first_of(" ", begin), line_length);
         token = line.substr(begin, end-begin);
      }

     	D.setValue(tokenBuffer, count + 1); 
   	count++;
    }

   out << D.to_string() << endl << endl;
   out << D.pre_string() << endl;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);		
   
}
