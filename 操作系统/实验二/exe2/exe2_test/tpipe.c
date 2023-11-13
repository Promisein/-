#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

/*
设有二元函数 f(x,y) = f(x) + f(y)
其中：
• f(x)=1 (x=1)

• f(x) = f(x-1) * x (x >1)

• f(y)=1 (y=1,2)

• f(y) = f(y-1) + f(y-2) (y> 2)

请基于无名管道，利用 pthread 线程库编程建立 3 个并发协作线程，它们分别
完成 f(x,y)、f(x)、f(y)
*/

int task1(int x) //线程 f(x) 执行函数原型
{
    if (x <= 0)
    {
        printf("x must > 0 !\n");
        return 0;
    }
    if (x == 1)
    {
        return 1;
    }
    else
    {
        if (x > 1)
        {
            return task1(x - 1) * x;
        }
    }
}
int task2(int y) //线程 f(y) 执行函数原型
{
    if (y <= 0)
    {
        printf("y must > 0 !\n");
        return 0;
    }
    if (y == 1 || y == 2)
    {
        return 1;
    }
    else
    {
        if (y > 2)
        {
            return task2(y - 1) + task2(y - 2);
        }
    }
}
int task3(int fx, int fy) //线程 f(x, y) 执行函数原型
{
    return fx + fy;
}

// 建立两个子进程分别执行f(x),和f(y)，然后让父亲进程执行f(x, y)
// 然后分别建立俩个管道，从子进程中向父进程传递参数

int pipe1[2], pipe2[2]; //存放第2个无名管道标号

pthread_t thrd1, thrd2, thrd3; //存放第3个线程标识

int main()
{
    printf("hello world\n");
    //使用 pipe()系统调用建立两个无名管道。建立不成功程序退出，执行终止

    int x, y;
    printf("请输入x的值: ");
    scanf("%d", &x);
    printf("请输入y的值: ");
    scanf("%d", &y);

    if (x <= 0 || y <= 0)
    {
        printf("x or y must > 0 !\n");
        exit(EXIT_FAILURE);
    }
    int status1, status2;
    if (pipe(pipe1) < 0)
    {

        perror("pipe not create");

        exit(EXIT_FAILURE);
    }

    if (pipe(pipe2) < 0)
    {

        perror("pipe not create");

        exit(EXIT_FAILURE);
    }

    int pid1 = fork();
    if (pid1 < 0)
    {
        perror("process not create");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (pid1 == 0) // 子进程执行f(x)
        {
            close(pipe1[0]); // 子进程从管道1的1端进行写数据

            int result_x = task1(x);

            printf("f(x) = %d\n", result_x);
            printf("child %d write : %d\n", getpid(), task1(x));

            write(pipe1[1], &result_x, sizeof(int));

            // 写完成后,关闭管道
            close(pipe1[1]);
        }
        else
        {
            // 执行父进程

            waitpid(pid1, &status1, 0); // 等待子进程1结束

            int pid2 = fork(); //建立子进程2

            if (pid2 < 0)
            {
                perror("process not create");
                exit(EXIT_FAILURE);
            }
            else
            {
                if (pid2 == 0) // 子进程2执行f(y)
                {
                    close(pipe2[0]); // 子进程从管道1的1端进行写数据

                    int result_y = task2(y);

                    printf("f(y) = %d\n", result_y);
                    printf("child %d write : %d\n", getpid(), result_y);

                    write(pipe2[1], &result_y, sizeof(int));

                    // 写完成后,关闭管道
                    close(pipe2[1]);
                }
                else
                {
                    waitpid(pid2, &status2, 0); // 等待子进程2结束

                    // 父进程分别冲两个管道的0端读取子进程读取出来的信息

                    // 子进程1
                    close(pipe1[1]);
                    int tempx;
                    read(pipe1[0], &tempx, sizeof(int));
                    printf("parent %d read: %d\n", getpid(), tempx);
                    close(pipe1[0]);

                    // 子进程2
                    close(pipe2[1]);
                    int tempy;
                    read(pipe2[0], &tempy, sizeof(int));
                    printf("parent %d read: %d\n", getpid(), tempy);
                    close(pipe2[0]);

                    int result = task3(tempx, tempy);
                    printf("f(x, y) = %d\n", result);
                }
            }
        }
    }
    exit(EXIT_SUCCESS);
}