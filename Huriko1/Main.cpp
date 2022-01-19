# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void Main()
{
	// ウィンドウ設定
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	// 定数
	constexpr double g = 9.8;
	constexpr double L = 2.0;

	// 初期値
	double theta = 40.0_deg + 180_deg;
	double omega = 0.0;


	double dt;

	while (System::Update())
	{
		dt = Scene::DeltaTime();

		// オイラー法で現在の角度thetaと角速度omegaを計算
		double theta1 = theta + omega * dt;
		double omega1 = omega + g * std::sin(theta) / L * dt;

		theta = theta1;
		omega = omega1;


		// 描画
		const Vec2 pos = OffsetCircular(Scene::Center(), 200, theta);
		Line(Scene::Center(), pos).draw(4, Palette::Yellow);
		Circle(pos, 20).draw(ColorF(0.2, 0.8, 0.1));
	}
}
