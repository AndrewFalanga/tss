/*
 *
 *  tss.h
 *
 *  Desc: headerfile for the tss program, manually created for tss.c
 *
 *  Copyright (c)        Andrew Falanga
 *  April 24, 2001, 2023
 *
 */

#ifndef _TSS_H_
#define _TSS_H_

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

#define PORT 25035             /* arbitrary port, no reason */
#define SLEEP_INTERVAL 14400   /* 4 hours, wake up 6 times a day */
#define SHUTDOWN_INTERVAL 300  /* 5 minutes */
#define MYBUFF 6               /* max size for string buffers */
#define MSG_LEN 4              /* length of bytes transmitted or received */
#define USGERR "tssd must be supplied either host names or -v for version\n"
#define VERSION "3.5.01\n"
#define MESSAGE "Agents notified of admin shutdown, gracefully exiting"

/* ------------------------------------------------------------------- */

#define MSG_HELLO   ":->0"
#define MSG_PWR_OFF ":-(0"
#define MSG_PWR_ON  ":-)0"
#define MSG_ADM_ACT ":-|0"
#define MSG_CHK_IN  ";->0"

typedef enum {
    Startup,
    Run,
    Vulnerable,
    Shdown
} Status;

typedef enum {
    Hello,
    Pwroff,
    Pwron,
    Admact,
    Chkup
} Message;


#endif
