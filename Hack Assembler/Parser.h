#ifndef PARSER
#define PARSER

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <map>


//parser creates a parser object, it takes an original file name and a new file name which are used to open and close files
class Parser{
private:
	std::string orig_file_name;
	std::string new_file_name;
public:
	Parser(std::string fname, std::string nfname);

	// by checking if the line is whitespace or comments, we first create a new file with just commands/pseudo commands
	bool not_whitespace(std::string curr_line);

	bool is_A_command(std::string command_line);
	std::string delete_inline_comments(std::string curr_line);
	void parse_file();
	void translate_symbols_and_skip_pseudocommands(std::map<std::string, std::string> table);
	
	// is_C_command, Is Label/Variable
};


#endif
