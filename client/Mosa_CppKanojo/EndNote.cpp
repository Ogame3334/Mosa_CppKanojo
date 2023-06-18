#include"EndNote.h"

EndNote::EndNote(class GameScene* scene, uint32 timing, Texture* texture)
	:NoteBase(scene, timing, texture){}

JUDGE EndNote::hit(int32 delta, Lane n) { return miss; }

void EndNote::draw(int hitX, int hitY, int currentTime, int bpm, int lane) {}
