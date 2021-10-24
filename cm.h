#ifndef CM_H
#define CM_H

#include <vector>
#include <string>
#include <iostream>
#include <functional>

class Command
{
private:
    std::string m_id;
    bool m_argsReq;
    int m_minArgs;
    int m_maxArgs;
    int argc;
    std::vector<std::string> m_argv{};
public:
    Command (std::string id, bool argsReq, int max, int min);
    void addArgv (std::vector<std::string> argArr);
    bool checkIfValid ();
    std::string getID() const;
    void addArg (std::string arg);
    std::string getArg (int index);
    int getArgCount ();
    int getArgAsInt (int index);

};

class CommandManager
{
private:
    std::vector<Command> m_commandArr{};
    std::vector<Command> m_execArr{};       //Holds commands to be executed
    std::vector<std::string> m_argv{};
    int m_argc{};
public:
    CommandManager () = default;
    void addCommand (std::string id, bool argsReq, int maxArgs, int minArgs);
    void parse (int argc, char* argv[]);
    std::vector<Command> getExecutables ();

};


#endif