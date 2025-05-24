#include "Binary_Coder.h"

std::string Binary_Coder::to_binary_from_A_command(int &num1) {
	std::string curr_binary_line = "";

	for (int i = 15; i >= 0; i--) {
		if (std::pow(2, i) > num1 || num1 == 0) {
			curr_binary_line += '0';
		}
		else {
			curr_binary_line += '1';
			num1 -= pow(2, i);
		}
	}
	return curr_binary_line;
}

std::string Binary_Coder::determine_command_type_and_compute(std::string curr_line,
	std::map<std::string, std::string>& table) {
	//std::cout << "curr_line: " << curr_line << std::endl;
	if (table.count(curr_line) > 0) {
		return table[curr_line];
	}
	else if (curr_line[0] == '@') {
		int integer = from_A_to_integer(curr_line, table);
		return to_binary_from_A_command(integer);
	}
	else {
		return to_binary_from_C_command(curr_line);
	}
}

int Binary_Coder::from_A_to_integer(std::string curr_num, std::map<std::string, std::string>& table) {
	std::string just_nums = "";
	for (int i = 1; i < curr_num.length(); i++) {
		just_nums += curr_num[i];
	}

	int new_int;
	try {
		new_int = std::stoi(just_nums);
	}
	catch (const std::invalid_argument& error) {
		std::cerr << "Invalid argument: " << error.what() << std::endl;
		std::string symbol_proper_name = "@";
		symbol_proper_name += just_nums;

		if (table.count(symbol_proper_name) < 1) {
			std::string rebuilt_A_command = std::to_string(variable_symbol_register);
			std::string binary_right_side = "";
			int half_step = variable_symbol_register;

			for (int i = 15; i >= 0; i--) {
				if (std::pow(2, i) > half_step || half_step == 0) {
					binary_right_side += '0';
				}
				else {
					binary_right_side += '1';
					half_step -= pow(2, i);
				}
			}

			table[symbol_proper_name] = binary_right_side;

			new_int = variable_symbol_register;
			variable_symbol_register++;
		}
		else {
			std::string rebuilt_meme = "";
			std::string full_meme = table[symbol_proper_name];
			new_int = std::stoi(full_meme);
		}
	}
	catch (const std::out_of_range& error) {
		std::cerr << "Out of range: " << error.what() << std::endl;
	}

	//std::cout << "curr_num: " << curr_num << std::endl;

	return new_int;
}

//int Binary_Coder::update_symbol_table(int memory_index, std::string symbol_name, std::map<std::string, std::string>& table) {
//	table[symbol_name] = memory_index;
//}

//function
// take separate table from other, 
// whenever we hit this error, check if in table
//if in table, return that number, if not, store in table, and incremenet register to 

std::string Binary_Coder::to_binary_from_C_command(std::string c_command) {
	std::string binary_command = "111";
	std::string dest_codes = handle_destination(c_command);
	std::string jump_codes = handle_jump(c_command);
	std::string control_codes = handle_control(c_command);
	binary_command = binary_command + control_codes + dest_codes + jump_codes;
	return binary_command;
}

std::string Binary_Coder::handle_destination(std::string command) {
	std::string dest_part = "";
	std::string left_side = "";
	char curr_char = command[0];
	if (command.find('=') != std::string::npos ) {
		int i = 0;
		while (command[i] != '=') {
			left_side +=command[i];
			i++;
		}
		
		dest_part = compare_dest_code(left_side);

	}
	else {
		dest_part = "000";
	}
	return dest_part;
}

std::string Binary_Coder::compare_dest_code(std::string command) {
	if (command == "M") {
		return "001";
	} 
	else if (command == "D") {
		return "010";
	}
	else if (command == "MD" || command == "DM") {
		return "011";
	}
	else if (command == "A") {
		return "100";
	}
	else if (command == "AM" || command == "MA") {
		return "101";
	}
	else if (command == "AD" || command == "DA") {
		return "110";
	}
	else if (command == "AMD") {
		return "111";
	}
	else {
		return "Error";
	}
}

std::string Binary_Coder::compare_jump_code(std::string command) {
	if (command == "JGT") {
		return "001";
	}
	else if (command == "JEQ") {
		return "010";
	}
	else if (command == "JGE" || command == "DM") {
		return "011";
	}
	else if (command == "JLT") {
		return "100";
	}
	else if (command == "JNE") {
		return "101";
	}
	else if (command == "JLE") {
		return "110";
	}
	else if (command == "JMP") {
		return "111";
	}
	else {
		return "Error";
	}
}

std::string Binary_Coder::compare_control_code(std::string command) {
	if (command == "0") {
		return "0101010";
	}
	else if (command == "1") {
		return "0111111";
	}
	else if (command == "-1") {
		return "0111010";
	}
	else if (command == "D") {
		return "0001100";
	}
	else if (command == "A") {
		return "0110000";
	}
	else if (command == "!D") {
		return "0001101";
	}
	else if (command == "!A") {
		return "0110001";
	}
	else if (command == "-D") {
		return "0001111";
	}
	else if (command == "-A") {
		return "0110011";
	}
	else if (command == "D+1") {
		return "0011111";
	}
	else if (command == "A+1") {
		return "0110111";
	}
	else if (command == "D-1") {
		return "0001110";
	}
	else if (command == "A-1") {
		return "0110010";
	}
	else if (command == "D+A") {
		return "0000010";
	}
	else if (command == "D-A") {
		return "0010011";
	}
	else if (command == "A-D") {
		return "0000111";
	}
	else if (command == "D&A") {
		return "0000000";
	}
	else if (command == "D|A") {
		return "0010101";
	}
	else if (command == "M") {
		return "1110000";
	}
	else if (command == "!M") {
		return "1110001";
	}
	else if (command == "-M") {
		return "1110011";
	}
	else if (command == "M+1") {
		return "1110111";
	}
	else if (command == "M-1") {
		return "1110010";
	}
	else if (command == "D+M") {
		return "1000010";
	}
	else if (command == "D-M") {
		return "1010011";
	}
	else if (command == "M-D") {
		return "1000111";
	}
	else if (command == "D&M") {
		return "1000000";
	}
	else if (command == "D|M") {
		return "1010101";
	}
	else {
		return "Error";
	}
}

std::string Binary_Coder::handle_jump(std::string command) {
	std::string jump_part = "";
	std::string right_side = "";
	char curr_char = command[0];
	int semicolon_index;
	if (command.find(';') != std::string::npos) {
		semicolon_index = command.find(';');
		semicolon_index++;
		while (semicolon_index < command.size() && command[semicolon_index] != '\\' && command[semicolon_index] != ' ') {
			right_side += command[semicolon_index];
			semicolon_index++;
		}

		jump_part = compare_jump_code(right_side);
	}
	else {
		jump_part = "000";
	}
	return jump_part;
}

std::string Binary_Coder::handle_control(std::string command) {
	std::string control_part = "";
	std::string middle_part = "";
	int i = 0;

	// assuming we know there is no equal sign because destination is null, we just go up until semicolon/end of line to grab code
	if (compare_dest_code(command) == "000") {
		while (command[i] != ';' && command[i] != '\\' && i < command.size()) {
			middle_part += command[i];
			i++;
		}
		control_part = compare_control_code(middle_part);
		return control_part;
	}

	// ************ add some error handling?
	else {
		int i = command.find('=');
		i++;
		while (command[i] != ';' && command[i] != '\\' && i < command.size()) {
			middle_part += command[i];
			i++;
		}
		control_part = compare_control_code(middle_part);
		return control_part;
	}
	
}