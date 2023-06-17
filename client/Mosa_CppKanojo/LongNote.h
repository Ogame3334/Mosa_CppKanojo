#pragma once
#include"NoteBase.h"

class LongNote : public NoteBase {
	LongNote(class GameScene* scene, uint32 start, uint32 end, Texture* texture);
	JUDGE hit(int32 delta) override;
	JUDGE hitEnd(int32 delta) override;
};
