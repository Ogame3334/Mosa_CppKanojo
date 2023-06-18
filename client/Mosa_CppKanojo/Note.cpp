#include"Note.h"
#include"GameScene.h"
Note::Note(GameScene* scene, uint32 timing, Texture* texture):
	NoteBase(scene, timing, texture) {}

JUDGE Note::hit(int32 delta, Lane lane) {
	JUDGE result = JUDGE::miss;

	if (lane == end) return JUDGE::none;

	if (delta < int32(scene->getJudgeTiming())) {
		if (delta < int32(scene->getJudgeTiming() / 3)) {
			result = JUDGE::excellent;
			scene->addScere(1000 + scene->getComb() * 10);
		}
		else if (delta < int32(scene->getJudgeTiming() * 2 / 3)) {
			result = JUDGE::good;
			scene->addScere(500 + scene->getComb() * 5);
		}

		texture = lane == under?scene->getTexture(U"broken_apple"):scene->getTexture(U"dried_apple");
		scene->nextNote(lane);
	}
	return result;
}

void Note::draw(int hitX, int hitY, int currentTime, int bpm, int lane) {
	Rect{
		int(hitX + (int(timing) - currentTime) * bpm / 300) - 50,
		hitY + lane * 450 - 500, 100
	}(*texture).draw();
}
