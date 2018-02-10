#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> LoadVector();
std::vector<std::string> First_Loop(std::vector<std::string> incoming_commands, std::string incoming_input);

int main() {
    std::string incoming_input = "";

    std::vector<std::string> ThursdayCommands = LoadVector();
    std::vector<std::string> incoming_commands;

    while(1) {
        std::cout << "Please enter: ";
        std::getline(std::cin, incoming_input);

        if (incoming_input == "exit")
            return 0;

        incoming_commands = First_Loop(incoming_commands, incoming_input);
        for (int a = 0; a < incoming_commands.size(); ++a)
            std::cout << a << ": " << incoming_commands[a] << " Size: " << incoming_commands[a].size() << std::endl;
        
        incoming_commands.clear();
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

std::vector<std::string> First_Loop(std::vector<std::string> incoming_commands, std::string incoming_input) {
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
            // Do the normal loop.
        } else {
            // Do the loop for the operators.
        }
    } else {
        incoming_commands.clear();
    }

    return incoming_commands;
}