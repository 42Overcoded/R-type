/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Protocol
*/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_
#include <cstdint>
#include <string>

namespace Network {
enum class Flag : uint32_t
{
	ServerGetPing,
	ServerConnect,
	ServerUpdateControls,

	ClientAccepted,
	ClientDenied,
	ClientAssignID,
	ClientSendPing,
	ClientAddPlayer,
	ClientRemovePlayer,
	ClientCreateEntity,
	ClientUpdateEntity,
};

const uint32_t DefaultPort = 4242;
const std::string DefaultIp = "127.0.0.1";
const uint32_t MaxPacketsProcessed = 10;
const uint32_t MaxClients = 4;
const uint32_t NetworkRefreshRate = 60;
};

#endif /* !PROTOCOL_HPP_ */
