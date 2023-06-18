#pragma once
#include<Siv3D.hpp>
# include "../Connection/Connection.hpp"

// リザルト画面
// 結果を表示する
class Result : public App::Scene {

private:

	const int my_score = getData().score;	// 自分のスコア
	int enemy_score = 0;	// 対戦相手のスコア
	const String songName = getData().songName;	// 曲名

	// 背景テクスチャ
	const Texture BG{ U"assets/Textures/BackGround/gamePlay.png" };

	// フォント
	Font scoreFont{ 130, U"assets/Font/Harlow Solid Regular.ttf" };

	// パケット
	FruitsGroove::Packet packet;
	// パケットがサーバから飛んでくるのを待つ
	bool hasSentPacket = false;
public:

	Result(const InitData& init)
		: IScene{ init } {

		getData().serverConnection.sendPacket(FruitsGroove::OperationType::GameEnd, Format(my_score));	// スコアの送信
	}

	void update() override {

		// 左クリックもしくは任意のキー入力で
		if ((MouseL.down()/* || Keyboard::GetAllInputs() */ ) && hasSentPacket == true)
		{
			// 曲選択シーンに遷移
			changeScene(U"Choice");
		}
		// パケットの受け取りを待つ
		if (getData().serverConnection.receivePacket(packet) && hasSentPacket == false)
		{
			if (packet.op == FruitsGroove::OperationType::ResultScore) {
				enemy_score = std::stoi(packet.content);
			}
		}
	}

	void draw() const override {

		BG.scaled(0.8).draw();	// 背景画像を表示
		if (hasSentPacket == true) {
			Rect{ 300, 50, 900,  150 }.draw(Palette::Saddlebrown).drawFrame(0, 8, Palette::Darkgray);	// 曲名の背景を表示
			FontAsset(U"TitleFont")(this->songName).drawAt(750, 125);
			// 自分のスコアを表示
			RoundRect{ 100, 250, 600, 550, 10 }.draw(Palette::Gold).drawFrame(10, 0, Palette::Orange);
			FontAsset(U"TitleFont")(U"score:").draw(130, 270);
			scoreFont(U"{}"_fmt(my_score)).draw(130, 320);
			// 相手のスコアを表示
			RoundRect{ 800, 250, 600, 550, 10 }.draw(Palette::Hotpink).drawFrame(10, 0, Palette::Deeppink);
			FontAsset(U"TitleFont")(U"score:").draw(830, 270);
			scoreFont(U"{}"_fmt(enemy_score)).draw(830, 320);
		}
		else {
			Rect{ 250, 250, 1000, 400 }.draw(ColorF(0, 0, 0, 0.2));
			FontAsset(U"TitleFont")(U"対戦対手を待っています").drawAt(750, 450);
		}
	}
};
