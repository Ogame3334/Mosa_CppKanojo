#include"NoteBase.h"
#include"GameScene.h"

NoteBase::NoteBase(GameScene* scene,uint32 timing, Texture* texture) :
	scene(scene), timing(timing), texture(texture) {}

void NoteBase::update(int currentTime, int bpm) {}

uint32 NoteBase::getTiming() {
	return timing;
}

const Texture* NoteBase::getTexture() {
	return texture;
}
