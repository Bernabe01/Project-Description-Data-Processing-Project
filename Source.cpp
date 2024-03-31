#include "FileOrganizer.h"

int main()
{
	FileOrganizer fileOrganizer;

	string filePath = "file.txt"; 	// should be able to access and read file path change file name to file you are using
	string fileContent = fileOrganizer.readFile(filePath); // reads the contents of the file

	if (!fileContent.empty()) // checks if the file contentn is readable 
	{
		cout << "Original File content:\n" << fileContent << "\n\n";

		// removes the comments and ewxcess spaces from the text file
		string cleanedContent = fileOrganizer.removeCommentsAndSpaces(fileContent);
		
		cout << "Code after removing excess space and comments:\n\n" << cleanedContent << endl;

		// tokenizing the cleaned content 
		vector<Token> tokens = fileOrganizer.tokenize(cleanedContent);

		// print out tokens
		cout << "\nOutput2 - Tokenized code in tabular form:\n";
		fileOrganizer.printTokens(tokens);
		

	}
	else
	{
		// if the file has not contents in it or can't be read
		cout << "File is empty or can't be read. " << endl;
	}



	return 0;
}
