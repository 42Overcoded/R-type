RFC
Authors : ``M. Jalbert``, ``M. Peireto``, ``F. Azema``, ``S. Borisenko``, ``J. Vignau-Espine``
Date : ``7 October 2023``

---

# Game Transmission Protocol (GTP)

## Status of this Memo

This memo is the official specification of the Game Transmission Protocol (GTP).

Distribution of this memo is unlimited.

## Index

- [Game Transmission Protocol (GTP)](#game-transmission-protocol-gtp)
  - [Status of this Memo](#status-of-this-memo)
  - [Index](#index)
  - [Introduction](#introduction)
  - [Overview](#overview)
    - [History](#history)
    - [Terminology](#terminology)
  - [The GTP Model](#the-gtp-model)
  - [Communication Functions](#communication-functions)
    - [GTP Commands](#gtp-commands)
      - [Messages Transmission Commands](#messages-transmission-commands)
    - [GTP Replies](#gtp-replies)
      - [Numeric Order List of Reply Codes](#numeric-order-list-of-reply-codes)
  - [Declarative Specifications](#declarative-specifications)
    - [Minimum Implementation](#minimum-implementation)
    - [Connections](#connections)
    - [Commands](#commands)
    - [GTP Commands](#gtp-commands-1)
    - [GTP Command Arguments](#gtp-command-arguments)
    - [Sequencing of commands and replies](#sequencing-of-commands-and-replies)

## Introduction

The Game Transmission Protocol (GTP) is defined to make available a
fast packet transmission of packet-switched computer communication in the
environment of an interconnected set of computer networks. This
protocol assumes that the User Datagram Protocol (UDP) [RFC 768](https://www.ietf.org/rfc/rfc768.txt)
is used as the underlying protocol.

This protocol provide a procedure for games to communicate with a server.
It uses UDP as a fast packet-switched computer communication protocol.
Therefore the protocol is transaction oriented, and delivery and duplicate
protection are not guaranteed.

## Overview

In this section, the history, the terminology, and the GTP model are discussed.
The terms defined in this section are only those that have special
significance in GTP. Some of the terminology is very specific to the GTP model;
some readers may wish to turn to the section on the GTP model while reviewing
the terminology.

### History

The Game Transmission Protocol come from a long tradition at the Epitech school.
Every year, 3nd year students have to work in teams to create a protocol
allowing a fast communication between multiple game clients an a server.

This protocol has been originally developed to create a multiplayer version of
the R-type game.
R-Type is a horizontally scrolling shooter arcade video game developed and
released by Irem in 1987 and the first game in the R-Type series.
The player controls a star ship, the R-9 "Arrowhead", in its efforts to destroy
the Bydo, a powerful alien race bent on wiping out all of mankind.
The R-9 can acquire a glowing orbicular device called a "Force", protecting it
from enemy fire and providing additional firepower.
The arcade version was distributed by Nintendo in North America; it is the last
arcade title Nintendo distributed.

### Terminology

GTP

```txt
    Game Transmission Protocol
```

UDP

```txt
    User Datagram Protocol
```

## The GTP Model

With the above definitions in mind, the following model (shown in Figure 1)
may be diagrammed for an GTP service.

```txt
/------------------------------------\
|      |    |              |         |
| Flag | Id | Payload Size | Payload |
|      |    |              |         |
|------------------------------------|
|                                    |
|                UDP                 |
|                                    |
\------------------------------------/
```

As you can see, the GTP is just on top of the UDP.
That allow it to be lightweight and highly efficient.

``Flag`` is a 1 bytes long (uint8_t) number.
  It define the following message.
``Id`` is a 8 bytes long (uint64_t) number.
  It is used to identify the message.
``Size`` is a 8 bytes long (uint64_t) number.
  It describe the size in bit of the payload.
  Value of 0 in case of no payload.
``Payload`` is a structure containing different information.
  It will change depending of the value of the header.

## Communication Functions

### GTP Commands

#### Messages Transmission Commands

### GTP Replies

#### Numeric Order List of Reply Codes

## Declarative Specifications

### Minimum Implementation

### Connections

### Commands

### GTP Commands

### GTP Command Arguments

### Sequencing of commands and replies
