/*
 *
 *  tss_common.h
 *
 *  Desc: headerfile for the tss program, manually created for tss.c
 *
 *  Copyright (c)        Andrew Falanga
 *  April 24, 2001, 2023
 *
 */

#ifndef _TSS_COMMON_H
#define _TSS_COMMON_H

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

#define TRUE        (1)
#define FALSE       !(TRUE)

typedef uint8_t boolean;

typedef enum {
    Startup,
    Run,
    Vulnerable,
    Shutdown
} Status;

typedef enum {
    Error = -1,
    Hello,
    PowerOff,
    PowerOn,
    AdminAction,
    CheckIn
} Message;

/*
 * Probably a poor design, but I was a young programmer 22 years ago. I used the happy/sad
 * faces which also represented PowerOn/PowerOff.
 */
typedef enum {
    PositiveAck = (int)PowerOn,
    NegativeAck = (int)PowerOff,
} Acks;

int processID(void); // prototype, source in tss_func.c
void tssfork(void); // prototype, source in tss_func.c
Message MessageKey(const char *); // prototype, source in tss_func.c
void usgerr(void); // prototype, source in tss_func.c
void ver(void); // prototype, source in tss_func.c
int tx_rx(int *, int); // prototype, source in tss_func.c
int receivemsg(int, char *); // prototype, source in tss_func.c
int sendmesg(int, const char *); // prototype, source in tss_func.c
int openchannel(int *); // prototype, source in tss_func.c

boolean IsHello(const char*);
boolean IsPowerOn(const char*);
boolean IsPowerOff(const char*);
boolean IsAdminAction(const char*);
boolean IsCheckIn(const char*);

#endif
