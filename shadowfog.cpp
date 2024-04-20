#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

void installDependencies();
void startTorService();
void checkTorStatus();
void executeWithProxychains(const std::string& command);
void modifyProxyChainsConfig(const std::string &mode, int chain_len);
void showHelp();
void showBanner();

#include <cstdlib>

/*void installDependencies() {
    // Update packages and later install tor and proxychains 
    int status = system("sudo apt update && sudo apt install -y tor proxychains");

    if (status != 0) {
        // Error handler
        std::cerr << "Error: Failed to install Tor and Proxychains." << std::endl;
        return;
    }

    // Configure execution permissions for the proxychains library 
    status = system("sudo chmod +x /usr/lib/x86_64-linux-gnu/libproxychains.so.3");

    if (status != 0) {
        // Error handler
        std::cerr << "Error: Failed to set execute permissions on Proxychains library." << std::endl;
    } else {
        std::cout << "Dependencies installed and configured successfully." << std::endl;
    }
}*/

void installDependencies() {
    // Update packages and later install tor and proxychains 
    int status = system("sudo apt update && sudo apt install -y tor proxychains");

    if (status != 0) {
        // Error handler
        std::cerr << "Error: Failed to install Tor and Proxychains." << std::endl;
        return;
    }

    std::cout << "Dependencies installed successfully." << std::endl;
}


void startTorService() { // starts tor service
    system("sudo systemctl start tor");
}

void stopTorService() { // stops tor service
    system("sudo systemctl stop tor");
}

void checkTorStatus() { // checks tor status
    system("sudo systemctl status tor");
}

/*void executeWithProxychains(const std::string& command) { // executes a program with proxychains
    std::string fullCommand = "proxychains4 " + command;
    system(fullCommand.c_str());
}*/

void executeWithProxychains(const std::string& command) {
    // Gets the name of the original user that started the session with sudo
    char* sudo_user = getenv("SUDO_USER");

    // Builds the full command considering that the normal user was get
    std::string fullCommand;
    if (sudo_user) {
        // Executes the command as normal user to avoid errors with x11 and permissions
        fullCommand = "sudo -u " + std::string(sudo_user) + " proxychains " + command;
    } else {
        // If there isnt sudo user executes normally 
        fullCommand = "proxychains " + command;
    }

    // Executes the command
    int status = system(fullCommand.c_str());
    if (status != 0) {
        std::cerr << "Error executing command with proxychains: " << fullCommand << std::endl;
    }
}

// Modifies the proxychains conf file
void modifyProxyChainsConfig(const std::string& mode, int chain_len) {
    std::ifstream fileIn("/etc/proxychains.conf"); // open the conf file
    if (!fileIn.is_open()) { // error handler
        std::cerr << "Error: unable to open the conf file at /etc/proxychains.conf. Please check the dependencies or check if the file exists" << std::endl;
        return;
    }

    std::string line, content;
    bool dynamicSet = false, randomSet = false, socks5Set = false;

    while (getline(fileIn, line)) {
        if (line.substr(0, 6) == "socks4") { // verifies is there is a line that starts with socks4
            content += "#" + line + "\n"; // Coments the socks 4 127.0.0.1 9050 line
        } else if (line.find("strict_chain") != std::string::npos) { // verifies if there is a line that contains strict_chain
            content += "#strict_chain\n"; // Always will coment the line because we need to
        } else if (line.find("#dynamic_chain") != std::string::npos) { // verifies is the line is the one that sets the dynamic chain
            content += (mode == "dynamic" ? "dynamic_chain\n" : "#dynamic_chain\n"); // if the mode that the user want to set is dynamic will add dynamic without the comment character, if is not it will let it commented
            dynamicSet = mode == "dynamic"; // sets the mode in dynamic
        } else if (line.find("#random_chain") != std::string::npos) { // verifies the same with random chain
            content += (mode == "random" ? "random_chain\n" : "#random_chain\n"); // will do the same operation but with random chain
            randomSet = mode == "random"; // sets the mode in random
        } else if (line.find("#chain_len") != std::string::npos && randomSet) { // verifies if the line is the one who matches with chain len
            content += "chain_len=" + std::to_string(chain_len) + "\n"; // sets the amount of chains
        } else if (line.find("socks5 127.0.0.1 9050") != std::string::npos && line.substr(0, 1) != "#") { // verifies if the soscks5 line is added and is not commented
            // Lets the line as it is
            socks5Set = true;
            content += line + "\n";
        } else {
            content += line + "\n"; // Passes al lines without changes
        }
    }

    if (!socks5Set) { // If there is no socks5 line added will added
        content += "socks5 127.0.0.1 9050\n";
    }

    fileIn.close(); // closes the conf file

    std::ofstream fileOut("/etc/proxychains.conf.tmp", std::ios::trunc); // opens the tmp file
    if (!fileOut.is_open()) {
        std::cerr << "Error: unable to open the conf file at /etc/proxychains.conf.tmp for writing" << std::endl; // error handler
        return;
    }
    fileOut << content; // writes everything on the tmp file
    fileOut.close();

    system("mv /etc/proxychains.conf.tmp /etc/proxychains.conf"); // Replaces the tmp with the original
}

// Makes a copy of the original conf file, is a good practice to set a backup before you set the configuration
void copyOriginalConfig() {
    std::string destinationPath;
    std::cout << "Enter the path where you want to copy the original conf file as backup: "; // sets the path where will be copied the backup
    std::getline(std::cin, destinationPath);
    if (destinationPath.empty()) {
        std::cout << "Error: enter a valid path please...\n"; // error handler
        return;
    }

    std::string command = "cp /etc/proxychains.conf " + destinationPath; // builds full command
    if (system(command.c_str()) == 0) { // runs the command and verifies the return code
        std::cout << "Succesfully created a backup on: " << destinationPath << "\n"; // success
    } else {
        std::cerr << "Error creating the backup copy, check permissions and the path please...\n"; // error handler
    }
}

// Not implemented will never be able to show if proxychains is running
void showAnonimousIp() {
    system("proxychains curl https://icanhazip.com");
}

void showHelp() { // shows the usage 
    std::cout << "\nShadowFog usage =>\n\n"
            << "-configure\t\t Install and configure dependencies\n"
            << "-cporiginalconf\t\t Copy the original ProxyChains conf file as a backup\n"
            << "-runsrv\t\t\t Start the Tor service\n"
            << "-stopsrv\t\t Stop the Tor service\n"
            << "-status\t\t\t Check the status of the Tor service\n"
            << "-set [mode] [length]\t Set the Proxychains mode ('random' with length of 2 by default, 'dynamic')\n"
            << "-start [program]\t Execute a program with Proxychains\n"
            << "-help\t\t\t Show this help message\n"
            << "-exit\t\t\t Exit the program\n\n"
            << "-----------------------------------------------------------\n\n";
}

void showBanner() { // shows the banner of the program
    std::cout << "\n-----------------------------------------------------------\n";
    system("\nfiglet -f slant ShadowFog");
    std::cout << "          > Hide your trail in the dense fog... <\n";
    std::cout << "\n-----------------------------------------------------------";
    std::cout << "\n              [+] Coded By AbyssWatcher [+]\n";
}

void userInterface() { // handles the shell of the program and manages the calls depending on the input
    std::string input, command, mode;
    int chainLength;

    std::cout << "\nShadowFog ~ ";

    while (std::getline(std::cin, input)) {
        if (input == "-configure") {
            installDependencies();
        } else if (input == "-runsrv") {
            startTorService();
        } else if (input == "-stopsrv") {
            stopTorService();
        } else if (input == "-status") {
            checkTorStatus();
        } else if (input == "-help") {
            showHelp();
        } else if (input == "-exit") {
            std::cout << "\nSee you next time...\n\n";
            break;
        } else if (input.substr(0, 7) == "-start ") {
            command = input.substr(7);
            executeWithProxychains(command);
        } else if (input.substr(0, 5) == "-set ") {
            istringstream ss(input.substr(5));
            ss >> mode >> chainLength;
            modifyProxyChainsConfig(mode, chainLength);
        } else if (input == "-cporiginalconf") {
            copyOriginalConfig();
        } else {
            std::cout << "Unknown command. Type -help to see the availbale commands.\n";
        }
        std::cout << "\nShadowFog ~ ";
    }
}

int main() {
    showBanner();
    showHelp();
    userInterface();
    return 0;
}