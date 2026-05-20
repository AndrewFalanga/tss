# Introduction

This specification defines the modules needed for the *Networked Power Monitor* application. This application enables a
network of computers, all connected to the same UPS, to know when power is lost when only one of the many is directly
connected to the UPS.

# Interface to the UPS

It is assumed that the software monitoring the UPS is running on the system which is running the *Power Agent*. The
*Power Agent* monitors a region of shared memory for messages from the UPS monitor (or some other program). These
will be authenticated by the *Power Agent* to ensure that it is not a spoof. 

The basic construct of the message from the UPS (or the software that writes to shared memory) is "on"/"off"
concatenated with a timestamp. This is then signed and that signature is concatenated to the end.

# Power Agent


## Interface to the UPS

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
