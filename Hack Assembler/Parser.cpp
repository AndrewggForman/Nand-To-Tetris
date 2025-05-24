#include "Parser.h"
#include "Binary_Coder.h"

Parser::Parser(std::string fname, std::string nfname) {
	orig_file_name = fname;
	new_file_name = nfname;
}

// everyline should begin with something that isn't empty or a comment, if not it's whitespace and shouldn't be included
bool Parser::not_whitespace(std::string curr_line) {
	return (curr_line[0] != '/' && (!curr_line.empty()));
}

//
bool Parser::is_A_command(std::string command_line) {
	return(command_line[0] == '@');
}

//go through a line until we hit an inline comment signifier '/', return from beginning to before inline comment 
std::string Parser::delete_inline_comments(std::string curr_line) {
	int line_length = curr_line.length();
	std::string fixed_line = "";
	for (int i = 0; i < line_length; i++) {
		if (curr_line[i] == '/') {
			i = line_length;
		}
		else {
			fixed_line += curr_line[i];
		}
	}
	return fixed_line;
}

//	if a line ISN'T whitespace, then add the line to the file AFTER deleting inline comments,
// then flush input and go to next line using 'std::endl'
void Parser::parse_file() {
	std::ifstream orig_file(orig_file_name);
	std::ofstream new_file(new_file_name);
	std::string current_line;

	if (orig_file.is_open() && new_file.is_open()) {
		while (std::getline(orig_file, current_line)) {
			if (not_whitespace(current_line)) {
				new_file << delete_inline_comments(current_line) << std::endl;
			}
		}
	}

	orig_file.close();
	new_file.close();
}

void Parser::translate_symbols_and_skip_pseudocommands(std::map<std::string, std::string> table) {
	std::ifstream orig_file(orig_file_name);
	std::ofstream new_file(new_file_name);
	std::string current_line;

	if (orig_file.is_open() && new_file.is_open()) {
		while (std::getline(orig_file, current_line)) {
			if (current_line[0] == '(') {
				continue;
			}
			else {
				new_file << current_line << std::endl;
			}
		}
	}


	orig_file.close();
	new_file.close();
}