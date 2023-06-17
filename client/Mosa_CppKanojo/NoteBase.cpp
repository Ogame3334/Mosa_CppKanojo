#include"NoteBase.h"
#include"GameScene.h"

NoteBase::NoteBase(GameScene* scene, uint32 timing, Texture* texture) :
	scene(scene), timing(timing), texture(texture) {}

JUDGE NoteBase::hitEnd(int32 delta) {
	return JUDGE::excellent;
}

uint32 NoteBase::getTiming() {
	return timing;
}

const Texture* NoteBase::getTexture() {
	return texture;
}
