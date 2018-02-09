#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> LoadVector();
std::vector<std::string> ParseInput(std::vector<std::string> out_going, std::string incoming_input);

int main() {
    std::string error_message = "";
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
    std::vector<std::string> incoming_commands;
    std::vector<std::string> pipeFirstCommands;
    std::vector<std::string> pipeSecondCommands;

    while(1) {
        std::cout << "Please enter: ";
        std::getline(std::cin, incoming_input);

        incoming_commands = ParseInput(incoming_commands, incoming_input)

        std::istringstream iss (incomingInput);                                                             // Prepare the incoming string
        while(std::getline(iss,input,' ')) {                                                                // Loop through the string by tokenizing by space.
            /*------------------------------------------------------------------------------*/
            size = input.size();                                                                            // Get the length of the token.
            /*------------------------------------------------------------------------------*/
            if (iss.tellg() == -1)                                                                          // Check to see if the next token is the last.
                last_item_flag = true;                                                                      // If so then set our bool statment to true.
            /*------------------------------------------------------------------------------*/
            if (double_quote_flag == false && single_quote_flag == false) {
                if (input == ">") {                                                                         // Check to see if the token is an operator.
                    if (pipe_flag == true) {
                        pipeSecondCommands = commands;
                        std::cout << "We have to run this through our spcial method for pipe" << std::endl;
                        std::cout << "And run it to another ouptput file" << std::endl;
                        std::cout << "File Path: " << filePath << std::endl;
                        for (int i = 0; i < pipeSecondCommands.size(); i++)
                            std::cout << i << ": " << pipeSecondCommands[i] << std::endl;
                        standard_out_secondary_flag = true;
                    } else if (standard_out_flag == true || standard_in_flag == true) {
                        error_flag = true;
                        error_message = "Check1";
                    }
                    standard_out_flag = true;
                } else if (input == "<") {                                                                  //
                    if (standard_out_flag == true || pipe_flag == true || standard_in_flag == true) {
                        error_flag = true;
                        error_message = "Check2";
                    }
                    standard_in_flag = true;
                } else if (input == "|") {                                                                  //
                    if (pipe_flag == true) {
                        pipeSecondCommands = commands;
                        std::cout << "Pipe PT3:" << std::endl;
                        for (int i = 0; i < pipeFirstCommands.size(); i++)
                            std::cout << i << ": " << pipeFirstCommands[i] << std::endl;

                        std::cout << std::endl << "Pipe PT4 - Pipe to specail method:" << std::endl;
                        for (int i = 0; i < pipeSecondCommands.size(); i++)
                            std::cout << i << ": " << pipeSecondCommands[i] << std::endl;
                        std::cout << std::endl;
                        // Will have to make a Pipe call from here.
                        next_argument_flag = true;
                        pipe_secondary_flag = true;
                        pipeFirstCommands.clear();
                        pipeSecondCommands.clear();
                        commands.clear();
                    } else {
                        if (standard_out_flag == true || standard_in_flag == true) {
                            error_flag = true;
                            error_message = "Check3";
                        }
                        operatorType = 4;                                                                       //
                        pipe_flag = true;                                                                       //
                        next_argument_flag = true;
                        pipeFirstCommands = commands;                                                           //
                        commands.clear();                                                                       //
                    }
                }   
            }
            /*------------------------------------------------------------------------------*/
            if (double_quote_flag == false && single_quote_flag == false) {
                if (input[size - 1] == ';') {                                                                   //
                    input.erase(input.begin()+(input.size() - 1), input.end());	                                //
                    semicolon_flag = true;                                                                      //
                } else {                                                                                        //
                    stringFind = input.find(';');                                                               //
                    if (stringFind != std::string::npos) {                                                      //
                        if (double_quote_flag != true && single_quote_flag != true) {                           //
                            std::cout << "There was some big mistake with your commands." << std::endl;         //
                            break;                                                                              //
                        }
                    }
                }
            }
            /*------------------------------------------------------------------------------*/
            if (double_quote_flag == false) {                                                               //
                if (input[0] == 39 || input[size - 1] == 39) {                                              //
                    if (single_quote_flag == false) {                                                       //
                        single_quote_flag = true;                                                           //
                    } else {                                                                                //
                        single_quote_flag = false;                                                          //
                        skip_command_flag = true;                                                           //
                        singleQuote += input;                                                               //
                        commands.push_back(singleQuote);                                                    //
                        singleQuote = "";                                                                   //
                    }
                } else {                                                                                    //
                    stringFind = input.find("'");                                                           //
                    if (stringFind != std::string::npos) {                                                  //
                        error_flag = true;                                                                  //
                        error_message = "Check4";
                        if (single_quote_flag == true) {                                                    //
                            single_quote_flag = false;                                                      //
                            singleQuote = "";
                        }
                    }
                }
            }
            /*------------------------------------------------------------------------------*/
            if (single_quote_flag == false) {                                                               //
                if (input[0] == '"' || input[size - 1] == '"') {                                            //
                    if (double_quote_flag == false) {                                                       //
                        double_quote_flag = true;                                                           //
                    } else {                                                                                //
                        double_quote_flag = false;                                                          //
                        skip_command_flag = true;                                                           //
                        doubleQuote += input;                                                               //
                        commands.push_back(doubleQuote);                                                    //
                        doubleQuote = "";                                                                   //
                    }
                } else {                                                                                    //
                    stringFind = input.find('"');                                                           //
                    if (stringFind != std::string::npos) {                                                  //
                        error_flag = true;                                                                  //
                        error_message = "Check5";
                        if (double_quote_flag == true) {                                                    //
                            double_quote_flag = false;                                                      //
                            doubleQuote = "";                                                               //
                        }
                    }
                }
            }
            /*------------------------------------------------------------------------------*/
            if (argumentPosition == 0) {                                                                    //
                for (int a = 0; a < ThursdayCommands.size(); a++) {                                         //
                    if (ThursdayCommands[a] == input)                                                       //
                        my_command_flag = true;	                                                            //												
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
                } else if (semicolon_flag == true || last_item_flag == true) {                                  //
                    if (skip_command_flag == false)                                                         //
                        commands.push_back(input);                                                          //

                    if (my_command_flag == false) {                                                         //
                        std::cout << "1 - Commands: " << std::endl;
                        for (int i = 0; i < commands.size(); i++)
                            std::cout << i << ": " << commands[i] << std::endl;
                        // SearchCommands(commandAndArguments, 1, envp);
                    } else if (my_command_flag == true) {                                                   //
                        std::cout << "2 - Commands: " << std::endl;
                        for (int i = 0; i < commands.size(); i++)
                            std::cout << i << ": " << commands[i] << std::endl;
                        // SearchCommands(commandAndArguments, 0, envp);
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
                } else if (next_argument_flag == false) {                                                       //
                    argumentPosition++;                                                                         //
                    if (single_quote_flag == false && double_quote_flag == false) {                             //
                        commands.push_back(input);                                                              //
                    } else if (single_quote_flag == true) {                                                     //
                        singleQuote += input;                                                                   //
                        singleQuote += " ";                                                                     //
                    } else if (double_quote_flag == true) {                                                     //
                        doubleQuote += input;                                                                   //
                        doubleQuote += " ";                                                                     //
                    }
                } else {
                    next_argument_flag = false;
                }
            } else {
                std::cout << "Sorry there was error some where!" << std::endl;
                std::cout << "ERROR: " << error_message << std::endl;
                break;
            }
        }
        singleQuote = "";
        doubleQuote = "";
        outputPath = "";
        inputPath = "";
        single_quote_flag = false;
        double_quote_flag = false;
        next_argument_flag = false;
        standard_in_flag = false;
        standard_out_flag = false;
        standard_out_secondary_flag = false;
        pipe_flag = false;
        pipe_secondary_flag = false;
        semicolon_flag = false;
        last_item_flag = false;
        my_command_flag = false;
        error_flag = false;
        skip_command_flag = false;
        moreOperatorsFound = false;
        white_space_flag = false;
        pipeFirstCommands.clear();
        pipeSecondCommands.clear();
        commands.clear();
        operatorType = 0;
        argumentPosition = 0;
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

    single_quote_flag = false;
    double_quote_flag = false;

    token = "";

    return out_going;

}