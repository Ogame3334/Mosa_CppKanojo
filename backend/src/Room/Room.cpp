//#include "src/Room/Room.hpp"

//namespace FruitsGroove{
//void Room::SocketDataProcessor(SocketPtr& dest_socket, SocketPtr& source_socket){
    //while(true){
        //// メッセージ受信
        //asio::streambuf receive_buffer;
        //boost::system::error_code error;
        //asio::read(*source_socket, receive_buffer, asio::transfer_at_least(1), error);

        //if (error && error != asio::error::eof) {
            //continue;
        //}
        //const char* data = asio::buffer_cast<const char*>(receive_buffer.data());
        //auto packet = ParsePacket(data);    
        //this->packetHandler.Handle(packet, dest_socket, *this);
    //}
//}
//Room::Room(std::array<SocketPtr, 2>&& socketArray):
    //socketArray(std::move(socketArray))
    //{}

    

//}
