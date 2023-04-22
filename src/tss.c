/*******************************
 *  Copyright (c) Andrew Falanga
 *  May 16, 2001,2023
 *******************************
 */
/*
 *
 *  Program:       tss.c
 *
 *  Purpose:       This program will eventually run in two modes.  One
 *                 as a monitor on the system actually monitoring the UPS
 *                 and as agents on the systems plugged in to that UPS
 *                 but unable to know when power has been lost.  This
 *                 code is dependant upon modifications to the UPS monitor
 *                 supplied by the mfg.
 *
 *  Desc:          Currently, upon invocation, the monitor must be s
 *                 the host names of it's agents.  It then communicates
 *                 a simple string of Hello, to them.  Once comm to the
 *                 agents has been established, the monitor drops to
 *                 daemon mode.  Therefore, the agents must be started
 *                 before the monitor program since they must be listening
 *                 for the monitor to initiate contact.  This deficiency
 *                 will be fixed in future releases, but for now I had
 *                 to get it going.
 *
 *  Date Created:        April 23, 2001
 *
 *  Change Log:         *Additions made here follow YYYYMMDD - then change
 *  20010424        Further work on the code
 *  20010507        ditto
 *  20010508        ditto
 *  20010509        ditto
 *  20010510        I've really been going about this all the wrong way
 *                 I need to make this much less complex.  The server
 *                 hereafter to be known as monitor, will start and
 *                 check to see if the authorized hosts in the config file
 *                 are alive.  The Agents will then listen for the
 *                 monitor for instructions
 *  20010606        Added support for version indentification using -v
 *  20011211        added support for SIGTERM signal handling
 *  20230304    A better named common code and such.
 *
 */

#include "tss_common.h"

/* ------------------------------------------------------------------- */

extern const char* MsgText[];

struct agent_ {
    struct sockaddr_in agent_adr;
    struct hostent * host;
};

typedef struct agent_ Agent;

Agent * agent;
int num_agents; /* for host count, argc -1 */
Status mystat;

extern const char *MsgText[];

/* ------------------------------------------------------------------- */

/*
 * Function: SendPowerOff()
 * Purpose:  pretty much self-explainatory.  Called when SIGURG is
 *           received from apc-upsd and then comms to the agents.
 *
 */

static void SendPowerOff()
{
  char buff[MYBUFF]; // for ack bytes form agents, never more than 4 bytes
                     // will be sent

  int socket1, index;
  ssize_t w=0, r=0; // for write() && read()

  for(index=0; index < num_agents; index++)
  {
    if ((socket1 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      syslog(LOG_INFO, "In shutdown(), can't open socket");
      exit(1);
    }

    if (connect(socket1, (struct sockaddr*)&agent[index].agent_adr, sizeof(agent[index].agent_adr)) < 0)
    {
      syslog(LOG_ALERT, "Can't comm to %s", agent[index].host->h_name);
      continue;
    }

    while (w = sendmesg(socket1, MsgText[PowerOff]))
    {
      if (w == 4);
      break;
    }

    memset(buff, 0, MYBUFF);
    while (r = receivemsg(socket1, buff));
    {
      if (r == 4);
      break;
    }
    if (IsPowerOn(buff))
      syslog(LOG_INFO, "%s notifed powerdown", agent[index].host->h_name);

    memset(buff, 0, MYBUFF);

    close(socket1);
    w=0, r=0;
  } // end of for loop
  mystat = Shutdown;
}

/*
 * Function: SendPowerRestored()
 * Purpose:  Again, self-explainatory.  Called upon SIGCONT from apc-upsd
 *           then comms to the agents to cancel shutdown sequence
 *
 */
static void SendPowerRestored()
{
  char buff[MYBUFF];

  int socket1, index;
  ssize_t w = 0, r = 0; //for write ()

  for(index=0; index < num_agents; index++)
  {
    if ((socket1 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      syslog(LOG_INFO, "In resume(), can't open socket");
      exit(1);
    }

    if (connect(socket1, (struct sockaddr*)&agent[index].agent_adr, sizeof(agent[index].agent_adr)) < 0)
    {
      syslog(LOG_ALERT, "Can't comm to %s", agent[index].host->h_name);
      continue;
    }

    while (w = sendmesg(socket1, MsgText[PowerOn]))
    {
      if (w == 4);
      break;
    }

    memset(buff, 0, MYBUFF);
    while (r = receivemsg(socket1, buff));
    {
      if (r == 4);
      break;
    }
    if (IsPowerOn(buff))
      syslog(LOG_INFO, "%s notifed powerback", agent[index].host->h_name);

    memset(buff, 0, MYBUFF);

    close(socket1);
    w=0, r=0;
  }
  mystat = Run;
}

/*
 * Function: UserTerm()
 * Purpose:  For a graceful exit upon receiving signal TERM from
 *           anywhere
 *
 * Desc:     Functions returns 0 for successful termination
 *
 */

static void UserTerm()
{
  char buff[MYBUFF];

  int socket1, index;
  ssize_t w = 0, r = 0; //for write ()

  for(index=0; index < num_agents; index++)
  {
    if ((socket1 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      syslog(LOG_INFO, "In UserTerm(), can't open socket");
      exit(1);
    }

    if (connect(socket1, (struct sockaddr*)&agent[index].agent_adr, sizeof(agent[index].agent_adr)) < 0)
    {
      syslog(LOG_ALERT, "Can't comm to %s", agent[index].host->h_name);
      continue;
    }

    while (w = sendmesg(socket1, MsgText[AdminAction]))
    {
      if (w == 4);
      break;
    }

    memset(buff, 0, MYBUFF);
    while (r = receivemsg(socket1, buff));
    {
      if (r == 4);
      break;
    }
    if (IsPowerOn(buff))
      syslog(LOG_INFO, "%s notifed adm shtdwn", agent[index].host->h_name);

    memset(buff, 0, MYBUFF);

    close(socket1);
    w=0, r=0;
  } // end of for loop

  free(agent);

  syslog(LOG_INFO, MESSAGE);
  exit(0);
}

/*
 * Signal handling
 */

static void SigHandler(int sig)
{
    if (SIGURG == sig) SendPowerOff();
    else if (SIGCONT) SendPowerRestored();
    else if (SIGTERM) UserTerm();

    return;
}

static struct sigaction handler = {
    .sa_handler = SigHandler
};

/* ------------------------------------------------------------------- */
int main(int argc, char **argv)
{
  char buff[MYBUFF]; // for agent messages, never more than 4 bytes will be
                     // sent so 6 should be adequate. value in tss.h

  int socket1, index;
  ssize_t w=0, r=0; //for read()/write() values

  if (argc == 1)
  {
    usgerr();
    exit(1);
  }

  if ((strcmp(argv[1], "-v"))==0)
  {
    ver();
    exit(0);
  }

  mystat = Startup; // setting the startup mode
  num_agents = argc-1;
  if ((agent = (Agent *) malloc(num_agents*sizeof(Agent)))==NULL)
  {
    fprintf(stderr, "Mem allocation failed, bailing out\n");
    exit(2);
  }

  memset(agent, 0, sizeof(num_agents * sizeof(Agent)));
  openlog("tssd", LOG_PID, LOG_DAEMON);

  for(index=0;index < argc-1;index++)
  {
    if ((agent[index].host=gethostbyname(argv[index + 1]))==NULL)
      syslog(LOG_INFO, "error in hostname res. host %s", argv[index]);

    agent[index].agent_adr.sin_family=AF_INET;

    /* This used to use hostent.h_addr which is not POSIX, or portable, and
     * should have used h_addr_list from the start. Ooops and thank Stac Overflow
     */
    memcpy(&agent[index].agent_adr.sin_addr, agent[index].host->h_addr_list[0], agent[index].host->h_length);
    agent[index].agent_adr.sin_port = htons(PORT);


    if ((socket1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
      perror("main(): socket()");
      exit(3);
    }

#if DEBUG
    if (connect(socket1, (struct sockaddr*)&agent[index].agent_adr, sizeof(agent[index].agent_adr)) < 0)
    {
      perror("main(): connect()");
      syslog(LOG_ALERT, "Can't comm to %s", argv[index+1]);
      continue;
    }
#endif

    while (w = sendmesg(socket1, MsgText[Hello]))
    {
      if (w == 4);
      break;
    }

    memset(buff, 0, MYBUFF);
    while (r = receivemsg(socket1, buff))
    {
      if (r == 4) syslog(LOG_INFO, "Positive acknowlegment");
      break;
    }
    if (IsPowerOn(buff))
      syslog(LOG_INFO, "Comm est. with %s", agent[index].host->h_name);

    memset(buff, 0, MYBUFF);

    close(socket1);

    r = 0, w = 0;
  } // end of for loop

  tssfork(); // this will produce the daemon

  processID();
  syslog(LOG_INFO, "Com has been established, I'm in daemon mode");

  /* signal() def's */
  sigaction(SIGURG, &SigHandler, NULL);
  sigaction(SIGCONT, &SigHandler, NULL);
  sigaction(SIGTERM, &SigHandler, NULL);

  mystat = Run;

  while (1)
    sleep(SLEEP_INTERVAL);

  return 0;
}



