#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Parser.h"
#include "Binary_Coder.h"
#include <thread>
#include <map>

void add_symbol_to_table(std::map<std::string, std::string>& symbol_map, std::string symbol, std::string value);
void worker_thread();

int main() {

	// initial thread that blocks the rest of the program from operating until the original file 
	// has been cleared of whitespace/comments/inline comments
	std::thread t(worker_thread);

	// the different files we are interacting with
	std::string first_filename = "Pong.asm";
	std::string second_filename = "tester_parsed.txt";
	std::string third_filename = "post_parsed.txt";
	std::string fourth_filename = "final_program.asm";

	t.join();
	
	//contains our parsed file with zero whitespace/comments
	std::ifstream second_file(second_filename);
	std::string current_line;

	// object used to call methods attached to our binary coder
	Binary_Coder code1;

	// creating predfined symbol table from hack specifications
	std::map<std::string, std::string> symbolTable;
	symbolTable["@R0"] = "0000000000000000";
	symbolTable["@R1"] = "0000000000000001";
	symbolTable["@R2"] = "0000000000000010";
	symbolTable["@R3"] = "0000000000000011";
	symbolTable["@R4"] = "0000000000000100";
	symbolTable["@R5"] = "0000000000000101";
	symbolTable["@R6"] = "0000000000000110";
	symbolTable["@R7"] = "0000000000000111";
	symbolTable["@R8"] = "0000000000001000";
	symbolTable["@R9"] = "0000000000001001";
	symbolTable["@R10"] = "0000000000001010";
	symbolTable["@R11"] = "0000000000001011";
	symbolTable["@R12"] = "0000000000001100";
	symbolTable["@R13"] = "0000000000001101";
	symbolTable["@R14"] = "0000000000001110";
	symbolTable["@R15"] = "0000000000001111";
	symbolTable["@SP"] = "0000000000000000";
	symbolTable["@LCL"] = "0000000000000001";
	symbolTable["@ARG"] = "0000000000000010";
	symbolTable["@THIS"] = "0000000000000011";
	symbolTable["@THAT"] = "0000000000000100";
	symbolTable["@SCREEN"] = "0100000000000000";
	symbolTable["@KBD"] = "0110000000000000"; // @dog = '7'
	
	//handles turning pseudo commands into symbols that point to a memory address.
	if (second_file.is_open()) {
		int i = 0;
		int* ptr1 = &i;
		while (std::getline(second_file, current_line)) {
			(*ptr1)++;
			//if we ever see a parentheses, we add the next lines location by converting our current line number
			// denoted by 'i' into a binary number and attach that to an @ sign to form an A command pointing to it
			if (current_line[0] == '(') {
				(*ptr1)--;
				std::string new_symbol = "@";
				for (int j = 1; j < (current_line.size() - 1); j++) {
					new_symbol += current_line[j];
				}
				//std::cout << "current line number: " << *ptr1 << std::endl;
				int copy_int = *ptr1;
				symbolTable[new_symbol] = code1.to_binary_from_A_command(copy_int);
			}
		}
	}


	// sets our position at newfile back to zero since currently we're at the end of it.
	second_file.seekg(0, std::ios::beg);
	second_file.close();

	for (const auto& pair : symbolTable) {
		std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
	}
	
	Parser hack_parser(second_filename, third_filename);
	hack_parser.translate_symbols_and_skip_pseudocommands(symbolTable);

	std::ifstream third_file(third_filename);
	std::ofstream fourth_file(fourth_filename);

	// make sure both files are open then go line by line through our parsed file
	// each file we pass off the handling of converting assembly to binary to our binary_coder method, determine_command_type_and_compute
	//add new line character after

	if (third_file.is_open() && fourth_file.is_open()) {
		int i = 0;
		while (std::getline(third_file, current_line)) {
			i++;
			fourth_file << code1.determine_command_type_and_compute(current_line, symbolTable); /***/
			fourth_file << "\n";
		}
	}

	third_file.close();
	fourth_file.close();
	return 0;
}



void add_symbol_to_table(std::map<std::string, std::string> &symbol_map, std::string symbol, std::string value) {
	symbol_map[symbol] = value;
}

//just a thread that uses the methods attached to our parser object
// to update a file with the name equal to the second_filename with a parsed of whitespace/comments version of the original file
void worker_thread() {

	std::string first_filename = "Pong.asm";
	std::string second_filename = "tester_parsed.txt";
	Parser hack_parser(first_filename, second_filename);
	hack_parser.parse_file();
}
