// FileOrganizer.h - class specifcation 

#ifndef FILEORGANIZER_H
#define FILEORGANIZER_H

#include <iostream>
#include <string>	
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype> // character classification
#include <sstream> // string stream
#include <set> // set container 
#include <iomanip>
#include <map>

using namespace std;

struct Token
{
	string type; // type of token like keyword, identifier and etc 
	string value; // the text of the token 
};


class FileOrganizer
{
public:
	// constructor
	FileOrganizer();  
	
	// function that allows user to read the file 
	string readFile(const string& filePath);
	
	/*function that removes comments and spaces from the file text 
	  with the given code that is in the text file		
	*/
	string removeCommentsAndSpaces(const string& code);

	void classifyToken(const string& token, vector<Token>& tokens, const set<string>& keywords, const set<char>& operators, const set<char>& delimiters);

	// tokenization method 
	vector<Token> tokenize(const string& code);

	void classifyToken(const string& token, vector<Token>& tokens, const set<string>& keywords, const set<char>& operators, const set<char>& delimiters, const set<string>& multiCharOperators);

	// prints token type and value 
	void printTokens(const vector<Token>& tokens);

	// deconstructor
	~FileOrganizer();

private:
	// protected memeber variables 


};
#endif