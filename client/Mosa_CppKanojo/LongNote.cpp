#include"LongNote.h"
#include"GameScene.h"

LongNote::LongNote(GameScene* scene, uint32 start, uint32 lenght, uint32 width, Texture* texture) :
	NoteBase(scene, start, texture), lenght(lenght), width(width){
	for (int i = 0; i < width; i += 80) {
		fruits.push_back(texture);
	}
}

JUDGE LongNote::hit(int32 delta, Lane lane) {
	JUDGE result = JUDGE::miss;
	if (lane == upper) {
		delta -= lenght;

		if (delta > -int32(scene->getJudgeTiming())) {
			if (Math::Abs(delta) < int32(scene->getJudgeTiming() / 3)) {
				result = JUDGE::excellent;
				scene->addScere(1000 + scene->getComb() * 10);
			}
			else if (delta > -int32(scene->getJudgeTiming() * 2 / 3)) {
				result = JUDGE::good;
				scene->addScere(500 + scene->getComb() * 5);
			}
		}
		isPushed = true;
	}
	else {
		if (delta < int32(scene->getJudgeTiming())) {
			if (Math::Abs(delta) < int32(scene->getJudgeTiming() / 3)) {
				result = JUDGE::excellent;
				scene->addScere(1000 + scene->getComb() * 10);
			}
			else if (delta < int32(scene->getJudgeTiming() * 2 / 3)) {
				result = JUDGE::good;
				scene->addScere(500 + scene->getComb() * 5);
			}
		}
		isPushed = false;
	}
	return result;
}

void LongNote::draw(int hitX, int hitY, int currentTime, int bpm, int lane){
	int x = int(hitX + (int(timing) - currentTime) * bpm / 300) - 50;
	int y = hitY + lane * 450 - 500;

	for (int i = 0; i < fruits.size(); ++i) {
		Rect{ x + i*80, y, 100 }(*fruits.at(i)).draw();
	}

	Rect{ x + 50, y + 80, width, 20 }.draw(Palette::Brown);
}

void LongNote::update(int currentTime, int bpm) {
	if (isPushed) {
		int l = (currentTime - timing) * bpm/300 / 80;
		if (l >= fruits.size() || l < 0) return;

		fruits.at(l) = scene->getTexture(U"dried_apple");
	}
}

uint32 LongNote::getTiming() {
	return timing + lenght;
}
