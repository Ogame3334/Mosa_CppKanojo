#pragma once
# include <Siv3D.hpp>
# include "../Button.hpp"
# include "../Connection/Connection.hpp"

// 曲選択シーン
// 挙動 : 左右キーで曲を選択、Enterか左クリックで決定
// 　　　ESCキーでタイトル画面に戻る
class Choice : public App::Scene {
private:

	// 左右選択ボタン
	ogm::Button<Triangle> leftButton{ Triangle(100, 400, 80, 270_deg), U"" };
	ogm::Button<Triangle> rightButton{ Triangle(1400, 400, 80, 90_deg), U"" };
	const Image buttonTexture_raw{ U"assets/Textures/UIUX/arrowButton.png" };	// ボタン用テクスチャ
	const Texture buttonTexture{ buttonTexture_raw };

	// メニュー画面で表示するボタン
	ogm::Button<RoundRect> touchSpeedButton{ RoundRect(550, 300, 400, 100, 5), U"タイミング調整" };
	ogm::Button<RoundRect> backTitleButton{ RoundRect(550, 450, 400, 100, 5), U"タイトル画面" };
	ogm::Button<RoundRect> exitButton{ RoundRect(550, 600, 400, 100, 5), U"ゲームを出る" };

	// 背景を動かす
	const Image bgImage_raw{ U"assets/Textures/BackGround/Banana.png" };
	const Texture bgImage[2]{ Texture{ bgImage_raw },  Texture{ bgImage_raw } };	// 背景画像の生成
	Vec2 bg_pos[2]{ Vec2{ 0,0 }, Vec2{ 0,1620 } };	// 背景画像の座標

	Array<String> songNames;	// 曲名
	int mScreen;	// 表示中の楽曲

	int keyF_CT = 0;	// Fキー入力のクールタイム
	int keyJ_CT = 0;	// Jキー入力のクールタイム
	const int keyHitCT = 10;	// キー入力のクールタイム
	bool sceneLock = false;	// シーン遷移ロック（trueの間はシーン遷移しない）
	bool menuLock = false;	// ESCキーでメニューを開いているときの画面ロック
	bool isWaitMatch = false;	// 他プレイヤーが来るまで待機
	bool isMatchComp = false;
	bool isSendSong = false;
	bool isWaitSelectedSong = false;
	bool isWaitStart = false;

	FruitsGroove::Packet packet;
public:

	// コンストラクタ
	Choice(const InitData& init)
		: IScene{ init }
	{
		// 存在するデータを全て読み込む
		for (const auto& path : FileSystem::DirectoryContents(U"assets/Songs", Recursive::No)) {
			this->songNames << path;
		}
		// 読み込んだデータのうち、mp3とwavのみ抽出する
		this->songNames.remove_if([](String songName) {
			return !(songName.ends_with(U".mp3") || songName.ends_with(U".wav"));
		});
		// 読み込んだ各楽曲について、その楽曲名のみを抽出する
		for (auto& songName : this->songNames) {
			const int dirPos = songName.lastIndexOf(U"/");	// 最後に現れるスラッシュを探す
			if (dirPos != songName.npos) {	// 最後のスラッシュが見つかったら、それ以前の文字を全部削除
				songName.erase(0, dirPos + 1);
			}
			// 同様に、曲の拡張子を削除する
			const int extPos = songName.lastIndexOf(U".");
			if (extPos != songName.npos) {
				songName.erase(extPos, songName.npos);
			}
		}

		// ボタンにテクスチャを追加
		this->leftButton.setIsTexture(true);
		this->leftButton.setTexture(this->buttonTexture);
		this->rightButton.setIsTexture(true);
		this->rightButton.setTexture(this->buttonTexture);

		// 各ボタンの色設定など
		this->touchSpeedButton.setFont(20, Typeface::Regular, FontStyle::Default);
		this->touchSpeedButton.setBackColors(ColorF{ 1.0, 0.714, 0.757, 1.0 }, ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.412, 0.706 , 1 });
		this->touchSpeedButton.setOutlineWidth(3, 0);
		this->touchSpeedButton.setOutlineColors(ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.412, 0.706 , 1 });
		this->backTitleButton.setFont(20, Typeface::Regular, FontStyle::Default);
		this->backTitleButton.setBackColors(ColorF{ 1.0, 0.714, 0.757, 1.0 }, ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.412, 0.706 , 1 });
		this->backTitleButton.setOutlineWidth(3, 0);
		this->backTitleButton.setOutlineColors(ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.412, 0.706 , 1 });
		this->exitButton.setFont(20, Typeface::Regular, FontStyle::Default);
		this->exitButton.setBackColors(ColorF{ 1.0, 0.714, 0.757, 1.0 }, ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.412, 0.706 , 1 });
		this->exitButton.setOutlineWidth(3, 0);
		this->exitButton.setOutlineColors(ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.412, 0.706 , 1 });

		// メニュー画面は最初開いていないので
		this->menuLock = false;

		this->mScreen = getData().songNum;	// 前回遊んでいた楽曲を表示
		this->mScreen = this->mScreen % this->songNames.size();	// 範囲外への楽曲選択を範囲内に戻す

		getData().serverConnection.connect();	// サーバとの接続を開始
	}

    void update() override
	{
		if (this->menuLock == false && this->isWaitMatch == false)	// メニュー画面を開いていないときの処理
		{
			if (this->keyF_CT == 0 && this->keyJ_CT == 0) { this->sceneLock = false; }	// シーン遷移ロックをはずす
			// 背景を動かす
			for (int i = 0; i < 2; i++) {
				this->bg_pos[i].y -= 1;
				if (this->bg_pos[i].y < -1620) { this->bg_pos[i].y = 1620; }
			}
			this->mScreen += this->songNames.size();	// シーン遷移のために数値を加算
			// DかFキーで左へ移動
			if (((KeyF | KeyD).pressed() && this->keyF_CT == 0) || this->leftButton.update()) {
				this->mScreen--;
				this->keyF_CT = this->keyHitCT;	// キー入力にクールタイムを設定
				this->sceneLock = true;	// シーン遷移しないようにする
			}
			// JかKキーで右へ移動
			if (((KeyJ | KeyK).pressed() && this->keyJ_CT == 0) || this->rightButton.update()) {
				this->mScreen++;
				this->keyJ_CT = this->keyHitCT;	// キー入力にクールタイムを設定
				this->sceneLock = true;	// シーン遷移しないようにする
			}
			if (KeyTab.up() || MouseR.up()) {	// モードを切り替え（ビット反転もどき）
				getData().isMultiPlay == false ? getData().isMultiPlay = true : getData().isMultiPlay = false;
			}
			this->mScreen = this->mScreen % this->songNames.size();	// 範囲外への楽曲選択を範囲内に戻す

			// 左クリックかenterかSpaceで実際のゲーム画面に遷移
			if ((MouseL.up() || KeyEnter.up() || KeySpace.up()) && this->sceneLock == false) {
				getData().songName = this->songNames[this->mScreen];	// 選択した楽曲名をゲームシーンに送信
				getData().songNum = this->mScreen;	// 楽曲の要素番号もゲームシーンに送信
				if (getData().isMultiPlay == false) {
					changeScene(U"Game");
				}
				else {
					isWaitMatch = true;
				}
			}

			if (this->keyF_CT > 0) { this->keyF_CT--; }	// クールタイムの回復
			if (this->keyJ_CT > 0) { this->keyJ_CT--; }	// クールタイムの回復

			// ESCキーでメニュー画面を表示
			if (KeyEscape.up()) {
				//メニュー画面に切り替え
				this->menuLock = true;
			}
		}
		else if (isWaitMatch == true) {
			if (isMatchComp == false) {
				if (getData().serverConnection.receivePacket(packet)) {
					if (packet.op == FruitsGroove::OperationType::WaitForPlayer) {}
					else if (packet.op == FruitsGroove::OperationType::MatchingComplete) {	// マッチング成功後
						isMatchComp = true;
					}
				}
			}
			if (isMatchComp == true && isSendSong == false) {
				if (getData().serverConnection.receivePacket(packet)) {
					if (packet.op == FruitsGroove::OperationType::NoticeRoomCreated) {
						getData().serverConnection.sendPacket(FruitsGroove::OperationType::SelectedSong, songNames[mScreen]);
						isSendSong = true;
					}
				}
			}
			if (isSendSong == true && isWaitSelectedSong == false) {
				if (getData().serverConnection.receivePacket(packet)) {
					if (packet.op == FruitsGroove::OperationType::WaitForSelectingSong) {
						isWaitSelectedSong = true;
					}
				}
			}
			if (isWaitSelectedSong == true && isWaitStart == false) {
				if (getData().serverConnection.receivePacket(packet)) {
					if (packet.op == FruitsGroove::OperationType::RandomChoicedSong) {
						getData().songName = Unicode::Widen(packet.content);
						getData().serverConnection.sendPacket(FruitsGroove::OperationType::ClientReady, U"");
						isWaitStart = true;
					}
				}
			}
			if (isWaitStart == true) {
				if (getData().serverConnection.receivePacket(packet)) {
					if (packet.op == FruitsGroove::OperationType::GameStart) {
						changeScene(U"Game");
					}
				}
			}
		}
		else if (menuLock == true)	// メニュー画面を開いているときの処理
		{
			if (touchSpeedButton.update()) {	// タイミング調整ボタンで調整画面に遷移
				changeScene(U"Mdspeed");
			}
			if (backTitleButton.update()) {	// タイトルへ戻るボタン
				changeScene(U"Title");
			}
			if (exitButton.update()) {	// ゲームを終了
				System::Exit();
			}
			// ESCキーでメニュー画面を表示
			if (KeyEscape.up()) {
				//メニュー画面を終了
				this->menuLock = false;
			}
		}
	}

	void draw() const override
	{
		for (int i = 0; i < 2; i++) { this->bgImage[i].draw(this->bg_pos[i]);}	// 背景画像を描画
		if (getData().isMultiPlay == true) {	// マルチプレイモードであれば背景をピンクっぽくする
			Rect{ 0, 0, 1920, 1080 }.draw(ColorF{ 1, 0, 1, 0.1 });
		}
		FontAsset(U"TitleFont")(U"Music Select - {}[TAB]"_fmt(getData().isMultiPlay == true ? U"マルチモード" : U"ソロモード")).drawAt(750, 100);
		FontAsset(U"TitleFont")(songNames[this->mScreen]).drawAt(750, 200);
		this->leftButton.draw();
		this->rightButton.draw();
		if (this->menuLock == true) {	// メニュー画面
			Rect{ 0, 0, 1920, 1080 }.draw(ColorF{ 0.0,0.0,0.0,0.25 });	// 画面を少し灰色にする
			this->touchSpeedButton.draw();	// メニュー項目の表示
			this->backTitleButton.draw();	// メニュー項目の表示
			this->exitButton.draw();	// メニュー項目の表示
		}
		if (isWaitMatch == true) {	// マッチング成功後
			Rect{ 0, 0, 1920, 1080 }.draw(Palette::Black);
			Print << Random();
			FontAsset(U"TitleFont")(U"Now Loading...").drawAt(1000, 800);
			if (isMatchComp == false) {
				FontAsset(U"TitleFont")(U"対戦相手を待っています...").drawAt(750, 200);
			}
			else if (isMatchComp == true && isSendSong == false) {
				FontAsset(U"TitleFont")(U"楽曲を送信しています...").drawAt(750, 200);
			}
			else if (isSendSong == true && isWaitSelectedSong == false) {
				FontAsset(U"TitleFont")(U"曲を抽選しています...").drawAt(750, 200);
			}
			else if (isWaitSelectedSong == true && isWaitStart == false) {
				FontAsset(U"TitleFont")(U"対戦相手を待っています...").drawAt(750, 200);
			}
			else if (isWaitStart == true) {
				FontAsset(U"TitleFont")(U"まもなく対戦が始まります...").drawAt(750, 200);
			}
		}
	}
};
