#pragma once
#include"NoteBase.h"

class EndNote : public NoteBase {
public:
	EndNote(class GameScene* scene, uint32 timing, Texture* texture);
	JUDGE hit(int32 delta, enum Lane lane);
	void draw(int hitX, int hitY, int currentTime, int bpm, int lane);
private:
};
