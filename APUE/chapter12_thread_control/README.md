* Difference between LWP and thread: https://stackoverflow.com/questions/28476456/threads-and-lwp-in-linux
* Linux有了man, 你可以不用开google就可以写C语言程序了，man可以让你查系统调用，库函数，头文件，多么遍历。写C++，估计还不行。写C，我感觉已经很顺畅了。
* C/C++ 线程库有三种， C++11的thread, pthread(POSIX thread), boost::thread
* 线程的好处，如果是多进程应用，业务逻辑要在不同的进程间切换，就要涉及CPU上下文切换，浪费了更多的CPU资源；如果是多线程，线程切换一样也要设计CPU上下文的切换，所以，我找对线程的优势。当不同执行逻辑之间需要交换数据的时候，线程就有优势了，线程可以用共享的全局变量；而进程间通信的成本就大的多，**如何大？** 如果涉及到IO读写，多线程就有优势，阻塞的线程，自己休眠就可以了，还没占用多少资源。
* 稀里糊涂说了那么多，发现，线程的好处是立身于多核环境，核心点就是共享，好处是相对于多进程应用。所以，你要和多进程应用比较，懂得多进程应用，多线程应用才能理解线程的优势，核心点就是线程的执行逻辑是共享各种操作系统资源：虚拟地址空间，打开的文件描述符，堆空间，全局变量。而多进程就不一样，每个进程都要有自己的一份操作系统资源。APUE读的好，都能理解。
* 不要浪费已有的努力，vert.x, 微服务，继续，成型。
* C语言开发的著名软件：
  * Nginx。 和Netty类似。
* C Semaphore example: http://pages.cs.wisc.edu/~remzi/Classes/537/Fall2008/Notes/threads-semaphores.txt
* 使用system call构造出Linux上的线程：https://nullprogram.com/blog/2015/05/15/  Raw Linux Threads via System Calls
* APUE-12.6 线程私有数据，有些情况下，还是需要线程私有数据，譬如说errno. 如何实现的线程成私有数据？数据存在何处？POSIX只是定义了接口，pthread_key_create, 可能有各种方式实现这个接口，不同的平台可能也有不同的实现。
