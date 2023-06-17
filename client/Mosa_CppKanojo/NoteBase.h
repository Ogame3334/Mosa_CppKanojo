#pragma once
#include<Siv3D.hpp>
#include"Judge.h"

class NoteBase {
public:
	NoteBase(class GameScene* scene, uint32 timing, Texture* texture);
	virtual JUDGE hit(int32 delta) = 0;
	virtual JUDGE hitEnd(int32 delta);
	uint32 getTiming();
	const Texture* getTexture();
protected:
	class GameScene* scene;
	uint32 timing;
	Texture* texture;
};
