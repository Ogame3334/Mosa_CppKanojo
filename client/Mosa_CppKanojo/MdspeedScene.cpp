#include"Scenes/MdspeedScene.h"
#include"Note.h"
#include"readUserData.h"
#include"Button.hpp"

MdspeedScene::MdspeedScene(const InitData& init) : IScene{ init }, frontNoteId(0) {
	data = SongData{U"adjustbpm_120", Audio{ Audio::Stream, U"assets\\TestSong\\adjustbpm_120.mp3", Loop::Yes}, 0};
	textures = std::unordered_map<String, Texture>{
		{U"excellent", Texture{U"assets\\Textures\\text_excellent.png"}},
		{U"good", Texture{U"assets\\Textures\\text_good.png"}},
		{U"miss", Texture{U"assets\\Textures\\text_miss.png"}},

		{U"apple", Texture{U"assets\\Textures\\apple.png"}},
		{U"broken_apple", Texture{U"assets\\Textures\\broken_apple.png"}}
	};
	userTouchSpeed = this->userData.getUserOptionData(U"touchSpeed");
	loadNotes();
	prev_loopCount = 0;

	// ボタンの色設定など
	this->decideButton.setFont(15, Typeface::Regular, FontStyle::Default);
	this->decideButton.setBackColors(ColorF{ 1.0, 0.714, 0.757, 1.0 }, ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.412, 0.706 , 1 });
	this->decideButton.setOutlineWidth(3, 0);
}

void MdspeedScene::update() {
	//play audio
	if (!data.audio.isPlaying()) {
		data.audio.play();
	}
	if (prev_loopCount != data.audio.loopCount() || decideButton.update()) {
		data.audio.stop();
		currentTime = 0;
		notes.clear();
        loadNotes();
		data.audio.play();
	}
	prev_loopCount = data.audio.loopCount();
	currentTime = uint32(data.audio.posSec() * 1000);

	if (KeyEscape.pressed()) {	// ESCキーが押されたら選択画面に戻る&変更を保存
		userData.setUserOptionData(U"touchSpeed", userTouchSpeed);
		changeScene(U"Choice");
	}

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

	double tmp = userTouchSpeed;
	SimpleGUI::Slider(U"速度調整", tmp, -300, 300, Vec2{ 300, 720 }, 50, 300);
	userTouchSpeed = tmp;
}

void MdspeedScene::draw() const {
	hit.draw();
	decideButton.draw();
	FontAsset(U"TitleFont")(U"タイミングを調整する").drawAt(750, 100);
	FontAsset(U"TitleFont")(U"現在の速度調整値:{}"_fmt(userTouchSpeed)).drawAt(750, 650);
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

void MdspeedScene::loadNotes() {
	TextReader reader{ U"assets\\TestSong\\{}.txt"_fmt(data.title)};

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
		uint32 timing = 260 + userTouchSpeed;
		double one_bar = 240000 / data.bpm;
		for (int i = 0; i < line.length(); ++i) {
			timing += one_bar / Math::Pow(4, i) * (line.at(i) - '0');
		}

		notes.push_back(std::shared_ptr<TestNote>(new TestNote{this, timing, &textures[U"apple"]}));
	}
}

//先頭のノートを次に進める
//true:ノートを進めた
//false:次のノートがない
bool MdspeedScene::nextNote() {
	if (frontNoteId + 1 >= notes.size()) {
		return false;
	}
	frontNoteId++;
	return true;
}

uint32 MdspeedScene::getJudgeTiming() {
	return judgeTiming;
}

Texture* MdspeedScene::getTexture(String name) {
	return &textures[name];
}
