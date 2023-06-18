#pragma once
#include<Siv3D.hpp>
#include"Judge.h"

class NoteBase {
public:
	NoteBase(class GameScene* scene, uint32 timing, Texture* texture);

	virtual JUDGE hit(int32 delta, enum Lane lane) = 0;
	virtual void draw(int hitX, int hitY, int currentTime, int bpm, int lane) = 0;
	virtual void update(int currentTime, int bpm);

	virtual uint32 getTiming();
	const Texture* getTexture();
protected:
	class GameScene* scene;
	uint32 timing;
	Texture* texture;
};
