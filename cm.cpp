#include <iostream>
#include <vector>
#include <functional>
#include <string>

class Command
{
    std::string m_id;
    bool m_argsReq;
    int m_minArgs;
    int m_maxArgs;
    int argc;
    std::vector<std::string> m_argv{};

public:
    Command (std::string id, bool argsReq, int min, int max) 
        : m_id {id}, m_argsReq {argsReq}, m_minArgs {min}, m_maxArgs {max}
    {
        argc = 0;        
    }

    void addArgv (std::vector<std::string> argArr)
    {
        m_argv.resize(argArr.size());
        m_argv = argArr;
        argc = static_cast<int>(m_argv.size());
    }

    bool checkIfValid ()
    {
        //  Makes sure minArgs <= argc <= maxArgs
        if (m_minArgs <= argc && m_maxArgs >= argc) return true;
        else return false;
    }

    std::string getID() {return m_id;}

    void addArg (std::string arg)
    {
        m_argv.push_back(arg);
    }
};

class CommandManager
{
private:
    std::vector<std::reference_wrapper<Command>> m_commandArr{};    //Holds all commands
    std::vector<std::reference_wrapper<Command>> m_execArr{};       //Holds commands to be executed
    std::vector<std::string> m_argv{};
    int m_argc{};
    
public:
    CommandManager () = default;

    void addCommand (Command newCom)
    {
        m_commandArr.push_back(newCom);
    }

    void parse (int argc, char* argv[])
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

        //  Match locations in comLocs with commands in m_commandArr
        for (int j{0}; j < comLocs.size(); ++j)
        {
            int index = comLocs[j];
            for (auto com : m_commandArr)
            {
                if (m_argv[index] == com.get().getID())
                {
                    //  Give command relevant arguments
                    //  Create command w/ args in m_execArr? Check # of parameters first
                    Command tempCom { com.get()};
                    std::vector<std::string> givenArgs(0);
                    int count {1};
                    while(m_argv.size() > (index + count))
                    {
                        if (m_argv[index+count].substr(0,2) != "--")
                        {
                            // Can optimize by adding directly to tempCom with .addArg
                            givenArgs.push_back(m_argv[index + count++]);
                        }
                        else ++count;
                    }
                    
                    tempCom.addArgv(givenArgs);
                    
                    if (tempCom.checkIfValid())
                    {
                        m_execArr.push_back(tempCom);
                    }
                    else std::cout << "Command check failed\n";

                }
            }
        }
    }




};

