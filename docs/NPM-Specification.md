# Introduction

This specification defines the modules needed for the *Networked Power Monitor* application. This application enables a
network of computers, all connected to the same UPS, to know when power is lost when only one of the many is directly
connected to the UPS.

## General Architecture

There are 2 software components to the *Networked Power Monitor*

 - *Power Agent*
 - *Power Monitor*

Communication between them utilizes UDP over Ethernet. This could be wired or wireless.

In general, communication is "one way" in this architecture. The *Agent* will listen to the UPS interface for on/off.
When detected, in either case, the *Agent* communicates the state to the *Monitors*.

*Monitor* programs listen to their UDP sockets for status messages. The *Agent* will periodically broadcast the state as
it is read from the UPS interface. There seems to be little point in the *Monitor* sending messages to *Agents*
periodically. However, most modern network systems usually prevent broadcast packets so there will be a dynamic
discovery mechanism employed by the *Agent* in which monitors will be added. The process is documented in the *Power
Agent* section below.

# Power Agent

The power agent is the software component

## Interface to the UPS

It is assumed that the software monitoring the UPS is running on the system which is running the *Power Agent*. The
*Power Agent* monitors a region of shared memory for messages from the UPS monitor (or some other program). These
will be authenticated by the *Power Agent* to ensure that it is not a spoof. 

The basic construct of the message from the UPS (or the software that writes to shared memory) is "on"/"off"
concatenated with a timestamp. This is then signed and that signature is concatenated to the end.

The *Power Agent* shall open a region of shared memory large enough to contain the following:

"on" or "off" || "<timestamp>" || <EC-DSA signature in ASN.1>

The minimum region size for this shall be 256 bytes.

## Communication

Opens a UDP socket bound to INADDR\_ANY. Does lots of a amazing things. The *Power Monitor* will only be a sender. It
will

- Periodically send the current state of the power system


# Power Monitor

The *Power Monitor* opens a UDP to INADDR\_ANY and listen. The *Power Monitor* will not send anything.

Each transmission from the *Power Agent* will be authenticated.

# Cryptographic Requirements

It's not desirable for anyone to signal a shutdown by simply communicating the right command to the UDP sockets. So, a
means of authenticating the command is required. Because the nature of this, it seems that authenticity is desired while
confidentiality is not required. To that end, the *Agent* and *Monitor* shall rely on ECC to perform DSA operations. The
algorithm choices are:

  - SHA384
  - EC Curve P-384

The elements to be hashed shall be:

  - The status message (see section status messages)
  - A time stamp string of the form "MM/DD/YYYY HH:MM:SS.MS"

These shall be concatenated and hashed according to FIPS-202 using SHA3-384 and then signed using EC-DSA according to
FIPS-186-5. The resulting signature shall be transmitted along with the status message and time stamp concatenation.

## Encryption

None is anticipated for this project


