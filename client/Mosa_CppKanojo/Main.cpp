# include <Siv3D.hpp>
# include"GameScene.h"
using App = SceneManager<String>;

// タイトルシーン
class Title : public App::Scene
{
public:

	// コンストラクタ（必ず実装）
	Title(const InitData& init)
		: IScene{ init }
	{

	}

	// 更新関数（オプション）
	void update() override
	{
		if (MouseL.down()) changeScene(U"Game");
	}

	// 描画関数（オプション）
	void draw() const override
	{
		Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });

		FontAsset(U"TitleFont")(U"My Game").drawAt(400, 100);

		Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
	}
};

void Main()
{
	FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);
	FontAsset::Register(U"CombFont", 200, Typeface::Heavy);
	FontAsset::Register(U"2PScoreFont", 40, Typeface::Heavy);
	FontAsset::Register(U"2PCombFont", 130, Typeface::Heavy);
	//Audio data = Audio{U"C:\\Users\\hmits\\source\\repos\\Mosa_CppKanojo\\client\\CassisGrape.mp3"};
	// シーンマネージャーを作成
	Window::SetStyle(WindowStyle::Sizable);
	Window::Resize(1920, 1080);

	App manager;

	// タイトルシーン（名前は "Title"）を登録
	manager.add<Title>(U"Title");
	manager.add<GameScene>(U"Game");

	while (System::Update())
	{
		// 現在のシーンを実行
		// シーンに実装した .update() と .draw() が実行される
		if (not manager.update())
		{
			break;
		}
	}
}
