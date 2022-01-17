/*
{-----------------------------------------------------------------------}
{			tss.h						}
{									}
{ Desc:	headerfile for the tss program, manually created for tss.c	}
{									}
{ Copyright (c)	Andrew Falanga 						}
{ April 24, 2001							}
{-----------------------------------------------------------------------}
*/

#ifndef _tss_h_
#define _tss_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* ------------------------------------------------------------------- */

#define PORT 5035	/* arbitrary port, no reason */
#define SLEEP_INTERVAL 14400 /* 4 hours, wake up 6 times a day */
#define SHUTDOWN_INTERVAL 300  /* 5 minutes */
#define MYBUFF 6 /* max size for string buffers */
#define MSG_LEN 4 /* length of bytes transmitted or received */
#define USGERR "tssd must be supplied either host names or -v for version\n"
#define VERSION "This is version 3.5.01 of The Shutdown Server\n"
#define MESSAGE "Agents notified of admin shutdown, gracefully exiting"

/* ------------------------------------------------------------------- */

typedef enum Stat {startup, run, vulnerable, shdown} Cur_Stat;
typedef enum trans {hello, pwroff, pwron, admact, chkup} Message;

/* ------------------------------------------------------------------- */

int processID(void); // prototype, source in tss_func.c
void tssfork(void); // prototype, source in tss_func.c
Message p_string(const char *); // prototype, source in tss_func.c
void usgerr(void); // prototype, source in tss_func.c
void ver(void); // prototype, source in tss_func.c
int tx_rx(int *, int); // prototype, source in tss_func.c
int receivemsg(int, char *); // prototype, source in tss_func.c
int sendmesg(int, const char *); // prototype, source in tss_func.c
int openchannel(int *); // prototype, source in tss_func.c

/* ------------------------------------------------------------------- */


#endif
