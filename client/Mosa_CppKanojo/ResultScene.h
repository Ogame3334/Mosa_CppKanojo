#pragma once
#include<Siv3D.hpp>
#include"GameData.h"
using App = SceneManager<String, GameData>;
class ResultScene : public App::Scene {
public:
	ResultScene(const InitData& init);

	void update() override;

	void draw() const override;
private:
};
