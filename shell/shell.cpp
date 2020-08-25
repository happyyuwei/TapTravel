#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <map>

#include "../container/string.h"

/**
 * 读取命令行
 */
TAP::String readCmd()
{
    //获取当前工作目录
    char *pwd = get_current_dir_name();
    // std::cout << "Please input a command:\n";
    std::cout << "myshell:" << pwd << ">";
    // //read the line
    char buffer[1024];
    std::cin.getline(buffer, 1024);

    TAP::String inputLine = buffer;
    // std::string inputLine;
    // inputLine = buffer;
    //看get_current_dir_name() 定义是maloc的地址，不知道是不是需要free
    free(pwd);
    return inputLine;
}

/**
 * 解析命令
 */
void parseArgs(std::vector<std::string> cmdList, char *cmd, char *args[])
{
    cmdList[0].copy(cmd, cmdList[0].length(), 0);
    for (int i = 0; i < cmdList.size(); i++)
    {
        //Such a rubbish code, but i don't know how do anyway.
        args[i] = (char *)cmdList[i].c_str();
    }
}

/**
 * 执行命令，调用 execl(/bin/sh -c "cmd") 即可，连重定向的实现都省了
 */
void execute(const char *cmd)
{
    int pid = fork();
    //子进程中pid=0
    if (pid == 0)
    {
        //creake a new progress and execute
        // std::cout << "results:\n ";
        //执行
        //不想弄了，简单点， /bin/sh -c "cmd" 即可，连重定向的实现都省了
        execl("/bin/sh", "sh", "-c", cmd, (const char *)0);
        // execle
        //use ps, filter the jobs PID,check the start time.
        //report error
        perror(("Error. Unable to execute " + std::string(cmd)).c_str());
        exit(EXIT_FAILURE);
    }
    //父进程会返回子进程的id
    else if (pid > 0)
    {
        int status;
        // std::cout << "Waiting for result, pid=" << pid << std::endl;
        pid = wait(&status);
        std::cout << "\nProcess " << pid << " ends with " << status << " status" << std::endl;
        std::cout << "=================================================\n";
    }
    //pid<0则创建失败
    else
    {
        std::cout << "An error occured when fork a child process.\n";
    }
}

//替换变量中的 $
//糟糕的实现
// void replaceVariable(std::vector<TAP::String> &argList, std::vector<TAP::String> &variableList)
// {
//     for (int i = 0; i < argList.size(); i++)
//     {
//         if (argList[i].contains("$"))
//         {
//             for (int j = 0; j < variableList.size(); j++)
//             {
//                 std::vector<TAP::String> kv = variableList[j].split("=");
//                 if (("$" + kv[0]).equals(argList[i].c_str()))
//                 {
//                     // argList.
//                 }
//             }
//         }
//     }
// }

int main()
{

    //环境变量列表
    std::vector<TAP::String> variableList;
    while (1)
    {
        //读取命令
        TAP::String inputLine = readCmd();
        // until the command is the word exit
        //its better to use !, but i can't see it clearly.
        //用感叹号总有一种不相等的错觉
        if (inputLine.equals("exit"))
        {
            std::cout << "Bye.\n";
            exit(EXIT_SUCCESS);
        }

        //分割
        std::vector<TAP::String> argList = inputLine.split(" ");

        // replaceVariable(argList, variableList);
        // //重新拼回line
        // TAP::String cmdLine = "";
        // for (int i = 0; i < argList.size(); i++)
        // {
        //     cmdLine.append(argList[i]);
        // }
        // std::cout << cmdLine << std::endl;

        // //分配字符串空间
        // //cmd空间
        // char cmd[64]{};
        // //args空间
        // char *args[cmdList.size() + 1]{};

        //解析
        // parseArgs(cmdList, cmd, args);

        //如果是cd命令，则不调用shell,
        if (argList[0].equals("cd"))
        {
            //修改当前路径
            chdir(argList[1].c_str());
        }
        else if (argList[0].contains("="))
        {
            //保存
            variableList.push_back(argList[0]);
            // a, 1
            //echo $a echo 1
        }
        else
        {
            //执行
            execute(inputLine.c_str());
        }
    }
}
