* compile tips: https://github.com/Joyounger/APUEse2
* http://www.apuebook.com/
* 我想知道的？
  * 数据是如何从应用程序写到磁盘的？  App buffer, kernel buffer, file system, disk bio_buffer?
  * TODO: kill -9是如何被处理的？这条命令向目标进程发送信号，目标有信号处理程序，信号处理程序会执行exit()?, 问题是进程只有一个执行路径（又不是多线程），所以说信号处理程序的执行上下文是如何的？每次有机会的时候都去验证一下是否有KILL信号，如果有的话就退出。这里的机会可能是进程让出CPU之后，被再次调度的时候。如果这个进程正在等IO， 是不是要等很久才能退出，还是说内核会让这种睡眠状态的进程，直接被唤醒，立马验证是否有KILL信号，然后退出。20190111
    * SIGKILL(9) 是不能被进程捕获/忽略的，所以,kill -9 应该是内核层面的强制退出,直接操作进程对应的内核结构。https://bencane.com/2014/04/01/understanding-the-kill-command-and-how-to-terminate-processes-in-linux/
    * https://major.io/2010/03/18/sigterm-vs-sigkill/
    ```text
    Although SIGKILL is defined in the same signal header file as SIGTERM, it cannot be ignored by the process.
    In fact, the process isn’t even made aware of the SIGKILL signal since the signal goes straight to the kernel init. 
    At that point, init will stop the process. The process never gets the opportunity to catch the signal and act on it.
    However, the kernel may not be able to successfully kill the process in some situations.
    If the process is waiting for network or disk I/O, the kernel won’t be able to stop it. 
    Zombie processes and processes caught in an uninterruptible sleep cannot be stopped by the kernel, either. 
    A reboot is required to clear those processes from the system.
    ```
    
  
* 线程栈的大小是可以控制的。Sherman在调Tomcat的VSS空间，发现几个ZMQ线程的栈各占了８MB的VSS空间。原因应该是ulimit -s设为了8MB.
 * https://stackoverflow.com/questions/50917576/zeromq-background-thread-creation
 * https://unix.stackexchange.com/questions/127602/default-stack-size-for-pthreads
 * Code 输出线程栈的大小：
  ```c
  #include <pthread.h>
  #include <stdio.h>

  int main()
  {

      pthread_attr_t attr;
      int stacksize;

      int rc = pthread_attr_init(&attr);
      pthread_attr_getstacksize(&attr, &stacksize);
      printf("Thread stack size = %d bytes \n", stacksize); //Will output Thread stack size = 8388608 bytes in our system.

      return 0;

  }
  ```
