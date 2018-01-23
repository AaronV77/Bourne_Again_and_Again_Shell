#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> LoadVector();

int main() {
    std::string incomingInput = "";
    std::string singleQuote = "";
    std::string doubleQuote = "";
    std::string input = "";
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
    bool skipTheCommandAdd = false;
    bool moreOperatorsFound = false;
    bool foundWhiteSpace = false;

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

        do {
            if (incomingInput[incomingInput.size() - 1] == 32) {
                incomingInput.erase(incomingInput.begin()+(incomingInput.size() - 1), incomingInput.end());
                foundWhiteSpace = true;
            } else {
                foundWhiteSpace = false;
            }
        } while (foundWhiteSpace == true);

        std::istringstream iss (incomingInput);                                                             // Prepare the incoming string
        while(std::getline(iss,input,' ')) {                                                                // Loop through the string by tokenizing by space.
            /*------------------------------------------------------------------------------*/
            size = input.size();                                                                            // Get the length of the token.
            /*------------------------------------------------------------------------------*/
            if (iss.tellg() == -1)                                                                          // Check to see if the next token is the last.
                lastItem = true;                                                                            // If so then set our bool statment to true.
            /*------------------------------------------------------------------------------*/
            if (foundDoubleQuote == false && foundSingleQuote == false) {
                if (input == ">") {                                                                         // Check to see if the token is an operator.
                    if (operatorType != 0)
                        errorFound = true;
                    operatorType = 2;                                                                           //                                                                         
                    operatorFound = true;                                                                       //
                } else if (input == "<") {                                                                  //
                    if (operatorType != 0)
                        errorFound = true;
                    operatorType = 3;                                                                           //
                    operatorFound = true;                                                                       //
                } else if (input == "|") {                                                                  //
                    if (pipeWasFound == true) {
                        pipeSecondCommands = commands;
                        std::cout << "Pipe PT3:" << std::endl;
                        for (int i = 0; i < pipeFirstCommands.size(); i++)
                            std::cout << i << ": " << pipeFirstCommands[i] << std::endl;
                    
                        std::cout << std::endl << "Pipe PT4:" << std::endl;
                        for (int i = 0; i < pipeSecondCommands.size(); i++)
                            std::cout << i << ": " << pipeSecondCommands[i] << std::endl;
                        std::cout << std::endl;
                        // Will have to make a Pipe call from here.
                        pipeFirstCommands.clear();
                        pipeFirstCommands = pipeSecondCommands;
                        pipeSecondCommands.clear();
                        commands.clear();
                        moreOperatorsFound = true;
                        operatorFound = true;
                    } else {
                        if (operatorType != 0)
                            errorFound = true;
                        operatorType = 4;                                                                       //
                        operatorFound = true;                                                                   //
                        pipeFirstCommands = commands;                                                           //
                        commands.clear();                                                                       //
                    }
                }   
            }
            /*------------------------------------------------------------------------------*/
            if (input[size - 1] == ';') {                                                                   //
                input.erase(input.begin()+(input.size() - 1), input.end());	                                //
                semiColonFound = true;                                                                      //
            } else {                                                                                        //
                stringFind = input.find(';');                                                               //
                if (stringFind != std::string::npos) {                                                      //
                    if (foundDoubleQuote != true && foundSingleQuote != true) {                             //
                        std::cout << "There was some big mistake with your commands." << std::endl;         //
                        break;                                                                              //
                    }
                }
            }
            /*------------------------------------------------------------------------------*/
            if (foundDoubleQuote == false) {                                                                //
                if (input[0] == 39 || input[size - 1] == 39) {                                              //
                    if (foundSingleQuote == false) {                                                        //
                        foundSingleQuote = true;                                                            //
                    } else {                                                                                //
                        foundSingleQuote = false;                                                           //
                        skipTheCommandAdd = true;                                                           //
                        singleQuote += input;                                                               //
                        commands.push_back(singleQuote);                                                    //
                        singleQuote = "";                                                                   //
                    }
                } else {                                                                                    //
                    stringFind = input.find("'");                                                           //
                    if (stringFind != std::string::npos) {                                                  //
                        errorFound = true;                                                                  //
                        if (foundSingleQuote == false) {                                                    //
                            foundSingleQuote = true;                                                        //
                        } else {                                                                            //
                            foundSingleQuote = false;                                                       //
                            singleQuote = "";                                                               //
                        }
                    }
                }
            }
            /*------------------------------------------------------------------------------*/
            if (foundSingleQuote == false) {                                                                //
                if (input[0] == '"' || input[size - 1] == '"') {                                            //
                    if (foundDoubleQuote == false) {                                                        //
                        foundDoubleQuote = true;                                                            //
                    } else {                                                                                //
                        foundDoubleQuote = false;                                                           //
                        skipTheCommandAdd = true;                                                           //
                        doubleQuote += input;                                                               //
                        commands.push_back(doubleQuote);                                                    //
                        doubleQuote = "";                                                                   //
                    }
                } else {                                                                                    //
                    stringFind = input.find('"');                                                           //
                    if (stringFind != std::string::npos) {                                                  //
                        errorFound = true;                                                                  //
                        if (foundDoubleQuote == false) {                                                    //
                            foundDoubleQuote = true;                                                        //
                        } else {                                                                            //
                            foundDoubleQuote = false;                                                       //
                            doubleQuote = "";                                                               //
                        }
                    }
                }
            }
            /*------------------------------------------------------------------------------*/
            if (argumentPosition == 0) {                                                                    //
                for (int a = 0; a < ThursdayCommands.size(); a++) {                                         //
                    if (ThursdayCommands[a] == input)                                                       //
                        commandSwitch = true;	                                                            //												
                }
            }
            /*------------------------------------------------------------------------------*/
            if (errorFound == false) {
                if (operatorFound == true) {                                                                    //
                    operatorFound = false;                                                                      //
                    if (operatorType != 4)                                                                      //
                        needNextArgument = true;                                                                //
                    else                                                                                        //
                        pipeWasFound = true;                                                                    //
                } else if (needNextArgument == true) {                                                          //
                    needNextArgument = false;                                                                   //
                    if (operatorType == 2) {                                                                    //
                        if ((semiColonFound == true || lastItem == true) && errorFound == false) {              //
                            outputPath = input;                                                                 //
                            std::cout << "Standard Out" << std::endl;
                            for (int i = 0; i < commands.size(); i++)
                                std::cout << i << ": " << commands[i] << std::endl;
                            std::cout << "File: " << outputPath << std::endl;
                            //Make the stdout Call
                            //leading commands are in the vector.
                            //The output file is in the string.
                        } else {                                                                                //
                            std::cout << "There was some error with the commands you were trying to give.1" << std::endl;
                        }
                    } else if (operatorType == 3) {                                                             //
                        if ((semiColonFound == true || lastItem == true) && errorFound == false) {              //
                            inputPath = input;                                                                  //
                            std::cout << "Standard In" << std::endl;
                            for (int i = 0; i < commands.size(); i++)
                                std::cout << i << ": " << commands[i] << std::endl;
                            std::cout << "File: " << inputPath << std::endl;
                            //Make the stdin Call
                            //leading commands are in the vector.
                            //The output file is in the string.
                        } else {                                                                                //
                            std::cout << "There was some error with the commands you were trying to give.2" << std::endl;
                        }
                    }
                    singleQuote = "";
                    doubleQuote = "";
                    outputPath = "";
                    inputPath = "";
                    foundSingleQuote = false;
                    foundDoubleQuote = false;
                    needNextArgument = false;
                    operatorFound = false;
                    semiColonFound = false;
                    lastItem = false;
                    commandSwitch = false;
                    errorFound = false;
                    skipTheCommandAdd = false;
                    moreOperatorsFound = false;
                    commands.clear();
                    operatorType = 0;
                    argumentPosition = 0;
                } else if (pipeWasFound == true && lastItem == true) {                                          //
                    if (errorFound == false && foundDoubleQuote == false && foundSingleQuote == false) {        //
                        if (skipTheCommandAdd == false)                                                         //
                            commands.push_back(input);                                                          //
                        
                        pipeSecondCommands = commands;                                                          //
                        std::cout << "Pipe PT1:" << std::endl;
                        for (int i = 0; i < pipeFirstCommands.size(); i++)
                            std::cout << i << ": " << pipeFirstCommands[i] << std::endl;
                    
                        std::cout << std::endl << "Pipe PT2:" << std::endl;
                        for (int i = 0; i < pipeSecondCommands.size(); i++)
                            std::cout << i << ": " << pipeSecondCommands[i] << std::endl;
                        // The first command and arguments are in the pipeFirstCommands vector.
                        // Everything else after the opeator are in the pipeSecondCommands vector.
                    } else {                                                                                    //
                        std::cout << "Sorry - there was an error with the commands that you had entered." << std::endl;
                    }
                    commands.clear();
                    pipeFirstCommands.clear();
                    pipeSecondCommands.clear();
                    pipeWasFound = false;
                    lastItem = false;
                    errorFound = false;
                    operatorFound = false;
                    foundDoubleQuote = false;
                    foundSingleQuote = false;
                    skipTheCommandAdd = false;
                    commandSwitch = false;
                    argumentPosition = 0;
                    operatorType = 0;
                    singleQuote = "";
                    doubleQuote ="";
                } else if (semiColonFound == true || lastItem == true) {                                        //
                    if (errorFound == false && foundDoubleQuote == false && foundSingleQuote == false) {        //
                        if (skipTheCommandAdd == false)                                                         //
                            commands.push_back(input);                                                          //

                        if (commandSwitch == false) {                                                           //
                            std::cout << "1 - Commands: " << std::endl;
                            for (int i = 0; i < commands.size(); i++)
                                std::cout << i << ": " << commands[i] << std::endl;
                            // SearchCommands(commandAndArguments, 1, envp);
                        } else if (commandSwitch == true) {                                                     //
                            std::cout << "2 - Commands: " << std::endl;
                            for (int i = 0; i < commands.size(); i++)
                                std::cout << i << ": " << commands[i] << std::endl;
                            // SearchCommands(commandAndArguments, 0, envp);
                        }
                    } else {                                                                                    //
                        std::cout << "Sorry - there was an error with the commands that you had entered." << std::endl;
                    } 
                    commands.clear();
                    semiColonFound = false;
                    lastItem = false;
                    errorFound = false;
                    foundSingleQuote = false;
                    foundDoubleQuote = false;
                    skipTheCommandAdd = false;
                    commandSwitch = false;    
                    argumentPosition = 0;  
                    singleQuote = "";
                    doubleQuote = "";        
                } else {                                                                                        //
                    argumentPosition++;                                                                         //
                    if (foundSingleQuote == false && foundDoubleQuote == false && operatorFound == false) {     //
                        commands.push_back(input);                                                              //
                    } else if (foundSingleQuote == true) {                                                      //
                        singleQuote += input;                                                                   //
                        singleQuote += " ";                                                                     //
                    } else if (foundDoubleQuote == true) {                                                      //
                        doubleQuote += input;                                                                   //
                        doubleQuote += " ";                                                                     //
                    }
                }
            } else {
                std::cout << "Sorry there was error some where!" << std::endl;
                break;
            }
        }
        singleQuote = "";
        doubleQuote = "";
        outputPath = "";
        inputPath = "";
        foundSingleQuote = false;
        foundDoubleQuote = false;
        needNextArgument = false;
        pipeWasFound = false;
        operatorFound = false;
        semiColonFound = false;
        lastItem = false;
        commandSwitch = false;
        errorFound = false;
        skipTheCommandAdd = false;
        moreOperatorsFound = false;
        foundWhiteSpace = false;
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