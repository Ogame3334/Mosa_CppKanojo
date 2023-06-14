#include"ResultScene.h"


ResultScene::ResultScene(const InitData& init)
	: IScene{ init }
{}

// 更新関数（オプション）
void ResultScene::update(){
	if (SimpleGUI::Button(U"toTitle", Vec2{ Scene::Size().x / 2 - 100, Scene::Size().y/2 + 100}, 200))
	{
		changeScene(U"Title");
	}
}

void ResultScene::draw() const{
	Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });

	FontAsset(U"TitleFont")(U"Result").drawAt(Scene::Size().x / 2, Scene::Size().y/2 - 100);
	FontAsset(U"TitleFont")(U"Score {}"_fmt(getData().score)).drawAt(Scene::Size().x / 2, Scene::Size().y/2);
	Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
}
