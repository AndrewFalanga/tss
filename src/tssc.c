/*
{-----------------------------------------------------------------------}
{                                                                       }
{ Copyright (c) Andrew Falanga                                          }
{ May 16, 2001                                                          }
{-----------------------------------------------------------------------}
*/
/*
{-----------------------------------------------------------------------}
{ Program:    tssc.c                                                    }
{                                                                       }
{ Desc:        The client side to "The Shutdown Server"                 }
{                                                                       }
{ Purp:        To run in daemon mode, open a connection to the tss      }
{        over IP and basically monitor what's happening and             }
{        in the event that the server sends out a disaster              }
{        broadcast, perform a clean shutdown of the file system         }
{        and OS.                                                        }
{                                                                       }
{ Date Created:    May 7, 2001                                          }
{ DLM:        March 19, 2002                                            }
{                                                                       }
{ Change log:                                                           }
{ YYYYMMDD     reason for change                                        }
{ 20010508    further work on the code                                  }
{ 20010509    further development, (see notes below for detail)         }
{ 20010510    further development, (see notes below for detail)         }
{ 20010531    redid code so that enters daemon mode upon                }
{        instantiation, rather than after the monitor starts.           }
{        Hopefully, with these mod's the program can be added to        }
{        rc.local and start as a system process.                        }
{ 20011217    added support for the newly written p_string()            }
{ 20230212  Long time! Wow, I was dumb for making such a ridiculous     }
{           header. Yeah, it looks good, but really! Too much!          }
{                                                                       }
{ Notes:                                                                }
{    coded enough that the client now opens connection, and sends       }
{    a string to which the server appends a new string and returns      }
{    the appended string                                                }
{                                                                       }
{    Realized today that I'd been thinking about this the wrong way     }
{    Instead of the server listening for incoming connections           }
{    it should be the clients listening for ther server                 }
{    The code must be reworked to reflect the new design                }
{-----------------------------------------------------------------------}
*/

#include "tss.h"

/* ------------------------------------------------------------------- */

const char *Agt_Msg[] = {":-)0", ":-(0"}; // acknowledgment strings
Cur_Stat mystat; // status indicator

/* ------------------------------------------------------------------- */

static void Shutdown(void);
static void TermHandle(int);
static void takeaction(Message, pid_t *);

/* ------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    char buff[MYBUFF];

    int socket1, socket2, mon_len;

    struct linger    linger_val;
    struct sockaddr_in mon_adr, my_adr;

    pid_t childpid;
    ssize_t r = 0, w = 0; // for read() & write()
    mystat = startup; // set current status at startup

    if(argc > 1)
    {
        if((strcmp(argv[1], "-v"))==0)
        {
            ver();
            exit(0);
        }
    }


    memset(&my_adr, 0, sizeof(my_adr));
    my_adr.sin_family = AF_INET;
    my_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_adr.sin_port = htons(PORT);

    tssfork();
    openlog("tsscd", LOG_PID, LOG_DAEMON);
    syslog(LOG_INFO, "tsscd is alive as daemon");

    (void)signal(SIGTERM, TermHandle);

    if(!processID())
        syslog(LOG_INFO, "Can't create /var/run/tss.pid file");

    if((socket1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        syslog(LOG_INFO, "tsscd, couldn't open socket, exiting");
        exit(3);
    }

    if(bind(socket1, (struct sockaddr*)&my_adr, sizeof(my_adr)) < 0)
    {
        syslog(LOG_INFO, "tsscd, error detected in bind() exiting");
        exit(4);
    }

    linger_val.l_onoff = 1;
    linger_val.l_linger = 10;
    listen(socket1, 5); // for portable code, this is set to 5

    while(1)
    {
        mon_len = sizeof(mon_adr);
#if STREAM_SOCKET
        if((socket2 = accept(socket1, (struct sockaddr*)&mon_adr, &mon_len))<0)
        {
            syslog(LOG_INFO, "tsscd, error in accept() exiting");
            exit(4);
        }

        if(setsockopt(socket2, SOL_SOCKET, SO_LINGER, &linger_val, sizeof(linger_val)) < 0)
            syslog(LOG_INFO, "Can't set sock options!!");
#endif

        while(r=receivemsg(socket2, buff))
        {
            if(r == 4) printf("r does equal 4\n");
            break;
        }
        while(w=sendmesg(socket2, Agt_Msg[0]))
        {
            if(w == r);
            break;
        }

        takeaction(p_string(buff), &childpid);

        memset(buff, 0, MYBUFF);
        r = 0, w = 0;
        close(socket2);
    } // end of while

} // end of main()


/*
{-----------------------------------------------------------------------}
{ Function:    Shutdown                        }
{                                    }
{ Purpose:    This functions passes a series of commands to a shell    }
{        after sleeping for the alloted, at the time of this    }
{        writing that was 5 minutes (see tss.h).  The function    }
{        is executed by a child process of this program        }
{-----------------------------------------------------------------------}
*/

static void Shutdown(void)
{
    sleep(SHUTDOWN_INTERVAL);

    /* save our file system */
    system("/bin/sync");
    system("/bin/sync");
    system("/bin/sync");

    /* shutdown the system now */
    system("shutdown -h now");
}

/*
{-----------------------------------------------------------------------}
{ Function:    TermHandle                        }
{                                    }
{ Purpose:    This function will handle things when the TERM signal    }
{        has been received.  Either explicitly, by an admin, or    }
{        implicitly by a system shutdown                }
{                                    }
{-----------------------------------------------------------------------}
*/
static void TermHandle(int x)
{
    syslog(LOG_INFO, "TERM signal received, agent exiting");
    exit(0);
}

/*
{-----------------------------------------------------------------------}
{ Function:    takeaction                                               }
{                                                                       }
{ Purpose:    This function will take appropriate action based upon     }
{        the result of the return of p_string().                        }
{                                                                       }
{-----------------------------------------------------------------------}
*/

void takeaction(Message act, pid_t * cpid)
{
    switch(act)
    {
        case pwroff: // shutdown directive received
            syslog(LOG_CRIT, "Power lost, shutdown in 5 minutes");
            mystat = shdown;

            if((*cpid=fork())==0)
                Shutdown();
            break;

        case admact: // notification that the monitor is going down
            syslog(LOG_CRIT, "mon going off-line, system in vulnerable state!");
            mystat = vulnerable;
            break;

        case pwron: // notification that power is back
            // kill(*cpid, SIGKILL);
            kill(*cpid, SIGTERM);
            *cpid = wait(NULL);
            syslog(LOG_CRIT, "Power restored, shutdown sequence canceled!");
            mystat = run;
            break;

        case hello: // monitor says hello and comm is established
            syslog(LOG_INFO, "tsscd, comm established with monitor");
            mystat = run;
            break;

        case chkup: // agent turned on after monitor
            syslog(LOG_INFO, "routine checkup");
            break;

        default:
            syslog(LOG_INFO, "monitor sent bogus data");
    } // end of switch
} // end of takeaction()
