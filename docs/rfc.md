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
  - [Commands](#commands)
    - [ServerGetPing](#servergetping)
    - [ServerConnect](#serverconnect)
    - [ServerUpdateControls](#serverupdatecontrols)
    - [ServerStartGame](#serverstartgame)
    - [ClientAccepted](#clientaccepted)
    - [ClientDenied](#clientdenied)
    - [ClientAssignID](#clientassignid)
    - [ClientSendPing](#clientsendping)
    - [ClientAddPlayer](#clientaddplayer)
    - [ClientRemovePlayer](#clientremoveplayer)
    - [ClientCreateEntity](#clientcreateentity)
    - [ClientUpdateEntity](#clientupdateentity)
    - [ClientDestroyEntity](#clientdestroyentity)
    - [ClientStartGame](#clientstartgame)
    - [ClientEndGame](#clientendgame)
  - [Connection](#connection)

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
|      |              |              |
| Flag | Payload Size |   Payload    |
|      |              |              |
|------------------------------------|
|                                    |
|                UDP                 |
|                                    |
\------------------------------------/
```

As you can see, the GTP is just on top of the UDP.
That allow it to be lightweight and highly efficient.

``Flag`` is a 4 bytes long (uint32_t) number.
  It define the following message.
``Size`` is a 4 bytes long (uint32_t) number.
  It describe the size in bit of the payload.
  Value of 0 in case of no payload.
``Payload`` is a structure containing different information.
  It will change depending of the value of the header.

## Commands

The following commands are available in the GTP protocol.

```txt
| Command | Description           |
| ------- | --------------------  |
| 0x00    | ServerGetPing         |
| 0x01    | ServerConnect         |
| 0x02    | ServerUpdateControls  |
| 0x03    | ServerStartGame       |
| 0x04    | ClientAccepted        |
| 0x05    | ClientDenied          |
| 0x06    | ClientAssignID        |
| 0x07    | ClientSendPing        |
| 0x08    | ClientAddPlayer       |
| 0x09    | ClientRemovePlayer    |
| 0x0A    | ClientCreateEntity    |
| 0x0B    | ClientUpdateEntity    |
| 0x0C    | ClientDestroyEntity   |
| 0x0D    | ClientStartGame       |
| 0x0E    | ClientEndGame         |
```

### ServerGetPing

- Origin : Client
- Flag : 0x00
- Size : 0x00
- Payload : None

- Response : ClientSendPing

Description : This command is used to check if the server is still alive.

### ServerConnect

- Origin : Client
- Flag : 0x01
- Size : 0x00
- Payload : None

- Response : ClientAccepted
- Response : ClientAssignID

Description : This command is used to connect to the server.
When the server accept the connection, it will open a new connection on a separate port.
Then it will send a ClientAccepted command to confirm the connection.
Then it will send a ClientAssignID command to assign an ID to the client.
When the server deny the connection, it will send a ClientDenied command.

### ServerUpdateControls

- Origin : Client
- Flag : 0x02
- Size : 0x05 (bool * 5)
- Payload : [bool, bool, bool, bool, bool] (Up, Down, Left, Right, Shoot)

Description : This command is used to update the controls of the player.

### ServerStartGame

- Origin : Client
- Flag : 0x03
- Size : 0x04 (uint_32_t)
- Payload : [uint32_t] (Game Type)

Description : This command is used to start the game. The payload describe the type of game.

### ClientAccepted

- Origin : Server
- Flag : 0x04
- Size : 0x00
- Payload : None

Description : This command is used to confirm the connection to the server.
It is usually followed by a ClientAssignID command.

### ClientDenied

- Origin : Server
- Flag : 0x05
- Size : 0x00
- Payload : None

Description : This command is used to deny the connection to the server.

### ClientAssignID

- Origin : Server
- Flag : 0x06
- Size : 0x04 (uint32_t)
- Payload : [uint32_t] (Client ID)

Description : This command is used to assign an ID to the client.

### ClientSendPing

- Origin : Server
- Flag : 0x07
- Size : 0x00
- Payload : None

Description : This command is used to check if the client is still alive. (Response to ServerGetPing)

### ClientAddPlayer

- Origin : Server
- Flag : 0x08
- Size : 0x04 (uint32_t)
- Payload : [uint32_t] (Player ID)

Description : This command is used to add a player to the game.

### ClientRemovePlayer

- Origin : Server
- Flag : 0x09
- Size : 0x04 (uint32_t)
- Payload : [uint32_t] (Player ID)

Description : This command is used to remove a player from the game.

### ClientCreateEntity

- Origin : Server
- Flag : 0x0A
- Size : 0x1C (uint32_t * 5 + float * 2)
- Payload : [uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, float, float] (Entity ID, Entity Owner, Entity Type, Arg1, Arg2, Position X, Position Y)

Description : This command is used to create an entity in the game.

### ClientUpdateEntity

- Origin : Server
- Flag : 0x0B
- Size : 0x0C (uint32_t * 3)
- Payload : [uint32_t, uint32_t, uint32_t] (Entity ID, Position X, Position Y)

Description : This command is used to update an entity in the game.

### ClientDestroyEntity

- Origin : Server
- Flag : 0x0C
- Size : 0x04 (uint32_t)
- Payload : [uint32_t] (Entity ID)

Description : This command is used to destroy an entity in the game.

### ClientStartGame

- Origin : Server
- Flag : 0x0D
- Size : 0x04 (uint32_t)
- Payload : [uint32_t] (Game Type)

Description : This command is used to start the game.

### ClientEndGame

- Origin : Server
- Flag : 0x0E
- Size : 0x00
- Payload : None

Description : This command is used to end the game.

## Connection

The connection is established by the client.
The client send a ServerConnect command to the server and open its UDP socket to new connections.
The Server create a new connection on a separate port and send a ClientAccepted command to the client.
Then it send a ClientAssignID command to assign an ID to the client.

If the server deny the connection, it will send a ClientDenied command.

```txt
/--------------------------------------\
|     Client       |      Server       |
|------------------|-------------------|
|                  |                   |
| ServerConnect    |                   |
|----------------->|[Create new socket]|
|[Allow incoming   |                   |
|connection]       |                   |
|                  |  ClientAccepted   |
|[Connect to       |<------------------|
|incoming]         |                   |
|                  |  ClientAssignID   |
|                  |<------------------|
|                  |                   |
|                  |                   |
\--------------------------------------/
```
