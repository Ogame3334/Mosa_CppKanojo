#pragma once
#include"NoteBase.h"

class MashNote : public NoteBase {
public:
	MashNote(class GameScene* scene, uint32 start, uint32 lenght, uint32 width, Texture* texture);
	JUDGE hit(int32 delta, enum Lane lane) override;
	void draw(int hitX, int hitY, int currentTime, int bpm, int lane) override;
	uint32 getTiming() override;
private:
	Array<Texture*> fruits;
	uint32 lenght;
	uint32 width;
};
