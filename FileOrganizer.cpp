// FileOrganizer.cpp

#include "FileOrganizer.h"

FileOrganizer::FileOrganizer() {} // constructor implementation (if needed)

string FileOrganizer::readFile(const string& filePath)
{
	ifstream file(filePath);
	if (!file.is_open())
	{
		cout << "Unable to open file: " << filePath << endl;

		return " "; // returns an empty string if it fails 
	}

	stringstream buffer;
	buffer << file.rdbuf(); // reads the entire text from the file.txt into buffer
	file.close(); // closes the file once it is done 
	
	return buffer.str(); // comverts the buffer contents into a string and returns it 

}

string FileOrganizer::removeCommentsAndSpaces(const string& code)
{
	stringstream ss(code); // creates a stringstream from the input code
	string line, result; // store each line from the stringstream
	bool inMultiLineComment = false;

	while (getline(ss, line))
	{
		// handles multi line comments like /* and */
		size_t startMultiLineComment = line.find("/*");
		size_t endMultiLineComment = line.find("*/");

		if (inMultiLineComment)
		{
			if (endMultiLineComment != string::npos)
			{
				line = line.substr(endMultiLineComment + 2);
				inMultiLineComment = false;
			}
			else
			{
				continue; // skips the entire line as it's within comment block
			}
		}
		else if (startMultiLineComment != string::npos)
		{
			line = line.substr(0, startMultiLineComment);
			if (endMultiLineComment == string::npos)
			{
				inMultiLineComment = true;
			}
		}


		// removes single line comments 
		size_t commentPosition = line.find('//');
		// makes sure if the line starts with '//' indicating a comment"
		if (commentPosition != string::npos)
		{
			// if a comment starts at the start of the line skip the entire line
			if (commentPosition == 0)
			{
				continue;
			}

			// if the comment is in between remove it 
			line.erase(commentPosition);

		}
	

		// removes the leading and trailing spaces from the code
		size_t start = line.find_first_not_of(" \t");
		size_t end = line.find_last_not_of(" \t");

		if (start != string::npos && end != string::npos)
		{
			line = line.substr(start, end - start + 1);
		}
		else if (start != string::npos)
		{
			line = line.substr(start);
		}

		// adds the line if it's not empty 
		if (!line.empty())
		{
			result += line + '\n';
		}
	}

	return result; // returns code from file.txt without the comments and extra spaces 
}

// Tokenize function Processes the given code string and tokenizes it into different categories
vector<Token> FileOrganizer::tokenize(const string& code)
{
	vector<Token> tokens;
	istringstream codeStream(code);
	string word;

	set<string> keywords = { "int", "return", "using", "namespace", "for" };
	set<string> multiCharOperators = { "<<", ">>" }; // Added multi-character operators
	set<char> operators = { '+', '=', '<', '>' };
	set<char> delimiters = { ';', ',', '(', ')', '{', '}' };

	char currentChar;
	string currentToken;
	bool isStringLiteral = false;

	while (codeStream.get(currentChar)) {
		if (isspace(currentChar) && !isStringLiteral) {
			if (!currentToken.empty()) {
				classifyToken(currentToken, tokens, keywords, operators, delimiters, multiCharOperators);
				currentToken.clear();
			}
			continue;
		}

		if (currentChar == '\"') {
			isStringLiteral = !isStringLiteral;
			currentToken += currentChar;
			continue;
		}

		if (!isStringLiteral) {
			if (operators.find(currentChar) != operators.end() || delimiters.find(currentChar) != delimiters.end()) {
				if (!currentToken.empty()) {
					classifyToken(currentToken, tokens, keywords, operators, delimiters, multiCharOperators);
					currentToken.clear();
				}
				currentToken += currentChar;
				// Check for multi-character operators
				if (currentChar == '<' || currentChar == '>') {
					if (codeStream.peek() == currentChar) {
						currentToken += currentChar;
						codeStream.get(); // Consume the next character
					}
				}
				classifyToken(currentToken, tokens, keywords, operators, delimiters, multiCharOperators);
				currentToken.clear();
				continue;
			}
		}

		currentToken += currentChar;
	}

	if (!currentToken.empty()) {
		classifyToken(currentToken, tokens, keywords, operators, delimiters, multiCharOperators);
	}

	return tokens;
}


void FileOrganizer::classifyToken(const string& token, vector<Token>& tokens, const set<string>& keywords, const set<char>& operators, const set<char>& delimiters, const set<string>& multiCharOperators) {
	if (keywords.find(token) != keywords.end()) {
		tokens.push_back({ "Keywords", token });
	}
	else if (multiCharOperators.find(token) != multiCharOperators.end()) {
		tokens.push_back({ "Operators", token });
	}
	else if (operators.find(token[0]) != operators.end()) {
		tokens.push_back({ "Operators", token });
	}
	else if (delimiters.find(token[0]) != delimiters.end()) {
		tokens.push_back({ "Delimiters", token });
	}
	else if (isdigit(token[0]) || (token.size() > 1 && token[1] == '.' && isdigit(token[0]))) {
		tokens.push_back({ "Literals", token });
	}
	else {
		tokens.push_back({ "Identifiers", token });
	}
}

// prints out the tokens and identifies the 
void FileOrganizer::printTokens(const vector<Token>& tokens)
{
	cout << left << setw(15) << "Category" << "Tokens" << endl;
	cout << string(30, '-') << endl; // a line seprator

	for (const auto& token : tokens)
	{
		cout << left << setw(15) << token.type << token.value << endl;
	}
}


FileOrganizer::~FileOrganizer() {} // destructo
