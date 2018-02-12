#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> LoadVector();
std::vector<std::string> ParseInput(std::vector<std::string> out_going, std::string incoming_input);

int main() {

    std::string incoming_input = "";
    std::string singleQuote = "";
    std::string doubleQuote = "";
    std::string outputPath = "";
    std::string inputPath = "";
    std::string filePath = "going_out_too";

    bool single_quote_flag = false;
    bool double_quote_flag = false;
    bool next_argument_flag = false;
    bool standard_in_flag = false;
    bool standard_out_flag = false;
    bool standard_out_secondary_flag = false;
    bool pipe_flag = false;
    bool pipe_secondary_flag = false;
    bool semicolon_flag = false;
    bool last_item_flag = false;
    bool my_command_flag = false;
    bool error_flag = false;
    bool skip_command_flag = false;
    bool moreOperatorsFound = false;
    bool white_space_flag = false;

    std::size_t stringFind;

    int operatorType = 0;
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

        incoming_command = ParseInput(incoming_command, incoming_input);                                    //  This takes care of any werid user spaceing, and any simple single or double quote issues.

        for (int a = 0; a < incoming_command.size(); ++a) {


            /*------------------------------------------------------------------------------*/
            if (argumentPosition == 0) {                                                                    //  If our argument position is at the start. We do this because all of our commands will be at the start.
                for (int a = 0; a < ThursdayCommands.size(); a++) {                                         //  Looop through the vector of my commands.
                    if (ThursdayCommands[a] == input)                                                       //  Check to see if the token we have matches any of my commands.
                        my_command_flag = true;	                                                            //	Set the command flag to true.
                }
            }
            /*------------------------------------------------------------------------------*/
            if (error_flag == false) {
                if (standard_in_flag == true || standard_out_flag == true) {                                      //
                    next_argument_flag = true;                                                                    //
                } else if (next_argument_flag == true && (last_item_flag == true || semicolon_flag == true)) {    //
                    if (argumentPosition >= 1) {
                        next_argument_flag = false;                                                               //
                        if (standard_out_flag == true) {                                                          //
                            outputPath = input;                                                                   //
                            if (standard_out_secondary_flag == true) {
                                std::cout << "We are going to execute the CP command or find some way to copy the contents over~!" << std::endl;
                                std::cout << "Output file is: " << outputPath << std::endl;
                            } else {
                                std::cout << "Standard Out" << std::endl;
                                for (int i = 0; i < commands.size(); i++)
                                    std::cout << i << ": " << commands[i] << std::endl;
                                std::cout << "File: " << outputPath << std::endl;
                            }
                            outputPath = "";
                        } else if (standard_in_flag == true) {                                                    //
                            inputPath = input;                                                                    //
                            std::cout << "Standard In" << std::endl;
                            for (int i = 0; i < commands.size(); i++)
                                std::cout << i << ": " << commands[i] << std::endl;
                            std::cout << "File: " << inputPath << std::endl;
                            inputPath = "";
                        }
                        next_argument_flag = false;
                        standard_in_flag = false;
                        standard_out_flag = false;
                        standard_out_secondary_flag = false;
                        semicolon_flag = false;
                        last_item_flag = false;
                        my_command_flag = false;
                        commands.clear();
                        argumentPosition = 0;
                    } else {
                        std::cout << "Sorry there was error some where - 1 !" << std::endl;
                        break;
                    }
                } else if (pipe_flag == true && (last_item_flag == true || semicolon_flag == true)) {             //
                    if (argumentPosition >= 1) {
                        commands.push_back(input);                                                                  //
                        
                        if (pipe_secondary_flag == true) {
                            pipeSecondCommands = commands;
                            std::cout << "We have to run the standard IN again for PIPE" << std::endl;
                            std::cout << "File Path: " << filePath << std::endl;
                            for (int i = 0; i < pipeSecondCommands.size(); i++)
                                std::cout << i << ": " << pipeSecondCommands[i] << std::endl;
                        } else {
                            pipeSecondCommands = commands;
                            std::cout << "Pipe PT1:" << std::endl;
                            for (int i = 0; i < pipeFirstCommands.size(); i++)
                                std::cout << i << ": " << pipeFirstCommands[i] << std::endl;
                        
                            std::cout << std::endl << "Pipe PT2:" << std::endl;
                            for (int i = 0; i < pipeSecondCommands.size(); i++)
                                std::cout << i << ": " << pipeSecondCommands[i] << std::endl;
                        }
                        commands.clear();
                        pipeFirstCommands.clear();
                        pipeSecondCommands.clear();
                        pipe_flag = false;
                        pipe_secondary_flag = false;
                        last_item_flag = false;
                        my_command_flag = false;
                        argumentPosition = 0;
                        operatorType = 0;
                    } else {
                        std::cout << "Sorry there was error some where - 2!" << std::endl;
                        break;
                    }
                } else if (semicolon_flag == true || last_item_flag == true) {                                  //  If we are at the end of a section of commands and arguments.
                    if (skip_command_flag == false)                                                             //  
                        commands.push_back(input);                                                              //
                    if (my_command_flag == false) {                                                             //
                        std::cout << "1 - Commands: " << std::endl;
                        for (int i = 0; i < commands.size(); i++)
                            std::cout << i << ": " << commands[i] << std::endl;
                    } else if (my_command_flag == true) {                                                       //
                        std::cout << "2 - Commands: " << std::endl;
                        for (int i = 0; i < commands.size(); i++)
                            std::cout << i << ": " << commands[i] << std::endl;
                    }
                    commands.clear();
                    semicolon_flag = false;
                    last_item_flag = false;
                    single_quote_flag = false;
                    double_quote_flag = false;
                    skip_command_flag = false;
                    my_command_flag = false;    
                    argumentPosition = 0;  
                    singleQuote = "";
                    doubleQuote = "";        
                } else if (next_argument_flag == false) {                                                       //  If we have not already stored the token.
                    argumentPosition++;                                                                         //  Increment the number of arguments we have looked at in the given section.
                    if (single_quote_flag == false && double_quote_flag == false) {                             //  If we are not current in a quote.
                        commands.push_back(incoming_command[a]);                                                //  Store the incoming token.
                    } else if (single_quote_flag == true) {                                                     //  If we are in a single quote.
                        singleQuote += incoming_command[a];                                                     //  Store the token into the single quote string.
                        singleQuote += " ";                                                                     //  Add a space to the string.
                    } else if (double_quote_flag == true) {                                                     //  If we are in a double quote.
                        doubleQuote += incoming_command[a];                                                     //  Store the token into the double quote string.
                        doubleQuote += " ";                                                                     //  Add a space to the string.
                    }
                } else {                                                                                        //  If we have already stored the incoming token.
                    next_argument_flag = false;                                                                 //  Set our next flag to fals.
                }
            } else {                                                                                            //  We found an error some where in the algorithm.
                std::cout << "Sorry there was error some where!" << std::endl;                                  //  Display our error logs.
                std::cout << "ERROR LOG: " std::endl;
                for (int b = 0; b < error_log.size(); ++b)                                                      //  Loop through the error log messages.
                    std::cout << error_log[b] << std::endl;
                break;                                                                                          // Break from the loop altogether, because any commands after this will not work if the first section doesnt.
            }
        }

        // Need to reset the variables here
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

    for (int i = 0; i < incoming_input.size(); ++i) {
        if (incoming_input[i] != 32) {
            if (incoming_input[i] == 39) {
                if (single_quote_flag == false) {
                    single_quote_flag = true;
                    token += incoming_input[i];
                } else {
                    single_quote_flag = false;
                    token += incoming_input[i];
                }
            } else if (incoming_input[i] == '"') {
                if (double_quote_flag == false) {
                    double_quote_flag = true;
                    token += incoming_input[i];
                } else {
                    double_quote_flag = false;
                    token += incoming_input[i];
                }
            } else if (incoming_input[i] == ';' || ((incoming_input.size() -1) == i) ) {

                if (single_quote_flag == true || double_quote_flag == true) {
                    cout << "There was a quote error with a seciton of input." << endl;
                    out_going.clear();
                } else {
                    if (token.size() > 0)
                        out_going.push_back(token);
                }
                token = "";
            } else {
                token += incoming_input[i];
            }
        } else {
            if (token.size() > 0)
                out_going.push_back(token);
        }
    }

    return out_going;

}