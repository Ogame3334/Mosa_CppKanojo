# include <Siv3D.hpp>
# include "Scenes/sceneManager.h"

void Main()
{
	FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);

	// シーンマネージャーを作成
	App manager;

	// タイトルシーン（名前は "Title"）を登録
	manager.add<Title>(U"Title");

	// 曲選択シーン（名前は "Choice"）を登録
	manager.add<Choice>(U"Choice");

	// ゲームシーン（名前は "Game"）を登録
	manager.add<GameScene>(U"Game");

	// 速度調整シーン（名前は"Mdspeed"）を登録
	manager.add<MdspeedScene>(U"Mdspeed");

	// 画面サイズを1920 x 1080に変更
	Window::SetStyle(WindowStyle::Sizable);
	Window::Resize(1920, 1080);

	//Window::SetFullscreen(true);

	System::SetTerminationTriggers(UserAction::NoAction);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
