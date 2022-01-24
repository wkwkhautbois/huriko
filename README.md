# 振り子の動きシミュレーション

単振り子の動きのシミュレーションを、次の式を順次計算することで行います。

![](https://latex.codecogs.com/gif.latex?\theta_{t+1}=\theta_{t}+\omega_{t}\cdot{dt})  
![](https://latex.codecogs.com/gif.latex?\omega_{t+1}=\omega_{t}+\frac{g\cdot{\sin{\theta_{t}}}}{L}\cdot{dt})

※ 座標系は左上原点としています。

![](asset/screenshot.png)

## Huriko1 : オイラー法

Huriko1では、オイラー法による計算を行っています。  
この実装では ![](https://latex.codecogs.com/gif.latex?dt) が十分に小さくないため、計算誤差が累積されて振れ幅が大きくなるのが分かりやすいです。  
また、オイラー法は精度が低めであることも寄与しています。

```cpp
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
```


## Huriko2 : ルンゲ・クッタ法

Huriko2では、ルンゲ・クッタ法による計算を行っています。  
Huriko1のオイラー法よりは計算誤差が小さいルンゲ・クッタ法ですが、こちらも ![](https://latex.codecogs.com/gif.latex?dt) が十分に小さくないため、Huriko1とほぼ同程度に計算誤差が大きいのが見て取れます。

```cpp
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
```

## 利用方法

想定環境

- Windows
- Visual Studio 2022

必要ライブラリ

- OpenSiv3D v0.6.3 [https://github.com/Siv3D/OpenSiv3D](https://github.com/Siv3D/OpenSiv3D)
   

OpenSiv3D SDKをインストール後に、Visual Studio 2022で新規のOpenSiv3Dプロジェクトを作成します。  
その後、作成されたプロジェクト内のMain.cppを、このリポジトリ内のMain.cppに置き換えてください。


参考:  
http://www.isc.meiji.ac.jp/~re00108/ch10/
