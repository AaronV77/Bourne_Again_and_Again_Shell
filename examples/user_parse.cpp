#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> LoadVector();

int main() {
    std::string incomingInput = "";
    std::string singleQuote = "";
    std::string doubleQuote = "";
    std::string input = "";
    std::string quote = "";
    std::string outputPath = "";
    std::string inputPath = "";

    bool foundSingleQuote = false;
    bool foundDoubleQuote = false;
    bool needNextArgument = false;
    bool pipeWasFound = false;
    bool operatorFound = false;
    bool semiColonFound = false;
    bool lastItem = false;
    bool commandSwitch = false;
    bool errorFound = false;

    std::size_t stringFind;

    int operatorType = 0;
    int size = 0;
    int argumentPosition = 0;

    std::vector<std::string> ThursdayCommands = LoadVector();
    std::vector<std::string> commands;
    std::vector<std::string> pipeFirstCommands;
    std::vector<std::string> pipeSecondCommands;

    while(1) {
        std::cout << "Please enter: ";
        std::getline(std::cin, incomingInput);
        std::cout << "Output: " << std::endl;

        std::istringstream iss (incomingInput);
        while(std::getline(iss,input,' ')) {
            /*------------------------------------------------------------------------------*/
            size = input.size();
            /*------------------------------------------------------------------------------*/
            if (iss.tellg() == -1)
                lastItem = true;
            /*------------------------------------------------------------------------------*/
            if (input == ">") {
                operatorType = 2;
                operatorFound = true;
            } else if (input == "<") {
                operatorType = 3;
                operatorFound = true;
            } else if (input == "|") {
                operatorType = 4;
                operatorFound = true;
                pipeFirstCommands = commands;
                commands.clear();
            }   
            /*------------------------------------------------------------------------------*/
            if (input[size - 1] == ';') {
                input.erase(input.begin()+(input.size() - 1), input.end());	
                semiColonFound = true;
            } else {
                stringFind = input.find(';');
                if (stringFind != std::string::npos) {
                    if (foundDoubleQuote != true && foundSingleQuote != true) {
                        std::cout << "There was some big mistake with your commands." << std::endl;
                        break;
                    }
                }
            }
            /*------------------------------------------------------------------------------*/
            if (input[0] == 39 || input[size - 1] == 39) {
                // input.erase(input.begin()+(input.size() - 1), input.end());	
                if (foundSingleQuote == false) {
                    foundSingleQuote = true;
                } else {
                    foundSingleQuote = false;
                    singleQuote += input;
                    commands.push_back(singleQuote);
                    singleQuote = "";
                }
            } else {
                stringFind = input.find("'");
                if (stringFind != std::string::npos) {
                    std::cout << "Skipping these commands" << std::endl;
                    errorFound = true;
                    if (foundSingleQuote == false) {
                        foundSingleQuote = true;
                    } else {
                        foundSingleQuote = false;
                        singleQuote += input;
                        commands.push_back(singleQuote);
                        singleQuote = "";
                    }
                }
            }
            /*------------------------------------------------------------------------------*/
            if (input[0] == '"' || input[size - 1] == '"') {
                // std::cout << "HEre" << std::endl;
                // input.erase(input.begin()+(input.size() - 1), input.end());	
                if (foundDoubleQuote == false) {
                    foundDoubleQuote = true;
                } else {
                    foundDoubleQuote = false;
                    singleQuote += input;
                    commands.push_back(singleQuote);
                    singleQuote = "";
                }
            } else {
                stringFind = input.find('"');
                if (stringFind != std::string::npos) {
                    std::cout << "Skipping these commands" << std::endl;
                    errorFound = true;
                    if (foundDoubleQuote == false) {
                        foundDoubleQuote = true;
                    } else {
                        foundDoubleQuote = false;
                        singleQuote += input;
                        commands.push_back(singleQuote);
                        singleQuote = "";
                    }
                }
            }
            /*------------------------------------------------------------------------------*/
            if (argumentPosition == 0) {
                for (int a = 0; a < ThursdayCommands.size(); a++) {
                    if (ThursdayCommands[a] == input)
                        commandSwitch = true;													
                }
            }
            /*------------------------------------------------------------------------------*/
            if (operatorFound == true) {
                operatorFound = false;
                if (operatorType != 4) 
                    needNextArgument = true;
                else 
                    pipeWasFound = true;
            } else if (needNextArgument == true) {
                needNextArgument = false;
                if (operatorType == 2) {
                    if ((semiColonFound == true || lastItem == true) && errorFound == false) {
                        outputPath = input;
                        std::cout << "Standard Out" << std::endl;
                        for (int i = 0; i < commands.size(); i++)
                            std::cout << i << ": " << commands[i] << std::endl;
                        std::cout << "File: " << outputPath << std::endl;
                        //Make the stdout Call
                        //leading commands are in the vector.
                        //The output file is in the string.
                    } else {
                        std::cout << "There was some error with the commands you were trying to give." << std::endl;
                    }
                } else if (operatorType == 3) {
                    if ((semiColonFound == true || lastItem == true) && errorFound == false) {
                        inputPath = input;
                        std::cout << "Standard In" << std::endl;
                        for (int i = 0; i < commands.size(); i++)
                            std::cout << i << ": " << commands[i] << std::endl;
                        std::cout << "File: " << inputPath << std::endl;
                        //Make the stdin Call
                        //leading commands are in the vector.
                        //The output file is in the string.
                    } else {
                        std::cout << "There was some error with the commands you were trying to give." << std::endl;
                    }
                }
                commands.clear();
                errorFound = false;
                foundDoubleQuote = false;
                foundSingleQuote = false;
                semiColonFound = false;
                lastItem = false;
                argumentPosition = 0;
            }  else if (semiColonFound == true || lastItem == true) {
                if (errorFound == false) {
                    commands.push_back(input);
                    if (pipeWasFound == true) {
                        pipeSecondCommands = commands;
                        commands.clear();
                        std::cout << "Pipe PT1:" << std::endl;
                        for (int i = 0; i < pipeFirstCommands.size(); i++)
                            std::cout << i << ": " << pipeFirstCommands[i] << std::endl;
                        std::cout << std::endl << "Pipe PT2:" << std::endl;
                        for (int i = 0; i < pipeSecondCommands.size(); i++)
                            std::cout << i << ": " << pipeSecondCommands[i] << std::endl;
                        // The first command and arguments are in the pipeFirstCommands vector.
                        // Everything else after the opeator are in the pipeSecondCommands vector.
                    } else {
                        if (commandSwitch == false) {
                            std::cout << "1 - Commands: " << std::endl;
                            for (int i = 0; i < commands.size(); i++)
                                std::cout << i << ": " << commands[i] << std::endl;
                            // SearchCommands(commandAndArguments, 1, envp);
                        } else if (commandSwitch == true) {
                            std::cout << "2 - Commands: " << std::endl;
                            for (int i = 0; i < commands.size(); i++)
                                std::cout << i << ": " << commands[i] << std::endl;
                            // SearchCommands(commandAndArguments, 0, envp);
                        }
                    }
                }
                commands.clear();
                errorFound = false;
                foundDoubleQuote = false;
                foundSingleQuote = false;
                semiColonFound = false;
                lastItem = false;
                argumentPosition = 0;
            } else {
                argumentPosition++;
                if (foundSingleQuote == false && foundDoubleQuote == false) {
                    commands.push_back(input);
                } else if (foundSingleQuote == true) {
                    singleQuote += input;
                    singleQuote += " ";
                } else if (foundDoubleQuote == true) {
                    doubleQuote += input;
                    doubleQuote += " ";
                }
            }
        }
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