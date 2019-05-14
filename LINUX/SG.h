#ifndef SG_H_INCLUDED
#define SG_H_INCLUDED
//Linux signal library handler

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


/*
SIGABRT Process abort signal.
SIGALRM Alarm clock.
SIGFPE  Erroneous arithmetic operation.
SIGHUP  Hangup.
SIGILL  Illegal instruction.
SIGINT Terminal interrupt signal.
SIGKILL Kill (cannot be caught or ignored).
SIGPIPE Write on a pipe with no one to read it.
SIGQUIT Terminal quit signal.
SIGSEGV Invalid memory reference.
SIGTERM Termination signal.
SIGUSR1 User-defined signal 1.
SIGUSR2 User-defined signal 2.
SIGCHLD Child process terminated or stopped.
SIGCONT Continue executing, if stopped.
SIGSTOP Stop executing (cannot be caught or ignored).
SIGTSTP Terminal stop signal.
SIGTTIN Background process attempting read.
SIGTTOU Background process attempting write.
SIGBUS  Bus error.
SIGPOLL Pollable event.
SIGPROF Profiling timer expired.
SIGSYS  Bad system call.
SIGTRAP Trace/breakpoint trap.
SIGURG  High bandwidth data is available at a socket.
SIGVTALRM   Virtual timer expired.
SIGXCPU CPU time limit exceeded.
SIGXFSZ File size limit exceeded.
*/


///Signal reader



void SH(int sig)//signal handler
{
write(0, "SIGINT!\n", 14);
}

int SC(){//Signal catcher
    
int SH(int sig); /* prototype */


struct sigaction sa;
sa.sa_handler = SH;
sa.sa_flags = 0; // or SA_RESTART
sigemptyset(&sa.sa_mask);

if (sigaction(SIGINT, &sa, NULL) == -1) {
perror("sigaction");
return 1;//Error return
}

}

///End signal reader.


///Signal sender



///End signal sender

#endif // AXSG_H_INCLUDED
