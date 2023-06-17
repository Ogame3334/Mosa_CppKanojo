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
    GameEnd, // ここにプレイヤーのスコアが乗ってくることを想定
    ResultScore, //これに相手のスコアを乗せて返す
    OperationCount, // 一番最後に置くこと!!! OperationTypeの数が入る 必要なときもあるだろう
    };
}
