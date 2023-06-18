#pragma once
#include "../Connection/Connection.hpp"
#include "../Protocol/PacketBuilder.hpp"

namespace FruitsGroove{
class APIClient{
private:
	Connection::ServerConnection connection;
public:
	bool CheckMatchingError() {
		Packet packet;
		if (this->connection.receivePacket(packet)) {
			return false;
		}
		return packet.op == OperationType::MatchingError;
	}

	bool CheckMatchingComplete() {
		Packet packet;
		if (this->connection.receivePacket(packet)) {
			return false;
		}
		return packet.op == OperationType::MatchingComplete;
	}

	void NoticeIDAndName(StringView name) {
		this->connection.sendPacket(OperationType::NoticeIDAndName, name);
		return;
	}

	bool CheckRoomCreated() {
		Packet packet;
		if (this->connection.receivePacket(packet)) {
			return false;
		}
		return packet.op == OperationType::NoticeRoomCreated;
	}

	void SendSelectedSong(StringView songName) {
		this->connection.sendPacket(OperationType::SelectedSong, songName);
		return;
	}

	bool CheckWaitForSelectingSong() {
		Packet packet;
		if (this->connection.receivePacket(packet)) {
			return false;
		}
		return packet.op == OperationType::WaitForSelectingSong;
	}

	bool CheckRandomChoicedSong(String& songName) {
		Packet packet;
		if (this->connection.receivePacket(packet)) {
			return false;
		}
		if (packet.op != OperationType::RandomChoicedSong) {
			return false;
		}
		songName = Unicode::FromUTF8(packet.content);
		return true;
	}

	void SendClientReady() {
		this->connection.sendPacket(OperationType::ClientReady, U"");
		return;
	}

	bool CheckGameStart() {
		Packet packet;
		if (this->connection.receivePacket(packet)) {
			return false;
		}
		return packet.op == OperationType::GameStart;
	}

	void SendCurrentScore(int score) {
		this->connection.sendPacket(OperationType::CurrentScore, Unicode::FromUTF8(std::to_string(score)));
		return;
	}

	void SendCurrentCombo(int combo) {
		this->connection.sendPacket(OperationType::CurrentCombo, Unicode::FromUTF8(std::to_string(combo)));
		return;
	}

	bool CheckGameEnd() {
		Packet packet;
		if (this->connection.receivePacket(packet)) {
			return false;
		}
		return packet.op == OperationType::GameEnd;
	}


	bool CheckOpponentResultScore(String& score) {
		Packet packet;
		if (this->connection.receivePacket(packet)) {
			return false;
		}
		if (packet.op != OperationType::ResultScore) {
			return false;
		}
		score = Unicode::FromUTF8(packet.content);
		return true;
	}

};

}


