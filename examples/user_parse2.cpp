#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> LoadVector();
std::vector<std::string> ParseInput(std::vector<std::string> out_going, std::string incoming_input);

int main() {

    std::string incoming_input = "";
    std::string singleQuote = "";
    std::string doubleQuote = "";

    bool single_quote_flag = false;
    bool double_quote_flag = false;
    bool next_argument_flag = false;
    bool semicolon_flag = false;
    bool last_item_flag = false;
    bool my_command_flag = false;
    bool error_flag = false;

    std::size_t stringFind;

    int size = 0;
    int argumentPosition = 0;

    std::vector<std::string> ThursdayCommands = LoadVector();
    std::vector<std::string> commands;
    std::vector<std::string> error_log;
    std::vector<std::string> incoming_command;
    std::vector<std::string> pipeFirstCommands;
    std::vector<std::string> pipeSecondCommands;

    while(1) {
        std::cout << "Please enter: ";
        std::getline(std::cin, incoming_input);

        incoming_command = ParseInput(incoming_command, incoming_input);                                    //  This takes care of any werid user spaceing issues.


        for (int a = 0; a < incoming_command.size(); ++a) {

            std::cout << incoming_command[a] << " Size: " << incoming_command[a].size() << std::endl;

        }

        size = 0;
        argumentPosition = 0;
        incoming_input = "";
        singleQuote = "";
        doubleQuote = "";

        single_quote_flag = false;
        double_quote_flag = false;
        next_argument_flag = false;
        semicolon_flag = false;
        last_item_flag = false;
        my_command_flag = false;
        error_flag = false;
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
    bool pipe_flag = false;

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
                for (int d = b; d < c; ++d) {
                    if (out_going[d] == ">" || out_going[d] == "<" || out_going[d] == "0<" || out_going[d] == "1>" || out_going == "|") {
                        operator_flag = true;
                        break;
                    }
                }
                if (operator_flag == false) {
                    std::cout << "There are to many commans / arguments after the stdin or stdout operator error." << std::endl;
                    out_going.clear();
                    break;
                }
            }
        }
    }
    operator_flag = false;
    stdout_flag = false;
    pipe_flag = false;
    int stdout = 1;
    int stdin = 0;
    int pipe = 0;
    int total = -1;
    std::size_t stringFind;
    for (int e = 0; e < out_going.size(); e++) {
        stringFind = incoming_command[a].find("2>");
        if (stringFind != std::string::npos) {
            stringFind = incoming_command[a].find("2>>");
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
        stringFind = incoming_command[a].find(">");
        if (stringFind != std::string::npos) {
            stringFind = incoming_command[a].find(">>");
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

        stringFind = incoming_command[a].find("<");
        if (stringFind != std::string::npos) {
            if (out_going[e].size() > 2){
                std::cout << "There was an operator size issue error." << std::endl;
                out_going.clear();
                break;
            }
        }

        stringFind = incoming_command[a].find("|");
        if (stringFind != std::string::npos) {
            if (out_going[e].size() > 1){
                std::cout << "There was an operator size issue error." << std::endl;
                out_going.clear();
                break;
            }

        }


    }



    return out_going;

}