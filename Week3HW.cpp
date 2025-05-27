/**
*  CSOPESY_OS_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
*  CSOPESY - S19 (Group 10)
*  Members:
*          - MARTIN, ELAINE RIZ COCAL
*          - ORDINARIO, KARL ANDREI LARITA
*          - SAYO, TRISHA ALISSANDRA
*
*  Submitted to: Mr. DE LA CRUZ, REN TRISTAN A.
**/


using namespace std;
#define _HAS_STD_BYTE 0


#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <vector>


const string YEL = "\033[0;33m";
const string GRN = "\033[0;32m";
const string RED = "\033[0;31m";
const string WHT = "\033[0m";


class Process {
public:
    string name;
    int currentLine;
    int totalLines;
    string creationTime;

    Process(string n) {
        name = n;
        currentLine = rand() % 100 + 1;
        totalLines = 100;
        creationTime = getCurrentTimestamp();
    }

    void drawConsole() {
        system("cls");  
        cout << GRN << "== Screen Session ==\n" << WHT;
        cout << "Process Name   : " << name << "\n";
        cout << "Instruction    : " << currentLine << " / " << totalLines << "\n";
        cout << "Created On     : " << creationTime << "\n";
    }

    const string& getName() const { return name; }

private:
    string getCurrentTimestamp() {
        time_t now = time(0);
        tm localtm;
        localtime_s(&localtm, &now);
        stringstream ss;
        ss << put_time(&localtm, "%m/%d/%Y, %I:%M:%S %p");
        return ss.str();
    }
};

namespace ProcessManager {
    void runScreenLoop(Process& process);
    Process* findProcess(const string& name);

    vector<Process> processes;

    void createProcess(const string& name) {
        if (findProcess(name) != nullptr) {
            cout << RED << "Process '" << name << "' already exists...\n" << WHT;
            Sleep(1500);
            system("cls");
            return;
        }
        Process newProcess(name);
        processes.push_back(newProcess);
        //newProcess.drawConsole();
        runScreenLoop(newProcess);
    }
    Process* findProcess(const string& name) {
        for (auto& process : processes) {
            if (process.getName() == name) {
                return &process;
            }
        }
        return nullptr;
    }
    void redrawProcess(const string& name) {
        if (Process* process = findProcess(name)) {
            runScreenLoop(*process);
        }
        else {
            cout << RED << "Process not found! Cannot redraw\n" << WHT;
        }
    }

    void runScreenLoop(Process& process) {
        string input;
        while (true) {
            process.drawConsole();
            cout << "\nEnter command : ";
            getline(cin, input);
            if (input == "exit") break;
            cout << RED << "Unknown command. Type 'exit' to return.\n" << WHT;
            Sleep(1500);
        }
        system("cls");
    }
}

void header() {
    cout << " ,-----. ,---.   ,-----. ,------. ,------. ,---.,--.   ,--. \n";
    cout << "'  .--./'   .-' '  .-.  '|  .--. '|  .---''   .-'\\  `.'  /  \n";
    cout << "|  |    `.  `-. |  | |  ||  '--' ||  `--, `.  `-. '.    /   \n";
    cout << "'  '--'\\.-'    |'  '-'  '|  | --' |  `---..-'    |  |  |    \n";
    cout << " `-----'`-----'  `-----' `--'     `------'`-----'   `--'     \n";
    cout << "                                                            \n";

    cout << GRN << "\tHello, Welcome to CSOPESY commandline!\n";
    cout << YEL << "\tType 'exit' to quit, 'clear' to clear the screen\n\n" << WHT;
}

void newLine() {
    cout << "\n";
}

void help() {
    cout << "List of commands:\n";
    cout << "initialize     - Initializes the program\n";
    cout << "screen         - Displays the screen\n";
    cout << "scheduler-test - Tests the scheduler\n";
    cout << "scheduler-stop - Stops the scheduler\n";
    cout << "report-util    - Generates a report\n";
    cout << "clear          - Clears the screen\n";
    cout << "exit           - Exits the program\n";
}

void print_confirmation(string command) 
{
    cout << GRN << "\n\t" + command + " command recognized. Doing something..." << WHT;
    Sleep(2000);

    if (command == "initialize" || command == "screen" || command == "scheduler-test"
        || command == "scheduler-stop" || command == "report-util")
    {
        system("cls");
    }
}

int main()
{
    string command = "";

    while (command != "exit") {
        header();
        //newLine();
        //help();
        cout << "Enter command: ";
        getline(cin, command);

        // insert code that converts command variable to lowercase
        for (int i = 0; i < command.length(); i++) {
            command[i] = tolower(command[i]);
        }

        if (command == "initialize") {
            print_confirmation(command);
            newLine();
        }
        else if (command.rfind("screen -s ", 0) == 0) {
            string name = command.substr(10);
            if (!name.empty())
                ProcessManager::createProcess(name);
            else
                cout << RED << "Process name required.\n" << WHT;
        }
        else if (command.rfind("screen -r ", 0) == 0)
        {
            string name = command.substr(10);
            if (!name.empty())
                ProcessManager::redrawProcess(name);
            else
                cout << RED << "Process name required.\n" << WHT;
        }
        else if (command == "scheduler-test") {
            print_confirmation(command);
            newLine();
        }
        else if (command == "scheduler-stop") {
            print_confirmation(command);
            newLine();
        }
        else if (command == "report-util") {
            print_confirmation(command);
            newLine();
        }
        else if (command == "clear") {
            system("cls");
            header();
        }
        else if (command != "exit") {
            cout << RED <<  "'" << command << "' command not recognized." << WHT;
            Sleep(2000);
            system("cls");
            newLine();
        }
    }

    return 0;
}
