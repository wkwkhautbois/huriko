# include <Siv3D.hpp> // OpenSiv3D v0.6.3

// 定数
constexpr double g = 9.8;
constexpr double L = 2.0;

const double f1(const double t, const double omega) {
	return omega;
}

const double f2(const double t, const double theta) {
	return g / L * std::sin(theta);
}


void Main()
{
	// ウィンドウ設定
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	// 初期値
	double theta = 40.0_deg + 180_deg;
	double omega = 0.0;
	double t = 0.0;

	double dt;

	while (System::Update())
	{
		dt = Scene::DeltaTime();

		const double k1 = f1(t, omega);
		const double k2 = f1(t + dt / 2.0, omega + dt / 2.0 * k1);
		const double k3 = f1(t + dt / 2.0, omega + dt / 2.0 * k2);
		const double k4 = f1(t + dt, omega + dt * k3);

		const double l1 = f2(t, theta);
		const double l2 = f2(t + dt / 2.0, theta + dt / 2.0 * l1);
		const double l3 = f2(t + dt / 2.0, theta + dt / 2.0 * l2);
		const double l4 = f2(t + dt, theta + dt * l3);

		theta = theta + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0 * dt;
		omega = omega + (l1 + 2 * l2 + 2 * l3 + l4) / 6.0 * dt;


		// 描画
		const Vec2 pos = OffsetCircular(Scene::Center(), 200, theta);
		Line(Scene::Center(), pos).draw(4, Palette::Yellow);
		Circle(pos, 20).draw(ColorF(0.2, 0.8, 0.1));
	}
}
