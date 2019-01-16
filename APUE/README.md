* compile tips: https://github.com/Joyounger/APUEse2
* http://www.apuebook.com/
* 我想知道的？
  * 数据是如何从应用程序写到磁盘的？  App buffer, kernel buffer, file system, disk bio_buffer?
  * TODO: kill -9是如何被处理的？这条命令向目标进程发送信号，目标有信号处理程序，信号处理程序会执行exit()?, 问题是进程只有一个执行路径（又不是多线程），所以说信号处理程序的执行上下文是如何的？每次有机会的时候都去验证一下是否有KILL信号，如果有的话就退出。这里的机会可能是进程让出CPU之后，被再次调度的时候。如果这个进程正在等IO， 是不是要等很久才能退出，还是说内核会让这种睡眠状态的进程，直接被唤醒，立马验证是否有KILL信号，然后退出。20190111
    * SIGKILL(9) 是不能被进程捕获/忽略的，所以,kill -9 应该是内核层面的强制退出,直接操作进程对应的内核结构。https://bencane.com/2014/04/01/understanding-the-kill-command-and-how-to-terminate-processes-in-linux/
    
  
