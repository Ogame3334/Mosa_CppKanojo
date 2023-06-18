#include"./NoteBase.h"
#include"Scenes/GameScene.h"

NoteBase::NoteBase(GameScene* scene,uint32 timing, Texture* texture) :
	scene(scene), timing(timing), texture(texture) {}

void NoteBase::update(int currentTime, int bpm) {}

uint32 NoteBase::getTiming() {
	return timing;
}

const Texture* NoteBase::getTexture() {
	return texture;
}


TestNoteBase::TestNoteBase(MdspeedScene* scene, uint32 timing, Texture* texture) :
	scene(scene), timing(timing), texture(texture) {}

JUDGE TestNoteBase::hitEnd(int32 delta) {
	return JUDGE::excellent;
}

uint32 TestNoteBase::getTiming() {
	return timing;
}

const Texture* TestNoteBase::getTexture() {
	return texture;
}