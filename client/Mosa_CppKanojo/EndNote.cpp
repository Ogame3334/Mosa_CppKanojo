#include"EndNote.h"

EndNote::EndNote(class GameScene* scene, uint32 timing, Texture* texture)
	:NoteBase(scene, timing, texture){}

JUDGE EndNote::hit(int32 delta, Lane n) { return miss; }
