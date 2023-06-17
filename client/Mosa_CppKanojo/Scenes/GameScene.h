#pragma once
#include<Siv3D.hpp>
#include<unordered_map>
#include<memory>
#include"../Judge.h"
#include"./sceneManager.h"

using App = SceneManager<String, GameData>;

struct SongData {
	String title;
	Audio audio;
	uint8 bpm;
};

class GameScene : public App::Scene {
public:
	GameScene(const InitData& init);
	void update() override;
	void draw() const override;
	bool nextNote();
	uint32 getJudgeTiming();
	Texture* getTexture(String name);
private:
	void loadNotes();

	s3d::Array<std::shared_ptr<class NoteBase>> notes;
	uint8 frontNoteId;
	Circle hit{100, Scene::Center().y, 50};
	SongData data;
	uint32 currentTime;
	Stopwatch sw{ StartImmediately::Yes };

	bool isStart;
	uint32 judgeTiming = 250;
	uint32 parmitDilay = 100;
	std::unordered_map<String, Texture> textures;
	Array<std::pair<JUDGE, uint32>> judges;
};
