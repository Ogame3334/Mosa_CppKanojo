#pragma once
#include"NoteBase.h"

class EndNote : public NoteBase {
public:
	EndNote(class GameScene* scene, uint32 timing, Texture* texture);
	JUDGE hit(int32 delta, enum Lane lane);
private:
};
