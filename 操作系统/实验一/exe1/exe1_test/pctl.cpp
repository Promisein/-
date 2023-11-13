#include "pctl.h"

/*
父进程每隔 3 秒重复建立两个子进程，首先创建的子进程让其执行 ls 命令，
之后创建的子进程让其执行 ps 命令，
并控制 ps 命令总在 ls 命令之前执行。
*/
int main(int argc, char *argv[])
{
    int pid1, pid2; //存放子进程号

    int status1;                             //存放子进程1返回状态
    int status2;                             //存放子进程2返回状态
    char *args1[] = {"/bin/ls", NULL, NULL}; //首先创建的子进程执行 ls 命令
    char *args2[] = {"/bin/ps", NULL, NULL}; //后创建的子进程执行 ps 命令

    unsigned int number = 5;
    while (number != 0)
    {
        printf("Start a new Program!\n");
        signal(SIGINT, (sighandler_t)sigcat); //注册一个本进程处理键盘中断的函数

        perror("SIGINT");

        pid1 = fork(); //建立子进程1

        if (pid1 < 0) // 建立子进程失败
        {
            printf("Create child Process1 fail!\n");
            exit(EXIT_FAILURE);
        }

        else
        {
            if (pid1 == 0)
            {
                printf("I am Child1 process %d\nMy father is %d\n", getpid(), getppid());

                printf("pasue child process one : %d\n", getpid());

                pause();
                printf("执行的命令: ");
                for (int i = 0; args1[i] != NULL; i++)
                {
                    printf("%s ", args1[i]);
                }
                printf("\n");

                //装入并执行新的程序
                status1 = execve(args1[0], args1, NULL);
            }
            else //父进程执行代码段
            {

                printf("I am father process %d\n", getpid());

                pid2 = fork();
                if (pid2 < 0)
                {
                    printf("Create child Process2 fail!\n");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    if (pid2 == 0)
                    {
                        printf("I am Child2 process %d\nMy father is %d\n", getpid(), getppid());

                        printf("执行的命令: ");
                        for (int i = 0; args2[i] != NULL; i++)
                        {
                            printf("%s ", args2[i]);
                        }
                        printf("\n");

                        //装入并执行新的程序
                        status2 = execve(args2[0], args2, NULL);
                    }
                    else
                    {
                        printf("%d Waiting for child done.\n\n", getpid());
                        waitpid(pid2, &status2, 0); //等待子进程结束
                        printf("\nMy child2 exit! status = %d\n\n", status2);

                        kill(pid1, SIGINT);
                        // sleep(3);
                    }
                }

                waitpid(pid1, &status1, 0); //等待子进程结束
                printf("\nMy child1 exit! status = %d\n\n", status1);

                wait(NULL);
                printf("ALL process have completed\n\n\n");
                sleep(3);
            }
        }
        number--;
    }
    return EXIT_SUCCESS;
}