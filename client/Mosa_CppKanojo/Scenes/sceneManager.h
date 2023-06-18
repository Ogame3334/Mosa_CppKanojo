# pragma once
# include <Siv3D.hpp>
# include "../Connection/Connection.hpp"

// 楽曲名とスコアを共有する
struct GameData {

	String songName = U"";
	int songNum = 0;
	int score = 0;
	bool isMultiPlay = 0;
	FruitsGroove::Connection::ServerConnection serverConnection{};
};

// 楽曲情報を保存
struct SongData {
	String title;
	Audio audio;
	uint8 bpm;
};

// 名前空間の省略
using App = SceneManager<String, GameData>;

// 各シーンが格納されたヘッダファイルを参照
# include "./titleScene.h"
# include "./choiceScene.h"
# include "./GameScene.h"
# include "./ResultScene.h"
# include "./MdspeedScene.h"
