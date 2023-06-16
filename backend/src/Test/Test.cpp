#include <gtest/gtest.h>
#include "src/Handler/TestHandler.hpp"
#include "src/Protocol/Packet.hpp"
#include "src/Protocol/PacketParser.hpp"
#include "src/Protocol/PacketBuilder.hpp"
#include <sstream>

TEST(TEST_TEST, TestOfTest){
    EXPECT_EQ(1, 1);
}

TEST(Handler_Test, TestHandler){
    std::stringstream ss;
    FruitsGroove::TestHandler th{ss};
    th.Handle("test");
    th.Handle("hoge");
    th.Handle("fuga");
    th.Handle("piyo");
    EXPECT_EQ(ss.str(), "testhogefugapiyo");
}

TEST(PacketTest, PacketParser){
    auto packet = FruitsGroove::ParsePacket("00hogefuga");
    EXPECT_EQ(packet.op, FruitsGroove::OperationType::None) << "00hogefuga";
    EXPECT_EQ(packet.content, "hogefuga");
    packet = FruitsGroove::ParsePacket("01fugapiyo");
    EXPECT_EQ(static_cast<int>(packet.op), 1);
    EXPECT_EQ(packet.content, "fugapiyo");
    packet = FruitsGroove::ParsePacket("05fugapiyo");
    EXPECT_EQ(static_cast<int>(packet.op), 5);
    EXPECT_EQ(packet.content, "fugapiyo");
    //2桁目チェック
    packet = FruitsGroove::ParsePacket("10fugapiyo");
    EXPECT_EQ(static_cast<int>(packet.op), 10);
    EXPECT_EQ(packet.content, "fugapiyo");
    packet = FruitsGroove::ParsePacket("22fugapiyo");
    EXPECT_EQ(static_cast<int>(packet.op), 22);
    EXPECT_EQ(packet.content, "fugapiyo");
    packet = FruitsGroove::ParsePacket("124fugapiyo");
    EXPECT_EQ(static_cast<int>(packet.op), 12);
    EXPECT_EQ(packet.content, "4fugapiyo");
    //無効なOperationType
    packet = FruitsGroove::ParsePacket("aafugapiyo");
    EXPECT_EQ(packet.op, FruitsGroove::OperationType::None);
    EXPECT_EQ(packet.content, "fugapiyo");
}

TEST(PacketTest, PacketBuilder){
    {
        FruitsGroove::PacketBuilder pb;
        auto operation = 0;
        auto content = "hoge";
        auto expectString = "00hoge";
        auto packet = 
        pb.SetOperation(static_cast<FruitsGroove::OperationType>(operation))
        .SetContent(content)
        .Build();
        EXPECT_EQ(packet, expectString) << "expectStr: " << expectString << std::endl;
    }
    {
        FruitsGroove::PacketBuilder pb;
        auto operation = 1;
        auto content = "hoge";
        auto expectString = "01hoge";
        auto packet = 
        pb.SetOperation(static_cast<FruitsGroove::OperationType>(operation))
        .SetContent(content)
        .Build();
        EXPECT_EQ(packet, expectString) << "expectStr: " << expectString << std::endl;
    }
    {
        FruitsGroove::PacketBuilder pb;
        auto operation = 1;
        auto content = "fuga";
        auto expectString = "01fuga";
        auto packet = 
        pb.SetOperation(static_cast<FruitsGroove::OperationType>(operation))
        .SetContent(content)
        .Build();
        EXPECT_EQ(packet, expectString) << "expectStr: " << expectString << std::endl;
    }
    {
        FruitsGroove::PacketBuilder pb;
        auto operation = 11;
        auto content = "fuga";
        auto expectString = "11fuga";
        auto packet = 
        pb.SetOperation(static_cast<FruitsGroove::OperationType>(operation))
        .SetContent(content)
        .Build();
        EXPECT_EQ(packet, expectString) << "expectStr: " << expectString << std::endl;
    }
    {
        FruitsGroove::PacketBuilder pb;
        auto operation = 19;
        auto content = "fuga";
        auto expectString = "19fuga";
        auto packet = 
        pb.SetOperation(static_cast<FruitsGroove::OperationType>(operation))
        .SetContent(content)
        .Build();
        EXPECT_EQ(packet, expectString) << "expectStr: " << expectString << std::endl;
    }
    {
        FruitsGroove::PacketBuilder pb;
        auto operation = 99;
        auto content = "fuga";
        auto expectString = "99fuga";
        auto packet = 
        pb.SetOperation(static_cast<FruitsGroove::OperationType>(operation))
        .SetContent(content)
        .Build();
        EXPECT_EQ(packet, expectString) << "expectStr: " << expectString << std::endl;
    }
    {
        FruitsGroove::PacketBuilder pb;
        auto operation = 100;
        auto content = "fuga";
        auto expectString = "100fuga例外発生するはず";
        try{
            auto packet = 
                pb.SetOperation(static_cast<FruitsGroove::OperationType>(operation))
                .SetContent(content)
                .Build();
                EXPECT_TRUE(false) << expectString;//例外発生でcatchへ飛ぶはず ここまで来たらテスト失敗
        }catch(...){
            EXPECT_TRUE(true);
        }
    }
    {
        FruitsGroove::PacketBuilder pb;
        auto operation = 128;
        auto content = "fuga";
        auto expectString = "128fuga例外発生するはず";
        try{
            auto packet = 
                pb.SetOperation(static_cast<FruitsGroove::OperationType>(operation))
                .SetContent(content)
                .Build();
                EXPECT_TRUE(false) << expectString;//例外発生でcatchへ飛ぶはず ここまで来たらテスト失敗
        }catch(...){
            EXPECT_TRUE(true);
        }
    }
}
