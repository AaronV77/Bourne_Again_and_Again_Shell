#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> LoadVector();
std::vector<std::string> ParseInput(std::vector<std::string> out_going, std::string incoming_input);

int main() {
    std::string incoming_input = "";
    std::vector<std::string> ThursdayCommands = LoadVector();
    std::vector<std::string> incoming_command;

    while(1) {
        std::cout << "Please enter: ";
        std::getline(std::cin, incoming_input);

        incoming_command = ParseInput(incoming_command, incoming_input);                                    //  This takes care of any werid user spaceing issues.


/*         for (int a = 0; a < incoming_command.size(); ++a) {

            std::cout << incoming_command[a] << " Size: " << incoming_command[a].size() << std::endl;

        } */

        incoming_command.clear();
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

std::vector<std::string> ParseInput(std::vector<std::string> out_going, std::string incoming_input) {
    std::string token = "";
    bool single_quote_flag = false;
    bool double_quote_flag = false;
    bool operator_flag = false;
    bool next_character_flag = false;
    bool stdout_flag = false;

    // This loop just gets rid of all spaces and tokens the incoming input.
    // This loop also makes sure there is a correct number of quotes (single and double).
    // This loop is also make sure that there are not more than one operator next to each other without a space and with a space.
    // I do this by setting a flag when an operator is found, and set another operator when a space is found.
    // If the next character after that space is another opeator then there is an error else there is not.
    // Then shoves them into a vector and returns the vector.

    for (int i = 0; i < incoming_input.size(); ++i) {
        if (incoming_input[i] == 39) {
            if (double_quote_flag == false) {
                if (single_quote_flag == false)
                    single_quote_flag = true;
                else
                    single_quote_flag = false;
            }
        } else if (incoming_input[i] == '"') {
            if (single_quote_flag == false) {
                if (double_quote_flag == false)
                    double_quote_flag = true;
                else
                    double_quote_flag = false;
            }
        } else if (incoming_input[i] == '>' || incoming_input[i] == '|' || incoming_input[i] == '<') {
            if (operator_flag == false) {
                operator_flag = true;
            } else if (incoming_input[i] == '>') {
                if (stdout_flag == false) {
                    stdout_flag = true;
                } else {
                    std::cout << "There are too many stdout operator symbols error." << std::endl;
                    out_going.clear();
                    break;
                }
            } else {
                std::cout << "There were too many operators close to one another error." << std::endl;
                out_going.clear();
                break;
            }
        }

        if (incoming_input[i] != 32)
            token += incoming_input[i];

        if (incoming_input[i] == 32 || incoming_input[i] == ';' || ((incoming_input.size() -1) == i) ) {
            if (incoming_input[i] == 32) {
                if (operator_flag == true) {
                    next_character_flag == true;
                }
                if (token.size() > 0) {
                    out_going.push_back(token);
                    token = "";
                }
            } else if (single_quote_flag == true || double_quote_flag == true) {
                std::cout << "There was a quote error with a seciton of input." << std::endl;
                out_going.clear();
                break;
            } else {
                if (next_character_flag == true) {
                    if (incoming_input[i] == 60 || incoming_input[i] == 62 || incoming_input[i] == 124 || incoming_input[i] == 48 || incoming_input[i] == 49) {
                        std::cout << "There were to many operators close to one another error - 2." << std::endl;
                        out_going.clear();
                        break;
                    } else {
                        operator_flag = true;
                        next_character_flag = true;
                    }
                }
                if (token.size() > 0) {
                    out_going.push_back(token);
                    token = "";
                }
            }
            operator_flag = false;
            stdout_flag = false;
        }
    }

    // This loop is make sure that there is only one argument after an stdin or stdout operator.
    // First we loop through the whole vector of tokens. If we find an stdin or stdou operator we work the algorithm.
    // We create two variables of iterators, the first "b" is to look at the next token and the other variable "c" is to set a range.
    // If the variable "c" is bigger than the vector size itself then we break, because that means there is only one argument after the operator.
    // Else we loop through the given range looking for another operator, if we found it then we are find, else there are to many arguments after the operator.
    operator_flag = false;
    for (int a = 0; a < out_going.size(); a++) {
        if (out_going[a] == ">" || out_going[a] == "<" || out_going[a] == "0<" || out_going[a] == "1>") {
            int b = a + 1;
            int c = a + 2;
            if (c >= out_going.size()) {
                break;
            } else {
                for (int d = b; d <= c; ++d) {
                    std::cout << "Second Loop Search: " << out_going[d] << std::endl;
                    if (out_going[d] == ">" || out_going[d] == "<" || out_going[d] == "0<" || out_going[d] == "1>" || out_going[d] == "|") {
                        operator_flag = true;
                        break;
                    }
                }
                if (operator_flag == false) {
                    std::cout << "There are to many commands / arguments after the stdin or stdout operator error." << std::endl;
                    out_going.clear();
                    break;
                }
            }
        }
    }

    std::size_t stringFind;
    int size = 0;
    for (int e = 0; e < out_going.size(); e++) {
        size = out_going[e].size();
        stringFind = out_going[e].find("2>");
        if (stringFind != std::string::npos) {
            stringFind = out_going[e].find("2>>");
            if (stringFind != std::string::npos) {
                if (out_going[e].size() > 3){
                    std::cout << "There was an operator size issue error." << std::endl;
                    out_going.clear();
                    break;
                }
            } else {
                if (out_going[e].size() > 2){
                    std::cout << "There was an operator size issue error." << std::endl;
                    out_going.clear();
                    break;
                }
            }
        }
        stringFind = out_going[e].find(">");
        if (stringFind != std::string::npos) {
            stringFind = out_going[e].find(">>");
            if (stringFind != std::string::npos) {
                if (out_going[e].size() > 3){
                    std::cout << "There was an operator size issue error." << std::endl;
                    out_going.clear();
                    break;
                }
            } else {
                if (out_going[e].size() > 2){
                    std::cout << "There was an operator size issue error." << std::endl;
                    out_going.clear();
                    break;
                } 
            }
        }
        stringFind = out_going[e].find("<");
        if (stringFind != std::string::npos) {
            if (out_going[e].size() > 2){
                std::cout << "There was an operator size issue error." << std::endl;
                out_going.clear();
                break;
            }
        }
        stringFind = out_going[e].find("|");
        if (stringFind != std::string::npos) {
            if (out_going[e].size() > 1){
                std::cout << "There was an operator size issue error." << std::endl;
                out_going.clear();
                break;
            }
        }
        stringFind = out_going[e].find("|");
        if (stringFind != std::string::npos) {
            if (out_going[e].size() > 1){
                std::cout << "There was an operator size issue error." << std::endl;
                out_going.clear();
                break;
            }
        }

        if (out_going[e][size - 1] != ';') {
            stringFind = out_going[e].find(";");
            if (stringFind != std::string::npos) {
                if (out_going[e].size() > 1){
                    std::cout << "There was a semicolon in a middle of a token error." << std::endl;
                    out_going.clear();
                    break;
                }
            } 
        }
    }

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

    for (int f = 0; f < out_going.size(); f++) {
        the_size = out_going[f].size();
        std::cout << "Looking at: " << out_going[f] << std::endl;
        if (out_going[f] == "|") {
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
        if (out_going[f] == ">" || out_going[f] == "1>" || out_going[f] == ">>" || out_going[f] == "1>>" ) {
            if (standard_out_flag == false) {
                the_operators.push_back("out");
                if (pipe_flag == true) {
                    standard_input_file = standard_output_file;
                }
                if (out_going[f] == ">>" || out_going[f] == "1>>") {
                    adding_to_standard_out_file = true;
                }
                standard_out_flag = true;
                standard_in_flag = true;
                skip_argument_flag = true;
                f++;
                the_size = out_going[f].size();
                if (out_going[f][the_size - 1] == ';') {
                    out_going[f].erase(out_going[f].begin()+(out_going[f].size() - 1), out_going[f].end());
                    end_of_section = true;
                }
                standard_output_file = out_going[f];
            } else {
                std::cout << "There was one to many standard out operators." << std::endl;
            }
        }
        if (out_going[f] == "2>" || out_going[f] == "2>>") {
            if (out_going[f] == "2>>") {
                adding_to_standard_error_file = true;
            }
            the_operators.push_back("error");
            skip_argument_flag = true;
            f++;
            the_size = out_going[f].size();
            if (out_going[f][the_size - 1] == ';') {
                out_going[f].erase(out_going[f].begin()+(out_going[f].size() - 1), out_going[f].end());
                end_of_section = true;
            }
            standard_error_file = out_going[f];
        }
        
        if (out_going[f] == "0<" || out_going[f] == "<") {
            if (standard_in_flag == false) {
                the_operators.push_back("in");
                standard_in_flag = true;
                skip_argument_flag = true;
                f++;
                the_size = out_going[f].size();
                if (out_going[f][the_size - 1] == ';') {
                    out_going[f].erase(out_going[f].begin()+(out_going[f].size() - 1), out_going[f].end());
                    end_of_section = true;
                }
                standard_input_file = out_going[f];
            } else {
                std::cout << "There was one to many standard in operators." << std::endl;
            }
        }

        if (end_of_section == true || out_going[f][size - 1] == ';' || (out_going.size() - 1) == f) {
            if (the_operators.size() == 0) {
                std::cout << "Saving: " <<  out_going[f] << std::endl;
                skip_argument_flag = true;
                commands.push_back(out_going[f]);
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
            std::cout << "Saving: " << out_going[f] << std::endl;
            commands.push_back(out_going[f]);
        } else {
            skip_argument_flag = false;
        }
    }


    return out_going;

}