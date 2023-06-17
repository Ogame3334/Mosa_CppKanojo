#include"Scenes/GameScene.h"
#include"Note.h"

GameScene::GameScene(const InitData& init) : IScene{ init }, frontNoteId(0), isStart(false) {
	data = SongData{U"test(bpm_120)", Audio{U"assets\\Songs\\test(bpm_120).mp3"}, 0};
	textures = std::unordered_map<String, Texture>{
		{U"excellent", Texture{U"assets\\Textures\\text_excellent.png"}},
		{U"good", Texture{U"assets\\Textures\\text_good.png"}},
		{U"miss", Texture{U"assets\\Textures\\text_miss.png"}},

		{U"apple", Texture{U"assets\\Textures\\apple.png"}},
		{U"broken_apple", Texture{U"assets\\Textures\\broken_apple.png"}}
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

	currentTime = uint32(data.audio.posSec() * 1000);
	Print << currentTime;

	//update judge message
	if (judges.size() > 0 && currentTime - judges.front().second > 1000) {
		judges.pop_front();
	}

	//decide front node
	int32 difTime = 0;
	for (;3;) { // <- It's so cute!!!
		difTime = int32(notes.at(frontNoteId)->getTiming()) - int32(currentTime);
		if (difTime >= -int32(parmitDilay)) break;
		if (!nextNote()) break;
	}

	//process key controle
	if (KeyF.down() || KeyD.down()) {
		judges.push_back(std::pair<JUDGE, uint32>{
			notes.at(frontNoteId)->hit(difTime), currentTime
		});	
	}
}

void GameScene::draw() const {
	hit.draw();
	for (auto note : notes) {
		//note->getTexture()->drawAt(
		//	Math::Floor(hit.center.x + (int(note->getTiming()) - int(currentTime)) * data.bpm / 400),
		//	Scene::Center().y
		//);
		Rect{
			int32(hit.center.x + (int(note->getTiming()) - int(currentTime)) * data.bpm/ 300) - 50,
			Scene::Center().y - 50, 100
		}(*(note->getTexture())).draw();
	}
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

	while (reader.readLine(line))
	{
		if (line.isEmpty())
		{
			continue;
		}

		uint32 timing = 260;
		double one_bar = 240000 / data.bpm;
		for (int i = 0; i < line.length(); ++i) {
			timing += one_bar / Math::Pow(4, i) * (line.at(i) - '0');
		}

		notes.push_back(std::shared_ptr<Note>(new Note{this, timing, &textures[U"apple"]}));
	}
}

//先頭のノートを次に進める
//true:ノートを進めた
//false:次のノートがない
bool GameScene::nextNote() {
	if (frontNoteId + 1 >= notes.size()) {
		return false;
	}
	frontNoteId++;
	return true;
}

uint32 GameScene::getJudgeTiming() {
	return judgeTiming;
}

Texture* GameScene::getTexture(String name) {
	return &textures[name];
}
