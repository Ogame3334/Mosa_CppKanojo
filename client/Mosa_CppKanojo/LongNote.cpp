#include"./LongNote.h"
#include"Scenes/GameScene.h"

LongNote::LongNote(GameScene* scene, uint32 start, uint32 end, Texture* texture) :
	NoteBase(scene, start, texture)
{}

JUDGE LongNote::hit(int32 delta) {
	return JUDGE::excellent;
}

JUDGE LongNote::hitEnd(int32 delta) {
	return JUDGE::excellent;
}
