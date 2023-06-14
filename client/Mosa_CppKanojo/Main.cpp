# include <Siv3D.hpp>
#include "Scenes/titleScene.h"

using App = SceneManager<String>;

// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init)
		: IScene{ init }
		, m_texture{ U"🐈"_emoji }
	{
		Print << U"Game::Game()";
	}

	~Game()
	{
		Print << U"Game::~Game()";
	}

	void update() override
	{
		// 左クリックで
		if (MouseL.down())
		{
			// タイトルシーンに遷移
			changeScene(U"Title");
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF(0.2, 0.8, 0.6));

		m_texture.drawAt(Cursor::Pos());
	}

private:

	Texture m_texture;
};

void Main()
{
	FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);

	// シーンマネージャーを作成
	App manager;

	// タイトルシーン（名前は "Title"）を登録
	manager.add<Title>(U"Title");

	// ゲームシーン（名前は "Game"）を登録
	manager.add<Game>(U"Game");

	// 画面サイズを1920 x 1080に変更
	Window::SetStyle(WindowStyle::Sizable);
	Window::Resize(1920, 1080);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
