﻿#pragma once
#include<Siv3D.hpp>
#include<unordered_map>
#include<memory>
#include"../Judge.h"
#include"./sceneManager.h"

using App = SceneManager<String, GameData>;

enum Lane {
	upper,
	under
};

class GameScene : public App::Scene {
public:
	GameScene(const InitData& init);
	void update() override;
	void draw() const override;
	bool nextNote(Lane lane);
	void addScere(uint32 s);
	uint32 getComb();
	uint32 getJudgeTiming();
	Texture* getTexture(String name);
private:
	void loadNotes();

	//Notes
	std::array<Array<std::shared_ptr<class NoteBase>>, 2> notes;
	std::array<uint8, 2> frontNoteId;
	//Hit
	Circle hit{ 300, Scene::Center().y + 300, 50 };
	//SongData
	SongData data;
	//Timer
	uint32 currentTime;
	Stopwatch sw{ StartImmediately::Yes };

	bool isStart;
	bool isPressing;
	//Consts
	uint32 judgeTiming = 250;
	uint32 parmitDilay = 100;
	//Texture
	std::unordered_map<String, Texture> textures;
	//Score
	uint32 score = 0;
	uint32 comb = 0;
	Array<std::pair<JUDGE, uint32>> judges;

	std::array<uint16, 4> pressAnim{ 350, 200, 250, 300 };
	uint8 currentAnim = 0;
	std::array<int, 4> dryAnim{ 0, 25, 50, 25 };
	uint8 currentDryAnim = 0;
};