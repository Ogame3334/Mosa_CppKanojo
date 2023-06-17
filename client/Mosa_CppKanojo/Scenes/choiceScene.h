#pragma once
# include <Siv3D.hpp>
# include "../Button.hpp"

// 曲選択シーン
// 挙動 : 左右キーで曲を選択、Enterか左クリックで決定
// 　　　ESCキーでタイトル画面に戻る
class Choice : public App::Scene {
private:

	// 左右選択ボタン
	ogm::Button<Triangle> leftButton{ Triangle(100, 400, 80, 270_deg), U"" };
	ogm::Button<Triangle> rightButton{ Triangle(1400, 400, 80, 90_deg), U"" };

	// 背景を動かす
	const Image bgImage_raw{ U"../Textures/BackGround/Banana.png" };
	const Texture bgImage[2]{ Texture{ bgImage_raw.scaled(0.6) },  Texture{ bgImage_raw.scaled(0.6) } };	// 背景画像の生成
	Vec2 bg_pos[2]{ Vec2{ 0,0 }, Vec2{ 0,1620 } };	// 背景画像の座標

	Array<String> songNames;	// 曲名
	int mScreen = 0;	// 表示中の楽曲

	int keyA_CT = 0;	// Aキー入力のクールタイム
	int keyD_CT = 0;	// Dキー入力のクールタイム
	const int keyHitCT = 10;	// キー入力のクールタイム
	bool sceneLock = false;	// シーン遷移ロック（trueの間はシーン遷移しない）
public:

	// コンストラクタ
	Choice(const InitData& init)
		: IScene{ init }
	{
		// 存在する楽曲を全て読み込む
		for (const auto& path : FileSystem::DirectoryContents(U"../Assets/Song", Recursive::No)) {
			songNames << path;
		}
		// 読み込んだ各楽曲について、その楽曲名のみを抽出する
		for (auto& songName : songNames) {
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
	}

    void update() override
	{
		if (this->keyA_CT == 0 && this->keyD_CT == 0) { this->sceneLock = false; }	// シーン遷移ロックをはずす
		// 背景を動かす
		for (int i = 0; i < 2; i++) {
			this->bg_pos[i].y -= 1;
			if (this->bg_pos[i].y < -1620) { this->bg_pos[i].y = 1620; }
		}
		this->mScreen += this->songNames.size();	// シーン遷移のために数値を加算
		// Aキーで左へ移動
		if ((KeyA.pressed() && this->keyA_CT == 0) || this->leftButton.update()) {
			this->mScreen--;
			this->keyA_CT = this->keyHitCT;	// キー入力にクールタイムを設定
			this->sceneLock = true;	// シーン遷移しないようにする
		}
		// Dキーで右へ移動
		if ((KeyD.pressed() && this->keyD_CT == 0) || this->rightButton.update()) {
			this->mScreen++;
			this->keyD_CT = this->keyHitCT;	// キー入力にクールタイムを設定
			this->sceneLock = true;	// シーン遷移しないようにする
		}
		this->mScreen = this->mScreen % this->songNames.size();	// 範囲外への楽曲選択を範囲内に戻す

		// 左クリックかenterで実際のゲーム画面に遷移
		if ((MouseL.up() || KeyEnter.up()) && this->sceneLock == false) {
			getData().songName = songNames[mScreen];	// 選択した楽曲名をゲームシーンに送信
			changeScene(U"Game");
		}

		if (keyA_CT > 0) { keyA_CT--; }	// クールタイムの回復
		if (keyD_CT > 0) { keyD_CT--; }	// クールタイムの回復

		// ESCキーでタイトル画面に戻る
		if (KeyEscape.pressed()) {
			// タイトル画面に遷移
			changeScene(U"Title");
		}
	}

	void draw() const override
	{
		
		for (int i = 0; i < 2; i++) { this->bgImage[i].draw(this->bg_pos[i]);}	// 背景画像を描画
		FontAsset(U"TitleFont")(U"Select a Music").drawAt(750, 100);
		FontAsset(U"TitleFont")(songNames[this->mScreen]).drawAt(750, 200);
		this->leftButton.draw();
		this->rightButton.draw();
	}
};
