
# General Protocol Requirements and Expected Use

## Agent Communications

The communication needs of this application are relatively simple. The most communicative application is the agent. The
agent is expecting input from a pipe which is communicating the presence/absence of utility power. The agent only
receives data on this pipe. The agent is then communicating this status to monitors that have registered with the agent.

The registration process is done with the arrival of a packet on the agent's socket which the "hello" string (defined
below). The IP stack operating on the system will provide the appropriate details for address and port, and the packet
payload contents will tell the agent of the legitimacy. This is the only input from monitors. The agent shall ignore all
other in-bound packets on that interface.

Power line status is conveyed with the strings defined below, concatenated with a time stamp and signed. The entirety of
those 3 are transmitted to each registered monitor. This would be

```txt
<status>||<time stamp>||<signature>
```

## Monitor Communications

The monitor is very stoic. The monitor shall transmit its presence via a "hello" packet to the agent. After this, the
monitor forever waits for activity from the agent.

The hello packet shall consist of the word "hello" concatenated with a time stamp (as defined below) and the EC-DSA
signature for that string. This provides a means for the agent to know of legitmate monitors. The registration process
does not provide for a means of acknowledgement.

Once registered, the monitor will begin polling for incoming data on the socket.

# Time Stamp

Time stamps shall consist of year, month and day with  Hour, Minute, second and milliseconds as is illustrated with the
following

```txt
YYYY-MM-DD HH:MM:SS.mmm
```

# Status Messages

The message is simple and really just informs power is on/off. The following shall be expected from both the agent, from
the UPS software, and the monitors:

| Symbol |  Meaning     |
+--------+--------------+
|  :-)   | Power is on  |
|  :-(   | Power is off |

These should be adequate. There isn't any point in conveying an unknown state of power. Obviously, if the code is
running, power is on.

# Packet Formats

In general, all packets are of the form

```txt
text||time stamp||signature
```

## Registration

The registration packet shall be

```txt
hello||YYYY-MM-DD HH:MM:SS.mmm||ECC-Sig
```

## Status Message

Status message received, either by the agent or monitor, shall be

```txt
<symbol>||YYYY-MM-DD HH:MM:SS.mmm||ECC-Sig
```
