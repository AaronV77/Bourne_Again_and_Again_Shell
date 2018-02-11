#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> LoadVector();
void First_Loop(std::vector<std::string> incoming_commands, std::vector<std::string>ThursdayCommands, std::string incoming_input);
void Normal_Loop(std::vector<std::string>incoming_commands, std::vector<std::string>ThursdayCommands);
void Operator_Loop(std::vector<std::string>incoming_commands);

int main() {
    std::string incoming_input = "";

    std::vector<std::string> ThursdayCommands = LoadVector();
    std::vector<std::string> incoming_commands;

    while(1) {
        std::cout << "Please enter: ";
        std::getline(std::cin, incoming_input);

        if (incoming_input == "exit")
            return 0;

        First_Loop(incoming_commands, ThursdayCommands, incoming_input);

    }

    return 0;
}

std::vector<std::string> LoadVector() {
    std::vector<std::string> myVector;

    myVector.push_back("back");
    myVector.push_back(" bash");
    myVector.push_back("cd");
    myVector.push_back("color");
    myVector.push_back("commands");
    myVector.push_back("compress");
    myVector.push_back("cp");
    myVector.push_back("date");
    myVector.push_back("debug");
    myVector.push_back("decompress");
    myVector.push_back("decrypt");
    myVector.push_back("disable");
    myVector.push_back("enable");
    myVector.push_back("encrypt");
    myVector.push_back("exit");
    myVector.push_back("find");
    myVector.push_back("getenv");
    myVector.push_back("hd");
    myVector.push_back("help");
    myVector.push_back("info");
    myVector.push_back("ls");
    myVector.push_back("mv");
    myVector.push_back("pid");
    myVector.push_back("ppid");
    myVector.push_back("printenv");
    myVector.push_back("prompt");
    myVector.push_back("rm");
    myVector.push_back("search");
    myVector.push_back("setenv");
    myVector.push_back("time");
    myVector.push_back("uid");
    myVector.push_back("unsetenv");
    myVector.push_back("usage");
    myVector.push_back("wd");
    
    return myVector;
}

void First_Loop(std::vector<std::string> incoming_commands, std::vector<std::string>ThursdayCommands, std::string incoming_input) {
    std::string token = "";
    std::string special_symbol_container = "";
    bool error_flag = false;
    bool ampersand_flag = false;
    bool next_operator_find_flag = false;
    bool single_quote_flag = false;
    bool double_quote_flag = false;
    bool bracket_char_flag = false;
    bool parentheses_char_flag = false;
    bool curly_brace_char_flag = false;
    bool skip_this_char = false;
    bool operator_found_flag = false;
    bool waitpid_flag = false;
    int which_command_parser = 0;
    int argument_position = 0;

    // This loop just gets rid of all spaces and tokens the incoming input.
    // This loop also makes sure there is a correct number of quotes (single and double).
    // This loop is also make sure that there are not more than one operator next to each other without a space and with a space.
    // I do this by setting a flag when an operator is found, and set another operator when a space is found.
    // If the next character after that space is another opeator then there is an error else there is not.
    // Then shoves them into a vector and returns the vector.

    for (int a = 0; a < incoming_input.size(); ++a) {

        if (parentheses_char_flag == false && curly_brace_char_flag == false && bracket_char_flag == false && double_quote_flag == false) {
            if (incoming_input[a] == 39) {
                if (single_quote_flag == false) {
                    single_quote_flag = true;
                    skip_this_char = true;
                    special_symbol_container += incoming_input[a];
                } else {
                    single_quote_flag = false;
                    skip_this_char = true;
                    special_symbol_container += incoming_input[a];
                    incoming_commands.push_back(special_symbol_container);
                    special_symbol_container = "";
                }
            }
        }
        if (single_quote_flag == false && parentheses_char_flag == false && curly_brace_char_flag == false && bracket_char_flag == false) {
            if (incoming_input[a] == '"') {
                if (double_quote_flag == false) {
                    double_quote_flag = true;
                    skip_this_char = true;
                    special_symbol_container += incoming_input[a];
                } else {
                    double_quote_flag = false;
                    skip_this_char = true;
                    special_symbol_container += incoming_input[a];
                    incoming_commands.push_back(special_symbol_container);
                    special_symbol_container = "";
                }
            }
        }
        if (single_quote_flag == false && double_quote_flag == false && curly_brace_char_flag == false && bracket_char_flag == false) {
           if (incoming_input[a] == '(' || incoming_input[a] == ')') {
                if (incoming_input[a] == '(') {
                    if (parentheses_char_flag == false) {
                        parentheses_char_flag = true;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                    } else {
                        std::cout << "There is a parentheses char error." << std::endl;
                        error_flag = true;
                        break;
                    }
                } else if (incoming_input[a] == ')') {
                    if (parentheses_char_flag == true) {
                        parentheses_char_flag = false;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                        incoming_commands.push_back(special_symbol_container);
                        special_symbol_container = "";
                    } else {
                        std::cout << "There is a parentheses char error." << std::endl;
                        error_flag = true;
                        break;
                    }
                }
            }
        }
        if (single_quote_flag == false && double_quote_flag == false && parentheses_char_flag ==false && curly_brace_char_flag == false) {
            if (incoming_input[a] == '[' || incoming_input[a] == ']') {
                if (incoming_input[a] == '[') {
                    if (bracket_char_flag == false) {
                        bracket_char_flag = true;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                    } else {
                        std::cout << "There is a bracket char error." << std::endl;
                        error_flag = true;
                        break;
                    }
                } else if (incoming_input[a] == ']') {
                    if (bracket_char_flag == true) {
                        bracket_char_flag = false;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                        incoming_commands.push_back(special_symbol_container);
                        special_symbol_container = "";
                    } else {
                        std::cout << "There is a bracket char error." << std::endl;
                        error_flag = true;
                        break;
                    }
                }
            }
        }
        if (single_quote_flag == false && double_quote_flag == false && parentheses_char_flag == false && bracket_char_flag == false) {
            if (incoming_input[a] == '{' || incoming_input[a] == '}') {
                if (incoming_input[a] == '{') {
                    if (curly_brace_char_flag == false) {
                        curly_brace_char_flag = true;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                    } else {
                        std::cout << "There is a curly brace char error." << std::endl;
                        error_flag = true;
                        break;
                    }
                } else if (incoming_input[a] == '}') {
                    if (curly_brace_char_flag == true) {
                        curly_brace_char_flag = false;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                        incoming_commands.push_back(special_symbol_container);
                        special_symbol_container = "";
                    } else {
                        std::cout << "There is a curly brace char error." << std::endl;
                        error_flag = true;
                        break;
                    }
                }
            }
        }
        if (single_quote_flag == false && double_quote_flag == false && parentheses_char_flag == false && bracket_char_flag == false && curly_brace_char_flag == false) {
            if (incoming_input[a] == '>' || incoming_input[a] == '<' || incoming_input[a] == '|') {
                if (operator_found_flag == false) {
                    operator_found_flag = true;
                    which_command_parser = 1;
                } else {
                    if (incoming_input[a] != '>') {
                        std::cout << "There are to many operators near by error-1." << std::endl;
                        error_flag = true;
                        break;
                    }
                }
            } else if (incoming_input[a] == '&') {
                if (ampersand_flag == false) {
                    ampersand_flag = true;
                    waitpid_flag = true;
                } else {
                    std::cout << "There was an ampersand error-1." << std::endl;
                    error_flag = true;
                    break;
                }
            }
        }
        if (skip_this_char == false) {
            if (single_quote_flag == true || double_quote_flag == true || curly_brace_char_flag == true || bracket_char_flag == true || parentheses_char_flag == true) {
                special_symbol_container += incoming_input[a];
            } else {
                if (incoming_input[a] != 32)
                    token += incoming_input[a];
            }
        } else {
            skip_this_char = false;
        }

        if (incoming_input[a] == 32 || incoming_input[a] == ';' || ((incoming_input.size() -1) == a) ) {
            if (incoming_input[a] == 32) {
                if (single_quote_flag == false && double_quote_flag == false && curly_brace_char_flag == false && parentheses_char_flag == false && bracket_char_flag == false) {
                    if (ampersand_flag == true) {
                        if (argument_position != 0) {
                            std::cout << "There was an ampersand error-2." << std::endl;
                            error_flag = true;
                            break;
                        } else {
                            ampersand_flag = false;
                        }
                    }
                    if (token.size() > 0) {
                        if (next_operator_find_flag == true) {
                            std::cout << "There are to many operators near by error-2." << std::endl;
                            error_flag = true;
                            break;
                        }
                        if (operator_found_flag == true) {
                            if (token != ">" || token != ">>" || token != "1>" || token != "1>>" || token != "2>" || token != "2>>" || token != "<" || token != "0<" || token != "|") {
                                operator_found_flag = false;
                                ampersand_flag = false;
                                next_operator_find_flag = true;
                            } else {
                                std::cout << "There was an incorrect operator found error-1." << std::endl;
                                error_flag = true;
                                break;
                            }
                        }
                        incoming_commands.push_back(token);
                        argument_position++;
                    }
                    token = "";
                } 
            } else {
                if (single_quote_flag == true || double_quote_flag == true) {
                    if (single_quote_flag == true) {
                        std::cout << "There was a single quote error with this section of input" << std::endl;
                    } else {
                        std:: cout << "There was a double quote error with this secton of input." << std::endl;
                    }
                    error_flag = true;
                    break;
                } else if (parentheses_char_flag == true) {
                    std::cout << "There was a parentheses error with this seciton of input." << std::endl;
                    error_flag = true;
                    break;
                } else if (bracket_char_flag == true) {
                    std::cout << "There was a bracket error with this seciton of input." << std::endl;
                    error_flag = true;
                    break;
                } else if (curly_brace_char_flag == true) {
                    std::cout << "There was a curly brace error with this seciton of input." << std::endl;
                    error_flag = true;
                    break;
                } else {
                    if (ampersand_flag == true) {
                        if (argument_position != 0) {
                            std::cout << "There was an ampersand error-3." << std::endl;
                            error_flag = true;
                            break;
                        } else {
                            ampersand_flag = false;
                        }
                    }
                    if (token.size() > 0) {
                        if (next_operator_find_flag == true) {
                            std::cout << "There are to many operators near by error-3." << std::endl;
                            error_flag = true;
                            break;
                        }
                        if (operator_found_flag == true) {
                            if (token != ">" || token != ">>" || token != "1>" || token != "1>>" || token != "2>" || token != "2>>" || token != "<" || token != "0<" || token != "|") {
                                std::cout << "There was an incorrect operator found error-2." << std::endl;
                                error_flag = true;
                                break;
                            } else {
                                operator_found_flag = false;
                                ampersand_flag = false;
                                next_operator_find_flag = true;
                            }
                        }
                        incoming_commands.push_back(token);
                        argument_position++;
                    }
                    token = "";
                
                }
            }
        }
    }
    
    if (error_flag == false) {
        if (which_command_parser == 0) {
            Normal_Loop(incoming_commands, ThursdayCommands);
        } else {
            Operator_Loop(incoming_commands);
        }
    } else {
        incoming_commands.clear();
    }

    return;
}

void Normal_Loop(std::vector<std::string>incoming_commands, std::vector<std::string>ThursdayCommands) {

    std::vector<std::string> sending_commands;
    bool thursday_command_flag = false;
    int command_size = 0;

    for (int a = 0; a < incoming_commands.size(); ++a) {

        command_size = incoming_commands.size();

		for (int b = 0; b < ThursdayCommands.size(); b++) {
            if (ThursdayCommands[b] == incoming_commands[a]){
                thursday_command_flag = true;
            }
		}

        if ((incoming_commands[a][command_size - 1] == ';') || (incoming_commands.size() == (a - 1))) {
            if (incoming_commands[a][command_size - 1] == ';')
                incoming_commands[a].erase(incoming_commands[a].begin()+(incoming_commands[a].size() - 1), incoming_commands[a].end());
            
            sending_commands.push_back(incoming_commands[a]);
            if (thursday_command_flag == true) {
                std::cout << "We have found one of our commands and will call it." << std::endl;
            } else {
                std::cout << "We did not find one of our commands and will call exec." << std::endl;
            }
            thursday_command_flag = false;
            sending_commands.clear();
        } else {
            sending_commands.push_back(incoming_commands[a]);
        }
    }
    return;    
}

void Operator_Loop(std::vector<std::string>incoming_commands) {

    std::string standard_error_file = "";
    std::string standard_input_file = "";
    std::string standard_output_file = "";

    bool standard_error_flag = false;
    bool standard_out_flag = false;
    bool standard_in_flag = false;
    bool pipe_flag = false;
    bool pipe_control_flag = false;
    bool skip_argument_flag = false;
    bool end_of_section = false;

    bool adding_to_standard_out_file = false;
    bool adding_to_standard_error_file = false;
    
    int the_size = 0;

    std::vector<std::string> the_operators;
    std::vector<std::string> commands;

    // Rule #1: You cannot have standard out before standard in.
    // Rule #2: You can have standard out and stnadard error after a pipe but not standard in.
    // Rule #3: You can only have one standard out and standard in each input section.

    for (int f = 0; f < incoming_commands.size(); f++) {
        the_size = incoming_commands[f].size();
        std::cout << "Looking at: " << incoming_commands[f] << std::endl;
        if (incoming_commands[f] == "|") {
            standard_in_flag = true;
            standard_out_flag = false;
            standard_error_flag = false;
            skip_argument_flag = true;
            if (the_operators.size() == 0) {
                if (pipe_flag == false) {
                    std::cout << "----The commands going into pipe (No Operators).----" << std::endl;
                    for (int h = 0; h < commands.size(); h++)
                        std::cout << h << ": " << commands[h] << std::endl;
                    
                    std::cout << "The standard output file is: temp_output.txt " << std::endl;
                    standard_output_file = "temp_output.txt";
                } else {
                    std::cout << "----The commands going into pipe (Pipe was found previously).----" << std::endl;
                    for (int h = 0; h < commands.size(); h++) 
                        std::cout << h << ": " << commands[h] << std::endl;
                    
                    std::cout << "The incoming path with data from the last pipe: " << standard_input_file << std::endl;
                    std::cout << "The standard output file is: temp_output.txt " << std::endl;
                    standard_output_file = "temp_output.txt";
                }
            } else {
                for (int g = 0; g < the_operators.size(); g++) {
                    if (pipe_control_flag == false) {
                        if (the_operators[g] == "in") {
                            pipe_control_flag = true;
                            std::cout << "----The standard input commands before a pipe operator.----" << std::endl;
                            for (int h = 0; h < commands.size(); h++) 
                                std::cout << h << ": " << commands[h] << std::endl;
                            
                            std::cout << "The standard input file is: " << standard_input_file << std::endl;

                            if (standard_output_file != "") {
                                if (adding_to_standard_out_file == false) {
                                    std::cout << "The standard output file is: " << standard_output_file << std::endl;
                                } else {
                                    std::cout << "We are adding to the standard output file, and it is: " << standard_output_file << std::endl;
                                }
                            } else {
                                std::cout << "The standard output file is: temp_output.txt " << std::endl;
                                standard_output_file = "temp_output.txt";
                            }

                            if (standard_error_file != "") {
                                if (adding_to_standard_error_file == false) { 
                                    std::cout << "The standard error file is: " << standard_error_file << std::endl;
                                } else {
                                    std::cout << "We are adding to the standard error file, and it is: " << standard_error_file << std::endl;
                                }
                            }

                        } else if (the_operators[g] == "out") {
                            pipe_control_flag = true;
                            if (pipe_flag == false) {
                                std::cout << "----The standard output commands before a pipe operator.----" << std::endl;
                                for (int i = 0; i < commands.size(); i++) 
                                    std::cout << i << ": " << commands[i] << std::endl;
                                
                                if (adding_to_standard_out_file == false) {
                                    std::cout << "The standard output file is: " << standard_output_file << std::endl;
                                } else {
                                    std::cout << "We are adding to the standard output file, and it is: " << standard_output_file << std::endl;
                                }

                                if (standard_error_file != "") {
                                    if (adding_to_standard_error_file == false) { 
                                        std::cout << "The standard error file is: " << standard_error_file << std::endl;
                                    } else {
                                        std::cout << "We are adding to the standard error file, and it is: " << standard_error_file << std::endl;
                                    }
                                }
                            } else {
                                std::cout << "----The standard output commands for after finding a pipe operator.----" << std::endl;
                                for (int i = 0; i < commands.size(); i++) 
                                    std::cout << i << ": " << commands[i] << std::endl;

                                std::cout << "The incoming file for data is: " << standard_input_file << std::endl;
                                if (adding_to_standard_out_file == false) {
                                    std::cout << "The standard output file is: " << standard_output_file << std::endl;
                                } else {
                                    std::cout << "We are adding to the standard output file, and it is: " << standard_output_file << std::endl;
                                }

                                if (standard_error_file != "") {
                                    if (adding_to_standard_error_file == false) { 
                                        std::cout << "The standard error file is: " << standard_error_file << std::endl;
                                    } else {
                                        std::cout << "We are adding to the standard error file, and it is: " << standard_error_file << std::endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            standard_input_file = standard_output_file;
            pipe_control_flag = false;
            adding_to_standard_error_file = false;
            adding_to_standard_out_file = false;
            pipe_flag = true;
            commands.clear();
            the_operators.clear();
        }
        if (incoming_commands[f] == ">" || incoming_commands[f] == "1>" || incoming_commands[f] == ">>" || incoming_commands[f] == "1>>" ) {
            if (standard_out_flag == false) {
                the_operators.push_back("out");
                if (pipe_flag == true) {
                    standard_input_file = standard_output_file;
                }
                if (incoming_commands[f] == ">>" || incoming_commands[f] == "1>>") {
                    adding_to_standard_out_file = true;
                }
                standard_out_flag = true;
                standard_in_flag = true;
                skip_argument_flag = true;
                f++;
                the_size = incoming_commands[f].size();
                if (incoming_commands[f][the_size - 1] == ';') {
                    incoming_commands[f].erase(incoming_commands[f].begin()+(incoming_commands[f].size() - 1), incoming_commands[f].end());
                    end_of_section = true;
                }
                standard_output_file = incoming_commands[f];
            } else {
                std::cout << "There was one to many standard out operators." << std::endl;
            }
        }
        if (incoming_commands[f] == "2>" || incoming_commands[f] == "2>>") {
            if (incoming_commands[f] == "2>>") {
                adding_to_standard_error_file = true;
            }
            the_operators.push_back("error");
            skip_argument_flag = true;
            f++;
            the_size = incoming_commands[f].size();
            if (incoming_commands[f][the_size - 1] == ';') {
                incoming_commands[f].erase(incoming_commands[f].begin()+(incoming_commands[f].size() - 1), incoming_commands[f].end());
                end_of_section = true;
            }
            standard_error_file = incoming_commands[f];
        }
        
        if (incoming_commands[f] == "0<" || incoming_commands[f] == "<") {
            if (standard_in_flag == false) {
                the_operators.push_back("in");
                standard_in_flag = true;
                skip_argument_flag = true;
                f++;
                the_size = incoming_commands[f].size();
                if (incoming_commands[f][the_size - 1] == ';') {
                    incoming_commands[f].erase(incoming_commands[f].begin()+(incoming_commands[f].size() - 1), incoming_commands[f].end());
                    end_of_section = true;
                }
                standard_input_file = incoming_commands[f];
            } else {
                std::cout << "There was one to many standard in operators." << std::endl;
            }
        }

        if (end_of_section == true || incoming_commands[f][the_size - 1] == ';' || (incoming_commands.size() - 1) == f) {
            if (the_operators.size() == 0) {
                std::cout << "Saving: " <<  incoming_commands[f] << std::endl;
                skip_argument_flag = true;
                commands.push_back(incoming_commands[f]);
                if (pipe_flag == false) {
                    std::cout << "----The basic commands----" << std::endl;
                    for (int h = 0; h < commands.size(); h++) 
                        std::cout << h << ": " << commands[h] << std::endl;
                } else {
                    std::cout << "----The commands coming after a pipe.----" << std::endl;
                    for (int h = 0; h < commands.size(); h++) 
                        std::cout << h << ": " << commands[h] << std::endl;
                    
                    std::cout << "The incoming path with data from the last pipe: " << standard_input_file << std::endl;
                    std::cout << "----The output is going to the screen.----" << std::endl;
                }
            } else {
                for (int j = 0; j < the_operators.size(); j++) {
                    if (pipe_control_flag == false) {
                        if (the_operators[j] == "in") {
                            pipe_control_flag = true;
                            std::cout << "----The standard input commands----" << std::endl;
                            for (int k = 0; k < commands.size(); k++) 
                                std::cout << k << ": " << commands[k] << std::endl;
                            
                            std::cout << "The standard input file is: " << standard_input_file << std::endl;

                            if (standard_output_file != "") {
                                if (adding_to_standard_out_file == false) {
                                    std::cout << "The standard output file is: " << standard_output_file << std::endl;
                                } else {
                                    std::cout << "We are adding to the standard output file, and it is: " << standard_output_file << std::endl;
                                }
                            } else {
                                std::cout << "The standard output file is: temp_output.txt " << std::endl;
                                standard_output_file = "temp_output.txt";
                            }

                            if (standard_error_file != "") {
                                if (adding_to_standard_error_file == false) { 
                                    std::cout << "The standard error file is: " << standard_error_file << std::endl;
                                } else {
                                    std::cout << "We are adding to the standard error file, and it is: " << standard_error_file << std::endl;
                                }
                            }

                        } else if (the_operators[j] == "out") {
                            pipe_control_flag = true;
                            if (pipe_flag == false) {
                                std::cout << "----The standard output commands----" << std::endl;
                                for (int l = 0; l < commands.size(); l++) 
                                    std::cout << l << ": " << commands[l] << std::endl;

                                if (adding_to_standard_out_file == false) {
                                    std::cout << "The standard output file is: " << standard_output_file << std::endl;
                                } else {
                                    std::cout << "We are adding to the standard output file, and it is: " << standard_output_file << std::endl;
                                }

                                if (standard_error_file != "") {
                                    if (adding_to_standard_error_file == false) { 
                                        std::cout << "The standard error file is: " << standard_error_file << std::endl;
                                    } else {
                                        std::cout << "We are adding to the standard error file, and it is: " << standard_error_file << std::endl;
                                    }
                                }
                            } else {
                                std::cout << "----The standard output commands----" << std::endl;
                                for (int i = 0; i < commands.size(); i++) 
                                    std::cout << i << ": " << commands[i] << std::endl;
                                
                                std::cout << "----The incoming file for data is: " << standard_input_file << std::endl;
                                
                                if (adding_to_standard_out_file == false) {
                                    std::cout << "The standard output file is: " << standard_output_file << std::endl;
                                } else {
                                    std::cout << "We are adding to the standard output file, and it is: " << standard_output_file << std::endl;
                                }

                                if (standard_error_file != "") {
                                    if (adding_to_standard_error_file == false) { 
                                        std::cout << "The standard error file is: " << standard_error_file << std::endl;
                                    } else {
                                        std::cout << "We are adding to the standard error file, and it is: " << standard_error_file << std::endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            standard_error_file = "";
            standard_input_file = "";
            standard_output_file = "";

            standard_error_flag = false;
            standard_out_flag = false;
            standard_in_flag = false;
            pipe_flag = false;
            adding_to_standard_error_file = false;
            adding_to_standard_out_file = false;
            pipe_control_flag = false;
            end_of_section = false;
            the_operators.clear();
            commands.clear();
        }

        if (skip_argument_flag == false) {
            std::cout << "Saving: " << incoming_commands[f] << std::endl;
            commands.push_back(incoming_commands[f]);
        } else {
            skip_argument_flag = false;
        }
    }
    return;
}
