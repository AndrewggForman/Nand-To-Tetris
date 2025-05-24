#ifndef BINARY_CODER
#define BINARY_CODER
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <map>

class Binary_Coder {
	private:
		int variable_symbol_register = 16;
	public:
		std::string to_binary_from_A_command(int &num1);
		std::string determine_command_type_and_compute(std::string curr_line, std::map<std::string, std::string>& table);
		int from_A_to_integer(std::string curr_num, std::map<std::string, std::string>& table);
		std::string to_binary_from_C_command(std::string c_command);
		std::string handle_destination(std::string command);
		std::string compare_dest_code(std::string command);
		std::string compare_jump_code(std::string command);
		std::string handle_jump(std::string command);
		std::string handle_control(std::string command);
		std::string compare_control_code(std::string command);
		//int update_symbol_table(int memory_index, std::string symbol_name, std::map<std::string, std::string>& table);

};


#endif