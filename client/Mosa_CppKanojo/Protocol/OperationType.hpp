#pragma once

namespace FruitsGroove{
enum class OperationType{
    None,
    WaitForPlayer,
	MatchingError,
    MatchingComplete, 
    NoticeIDAndName,
    NoticeRoomCreated,
    SelectedSong,
    WaitForSelectingSong,
    RandomChoicedSong,  
    ClientReady, //clientが準備完了であるあかし
    GameStart,
    CurrentScore, 
    CurrentCombo,
    GameEnd, 
    ResultScore,
    OperationCount, // 一番最後に置くこと!!! OperationTypeの数が入る 必要なときもあるだろう
    };
}
