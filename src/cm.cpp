#include "cm.h"

Command::Command (std::string id, bool argsReq, int max, int min) 
    : m_id {id}, m_argsReq {argsReq}, m_minArgs {min}, m_maxArgs {max}
{
    argc = 0;        
}

void Command::addArgv (std::vector<std::string> argArr)
{
    m_argv.resize(argArr.size());
    m_argv = argArr;
    argc = static_cast<int>(m_argv.size());
}

bool Command::checkIfValid ()
{
    //  Makes sure minArgs <= argc <= maxArgs
    if (m_argsReq && m_minArgs <= argc && m_maxArgs >= argc) return true;
    else if (!m_argsReq && m_minArgs == 0) return true;
    else return false;
}

std::string Command::getID() const {return m_id;}

void Command::addArg (std::string arg) { m_argv.push_back(arg); }
std::string Command::getArg (int index) { return m_argv[index]; }
int Command::getArgCount () { return argc; }

int Command::getArgAsInt (int index)
{
    //  Add exception handling
    return std::stoi(m_argv[index]);
}


//CommandManager::CommandManager= default;

void CommandManager::addCommand (std::string id, bool argsReq, int maxArgs, int minArgs)
{
    //m_commandArr.push_back(newCom);
    m_commandArr.push_back(Command {id, argsReq, maxArgs, minArgs});
}

void CommandManager::parse (int argc, char* argv[])
{
    m_argc = argc-1;
    
    for (int i {1}; i < argc; ++i)
    {
        m_argv.push_back(std::string {argv[i]});
    }
    
    std::vector<int> comLocs(0);    //  Vector of indecies for commands in m_argv
    for (int ii{0}; ii < m_argc; ++ii)
    {
        if (m_argv[ii].substr(0,2) == "--")
            comLocs.push_back(ii);
    }

    comLocs.push_back(static_cast<int>(m_argv.size())); //Add length of m_argv for loop adding parameterer o commands

    //  Match locations in comLocs with commands in m_commandArr
    for (int j{0}; j <= comLocs.size() - 1; ++j)
    {
        int index {comLocs[j]};
        for (auto com : m_commandArr)
        {
            if (m_argv[index] == com.getID())
            {
                //  Give command relevant arguments
                //  Create command w/ args in m_execArr? Check # of parameters first
                Command tempCom {com};
                std::vector<std::string> givenArgs(0);
                for(int jj{index + 1}; jj < comLocs[j+1]; ++jj)
                {
                    givenArgs.push_back(m_argv[jj]);
                }
                
                tempCom.addArgv(givenArgs);
                
                if (tempCom.checkIfValid())
                {
                    m_execArr.push_back(tempCom);
                }
                else std::cout << "Command check failed\n";
                break;
            }
        }
    }
}

std::vector<Command> CommandManager::getExecutables ()
{
    return m_execArr;
}


