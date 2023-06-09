﻿#pragma once
#include<Siv3D.hpp>
#include"NoteBase.h"
class Note: public NoteBase {
public:
	Note(class GameScene *scene, uint32 timing, Texture* texture, String fruit);
	JUDGE hit(int32 delta, enum Lane lane) override;
	void draw(int hitX, int hitY, int currentTime, int bpm, int lane) override;
private:
	String fruit;
};

class TestNote : public TestNoteBase {
public:
	TestNote(class MdspeedScene* scene, uint32 timing, Texture* texture);
	JUDGE hit(int32 delta) override;
private:
};
