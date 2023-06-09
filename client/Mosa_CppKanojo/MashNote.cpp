﻿#include"MashNote.h"
#include"Scenes/GameScene.h"

MashNote::MashNote(GameScene* scene, uint32 start, uint32 lenght, uint32 width, Texture* texture) :
	NoteBase(scene, start, texture), lenght(lenght), width(width) {

	for (int i = 0; i < width; i += 80) {
		fruitNames.push_back(scene->getFruit(timing+i));
		fruits.push_back(scene->getTexture(fruitNames.at(i/80)));
	}
}

JUDGE MashNote::hit(int32 delta, Lane lane) {
	JUDGE result = JUDGE::miss;

	if (delta - lenght < int32(scene->getJudgeTiming() / 3) || delta > int32(scene->getJudgeTiming() / 3)) {
		result = JUDGE::good;
		scene->addScere(50);
	}
	int i = (lenght - delta)* scene->getBpm() / 300 / 80;
	if (i >= 0 && i < fruits.size())
		fruits.at(i) = scene->getTexture(U"broken_{}"_fmt(fruitNames.at(i)));
	return result;
}

void MashNote::draw(int hitX, int hitY, int currentTime, int bpm, int lane) {
	int x = int(hitX + (int(timing) - currentTime) * bpm / 300) - 50;
	int y = hitY + lane * 450 - 500;

	for (int i = 0; i < fruits.size(); ++i) {
		Rect{ x + i * 80, y, 100 }(*fruits.at(i)).draw();
	}

	Rect{ x + 50, y + 80, width, 20 }(*scene->getTexture(U"plate")).draw();
}

uint32 MashNote::getTiming() {
	return timing + lenght;
}
