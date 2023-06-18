#pragma once
#include<Siv3D.hpp>
#include<unordered_map>
#include<memory>
#include"../Judge.h"
#include"./sceneManager.h"
#include "../readUserData.h"
#include"../Button.hpp"

using App = SceneManager<String, GameData>;

class MdspeedScene : public App::Scene {
public:
	MdspeedScene(const InitData& init);
	void update() override;
	void draw() const override;
	bool nextNote();
	uint32 getJudgeTiming();
	Texture* getTexture(String name);
private:
	void loadNotes();
	UserData userData{};
	int32 userTouchSpeed;
	int prev_loopCount;
	// ボタンの作成
	ogm::Button<Rect> decideButton{ Rect{900, 720, 200, 60}, U"調整値の確認" };

	s3d::Array<std::shared_ptr<class TestNoteBase>> notes;
	uint8 frontNoteId;
	Circle hit{100, Scene::Center().y, 50};
	SongData data;
	uint32 currentTime;
	Stopwatch sw{ StartImmediately::Yes };

	uint32 judgeTiming = 250;
	uint32 parmitDilay = 100;
	std::unordered_map<String, Texture> textures;
	Array<std::pair<JUDGE, uint32>> judges;
};
