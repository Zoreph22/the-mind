#pragma once

/// Liste des types de message envoyé par le client.
enum CliMsg
{
	CLI_MSG_NONE,
	CLI_MSG_SET_NAME = 1,
	CLI_MSG_SET_READY = 2,
	CLI_MSG_SET_NUM_BOT = 3,
	CLI_MSG_PLAY_CARD = 4,
	CLI_MSG_REPLAY_GAME = 5,
	CLI_MSG_MAX
};

/// Liste des types de message envoyé par le serveur.
enum SrvMsg
{
	SRV_MSG_NONE,
	SRV_MSG_INFO_LOBBY = 1,
	SRV_MSG_PLAYER_CONNECTED = 2,
	SRV_MSG_CARD_PLAYED = 3,
	SRV_MSG_NEXT_ROUND = 4,
	SRV_MSG_GAME_END = 5,
	SRV_MSG_MAX
};