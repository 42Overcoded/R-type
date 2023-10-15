/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Protocol
*/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_
#include <cstdint>

namespace Network {
enum class Flag : uint32_t
{
	ServerGetPing,
	ServerConnect,
	ServerUpdateControls,

	ClientAccepted,
	ClientAssignID,
	ClientSendPing,
	ClientAddPlayer,
	ClientRemovePlayer,
	ClientCreateEntity,
	ClientUpdateEntity,
};
};

#endif /* !PROTOCOL_HPP_ */
