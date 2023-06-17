#include"Note.h"
#include"GameScene.h"
Note::Note(GameScene* scene ,uint32 timing, Texture* texture):
	NoteBase(scene, timing, texture) {}

JUDGE Note::hit(int32 delta) {
	JUDGE result = JUDGE::miss;

	if (delta < int32(scene->getJudgeTiming())) {
		if (delta < int32(scene->getJudgeTiming() / 3))
			result = JUDGE::excellent;
		else if(delta < int32(scene->getJudgeTiming() * 2 / 3))
			result = JUDGE::good;

		texture = scene->getTexture(U"broken_apple");
		scene->nextNote();
	}
	return result;
}
