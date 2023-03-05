/*
 *
 *  tss_func.c
 *
 *  Contains all "global" functions for the tss program
 *  and it's agents
 *
 *  Copyright 2001,2023 Andrew Falanga (c)
 *    All Rights Reserved
 *
 *
 *
 *  DLM: March 16, 2002
 *       March 4, 2023
 *
 */

#include "tss.h"

/*---------------------------------------------------------------------*/

extern const char *Mon_Msg[];

/*---------------------------------------------------------------------*/

/*
 * Function:        tssfork()
 * Purpose:        only to turn the process of forking to a child
 *                less muddy to main program code files
 */

void tssfork(void)
{
  switch(fork())
  {
    case -1:
        syslog(LOG_CRIT, "fork() didn't work, exiting");
        exit(7);
    case  0:        /* child process */
        break;
    default:        /* parent */
        exit(0);
  }
}

/*
 * Function:        ProcessID()
 * Purpose:        To write the process ID of the daemon to /var/run/tss.pid
 * Use:                Mainly, at this point, it is only used by the apc-upsd
 *                software to comm to the monitor portion of the code
 *                however, it's included in the agent for properly
 *                documenting the PID and for use with other programs should
 *                the need arise.
 */

int processID(void)
{
  FILE * fpid;

  if((fpid=fopen("/var/run/tss.pid", "w"))==NULL)
   return 0;

  fprintf(fpid, "%d\n", (int)getpid());
  fclose(fpid);
  return 1;
}

/*
 * Function:        p_string(char*)
 * Purpose:        This function serves the purpose of parsing the actual
 *                contents of the buffer to which data, transmitted from
 *                the monitor to agents, is stored.  Determine what the
 *                message is, and return an integer value to correspond
 *                to.  The function returns -1 if nothing meaningful is
 *                read.
 *
 * Notes:        a single char variable is used to keep track of the current
 *                system state.  The following values are used:
 *                s -- startup state
 *                        this value will only exist upon program start, or
 *                        when the agent has received notification that the
 *                        monitor is going offline
 *                k -- kill state
 *                        this value will exist when the monitor sends shutdown
 *                r -- normal run state
 */

Message p_string(const char *str)
{
  if(strstr(str, ";->0"))
    return chkup;

  if(strstr(str, ":->0"))
    return hello;

  if(strstr(str, ":-(0"))
    return pwroff;

  if(strstr(str, ":-)0"))
    return pwron;

  if(strstr(str, ":-|0"))
    return admact;
}

/*
 * Func:        usgerr
 * Pur:                to display the correct usage of this program
 *
 */

void usgerr()
{
  fprintf(stdout, "%s", USGERR);
}

/*
 * Func: ver
 * Pur:  to display the current version #
 *
 */

void ver()
{
  fprintf(stdout, "%s", VERSION);
}

/*
 * Func: receivemsg()
 * Pur:  function that will actually read from the file descriptor
 *       the data being sent from either monitor or agent.
 */

int receivemsg(int sock, char *hold)
{
  int received=0;
  while(received != 4)
  {
    received=recv(sock, hold, MSG_LEN, MSG_NOSIGNAL);
    if(received == 0)
      return received;
    hold += received;
  }
  return received;
}

int sendmesg(int sock, const char *hold)
{
  int sent=0;
  while(sent !=4)
    sent=send(sock, hold, MSG_LEN, MSG_NOSIGNAL);

  return sent;
}

/*
 * Function:        openchannel()
 * Purp:        This function
int openchannel(int *); // prototype, source in tss_func.c */
