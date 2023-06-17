﻿#include"Scenes/GameScene.h"
#include"Note.h"
#include"EndNote.h"

GameScene::GameScene(const InitData& init) : IScene{ init }, frontNoteId{0,0}, isStart(false) {
	data = SongData{ getData().songName, Audio{U"assets\\Songs\\{}.mp3"_fmt(getData().songName)}, 0};
	textures = std::unordered_map<String, Texture>{
		{U"bg", Texture{U"assets\\Textures\\gamePlay.png"}},
		{U"bg_kibako", Texture{U"assets\\Textures\\bg_kibako.png"}},
		{U"giar", Texture{U"assets\\Textures\\giar.png"}},

		{U"excellent", Texture{U"assets\\Textures\\text_excellent.png"}},
		{U"good", Texture{U"assets\\Textures\\text_good.png"}},
		{U"miss", Texture{U"assets\\Textures\\text_miss.png"}},

		{U"press", Texture{U"assets\\Textures\\press.png"}},

		{U"apple", Texture{U"assets\\Textures\\apple.png"}},
		{U"broken_apple", Texture{U"assets\\Textures\\broken_apple.png"}},
		{U"dried_apple", Texture{U"assets\\Textures\\dried_apple.png"}},

		{U"invisible", Texture{U"assets\\Textures\\invisible.png"}}
	};
	loadNotes();
}

void GameScene::update() {
	//play audio
	if (!data.audio.isPlaying()) {
		if (isStart)
			changeScene(U"Title");
		else {
			data.audio.play();
			isStart = true;
		}
	}

	if (KeyEscape.pressed()) {	// ESCキーが押されたら選択画面に戻る
		changeScene(U"Choice");
	}

	currentTime = uint32(data.audio.posSec() * 1000);

	//update press animation
	if (currentAnim != 0) {
		++currentAnim;
		if (pressAnim.size() == currentAnim) currentAnim = 0;
	}
	if (currentDryAnim != 0) {
		++currentDryAnim;
		if (dryAnim.size() == currentDryAnim) currentDryAnim = 0;
	}

	//update judge message
	if (judges.size() > 0 && currentTime - judges.front().second > 1000) {
		judges.pop_front();
	}

	//decide front node
	int32 difTime[]{ 0, 0 };
	Lane n = upper;
	for (;3;) { // <- It's so cute!!!
		difTime[n] = int32(notes[n].at(frontNoteId[n])->getTiming()) - int32(currentTime);
		if (difTime[n] >= -int32(parmitDilay)) {
			if (n == upper) {
				n = under;
				continue;
			}
			break;
		}
		if (!nextNote(n)) {
			if (n == upper) {
				n = under;
				continue;
			}
			break;
		}
	}

	//process key controle
	n = upper;
	if (KeyF.down() || KeyD.down() || KeyJ.down() || KeyK.down()) {
		if (KeyF.down() || KeyD.down()) {
			n = under;
			currentAnim = 1;
		}
		else {
			n = upper;
			currentDryAnim = 1;
		}
		JUDGE result = notes[n].at(frontNoteId[n])->hit(difTime[n], n);
		judges.push_back(std::pair<JUDGE, uint32>{
			result, currentTime
		});
		if (result == JUDGE::miss) {
			comb = 0;
		}
		else {
			++comb;
		}
	}
}

void GameScene::draw() const {
	//BackGround
	Rect{ 0,0,Scene::Width(), Scene::Height() }(textures.at(U"bg")).draw(Color{ 100,100,100 });
	for (int i = 0; i < 3; ++i) {
		Rect{ Scene::Width() / 3,Scene::Height() * i / 3,Scene::Width() / 3, Scene::Height() / 3 }(textures.at(U"bg_kibako")).draw();
		Rect{ Scene::Width() / 2,Scene::Height() * i / 3,Scene::Width() / 3, Scene::Height() / 3 }(textures.at(U"bg_kibako")).draw();
		Rect{ Scene::Width() * 2 / 3,Scene::Height() * i / 3,Scene::Width() / 3, Scene::Height() / 3 }(textures.at(U"bg_kibako")).draw();
	}
	//Machine
	//Wall
	Rect{ int(hit.left().x), int(hit.top().y) - 650, 150, int(hit.top().y) + 650 }.draw(Color{ 50, 50, 50 });
	hit.draw();
	Polygon{
		Vec2{int(hit.left().x) + 150, int(hit.top().y) - 650},
		Vec2{int(hit.left().x) + 150, Scene::Height()},
		Vec2{int(hit.left().x) + 140, Scene::Height()},
		Vec2{int(hit.left().x) + 140, int(hit.top().y) - 630},
	}.draw(Color{ 140, 140, 140 });

	for (int j = 0; j < 2; ++j) {
		int h = 450;
		int beltW = 80;
		int beltH = 120;
		int lineW = 5;
		//ベルトコンベア
		Rect{ 0, int(hit.bottom().y + beltW / 2 - j * h), Scene::Width(), beltW }.draw(Color{ 50,50,50 });
		Rect{ 0, int(hit.bottom().y - beltW / 2 - j * h), Scene::Width(), beltW }.draw(Color{ 150,150,150 });
		Rect{ 0, int(hit.bottom().y + beltW / 2 - lineW - j * h), Scene::Width(), lineW }.draw(Color{ 0,0,0 });
		Rect{ 0, int(hit.bottom().y + beltH - j * h), Scene::Width(), lineW }.draw(Color{ 0,0,0 });
		Rect{ 0, int(hit.bottom().y - beltW / 2 - j * h), Scene::Width(), lineW }.draw(Color{ 0,0,0 });
		for (int i = 0; i < Scene::Width(); i += 500) {
			textures.at(U"giar").scaled(0.8).rotated(data.bpm * (currentTime / 50 % 360))
				.drawAt(i, int(hit.bottom().y + beltW - j * h));
		}
		//draw bar
		int quater_bar = 60000 / data.bpm;
		for (int i = -4; i < 50; ++i) {
			Rect{
				int32(hit.center.x) + int(((i + 4) * quater_bar - int(currentTime % quater_bar)) * data.bpm / 300) - 105,
				int32(hit.center.y) + 5 - j * h, lineW, beltW + 10
			}.rotated(10).draw(Color{ 0, 0, 0 });
		}
		//draw node
		for (int n = 0; n < 2; ++n) {
			for (auto note : notes[n]) {
				Rect{
					int32(hit.center.x + (int(note->getTiming()) - int(currentTime)) * data.bpm / 300) - 50,
					int32(hit.center.y) + n * h - 500, 100
				}(*(note->getTexture())).draw();
			}
		}
		if (j == 1) break;
		//Press
		Rect{
			int(hit.left().x - 25),
			int(hit.top().y - pressAnim[currentAnim]),
			150, 300
		}(textures.at(U"press")).draw();
		Rect{
			0, int(hit.top().y - pressAnim[0] + 110),
			Scene::Width(), 90
		}.draw(Color{ 100,100,100 });
	}
	//Machine

		//Top
	Polygon{
		Vec2{int(hit.left().x) + 100, int(hit.top().y) - 550},
		Vec2{int(hit.left().x) - 50, int(hit.top().y) - 550},
		Vec2{int(hit.left().x) , int(hit.top().y) - 650},
		Vec2{int(hit.left().x) + 150, int(hit.top().y) - 650}
	}.draw(Color{ 210, 210, 210 });
	//Wall
	Rect{ int(hit.left().x) - 50, int(hit.top().y) - 550, 150, 450 }.draw(Color{ 180, 180, 180 });
	Polygon{
		Vec2{int(hit.left().x) + 150, int(hit.top().y) - 650},
		Vec2{int(hit.left().x) + 150, int(hit.top().y) - 550},
		Vec2{int(hit.left().x) + 100, int(hit.top().y) - 450},
		Vec2{int(hit.left().x) + 100, int(hit.top().y) - 550},
	}.draw(Color{ 140, 140, 140 });
	Polygon{
		Vec2{int(hit.left().x) + 110, int(hit.top().y) - 570},
		Vec2{int(hit.left().x) + 110, int(hit.top().y) - 120},
		Vec2{int(hit.left().x) + 100, int(hit.top().y) - 100},
		Vec2{int(hit.left().x) + 100, int(hit.top().y) - 550},
	}.draw(Color{ 140, 140, 140 });
	FontAsset(U"TitleFont")(U"DRY").draw(
		hit.left().x - 40, 300,
		Color{ s3d::Color::value_type(200 + dryAnim[currentDryAnim]), s3d::Color::value_type(200 - dryAnim[currentDryAnim]), 0 }
	);

	//Score
	FontAsset(U"TitleFont")(U"Score {}"_fmt(score)).draw(100, 100);
	FontAsset(U"CombFont")(U"{}"_fmt(comb)).draw(Scene::Center().x, Scene::Center().y - 300);
	//Judge
	for (auto judge : judges) {
		String judgeMsg = U"miss";
		switch (judge.first) {
		case JUDGE::excellent:
			judgeMsg = U"excellent";
			break;
		case JUDGE::good:
			judgeMsg = U"good";
		}
		int32 delta = (currentTime - judge.second)/20;
		textures.at(judgeMsg).draw(
			int32(hit.right().x) + delta,
			int32(hit.top().y - 50) + (delta-10)*(delta-10) - 100
		);
	}
}

void GameScene::loadNotes() {
	TextReader reader{ U"assets\\Songs\\{}.txt"_fmt(data.title)};

	if (not reader)
	{
		throw Error{ U"譜面 {} が見つかりません。"_fmt(data.title) };
	}
	String line;

	reader.readLine(line);

	data.bpm = Parse<uint8>(line);

	Array<String> params;
	while (reader.readLine(line))
	{
		if (line.isEmpty())
		{
			continue;
		}
		params = line.split(' ');

		uint32 timing = 260;
		double one_bar = 240000 / data.bpm;
		for (int i = 0; i < params[1].length(); ++i) {
			timing += one_bar / Math::Pow(4, i) * (params[1].at(i) - '0');
		}

		if (params[0] == U"0")
			notes[upper].push_back(std::shared_ptr<Note>(new Note{ this, timing, &textures[U"broken_apple"] }));
		else
			notes[under].push_back(std::shared_ptr<Note>(new Note{ this, timing, &textures[U"apple"] }));
	}
	for (int i = 0; i < 2; ++i) {
		notes[i].push_back(std::shared_ptr<EndNote>(
			new EndNote{ this, notes[i].back()->getTiming() + 100, &textures[U"invisible"] }
		));
	}
}

//先頭のノートを次に進める
//true:ノートを進めた
//false:次のノートがない
bool GameScene::nextNote(Lane lane) {
	if (frontNoteId[lane] + 1 >= notes[lane].size()) {
		return false;
	}
	frontNoteId[lane]++;
	return true;
}

uint32 GameScene::getComb() {
	return comb;
}
void GameScene::addScere(uint32 s) {
	score += s;
}

uint32 GameScene::getJudgeTiming() {
	return judgeTiming;
}

Texture* GameScene::getTexture(String name) {
	return &textures[name];
}