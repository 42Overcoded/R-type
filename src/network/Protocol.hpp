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
    Server_GetStatus,
	Server_GetPing,

	Client_Accepted,
	Client_AssignID,
	Client_RegisterWithServer,
	Client_UnregisterWithServer,

	Game_AddPlayer,
	Game_RemovePlayer,
	Game_UpdatePlayer,

};
};

#endif /* !PROTOCOL_HPP_ */
