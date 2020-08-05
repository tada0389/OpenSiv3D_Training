#include <Siv3D.hpp>

class CircleManager {
public:
    CircleManager(const double _duration, const double _interval) :
        duration_(_duration), interval_(_interval) {
        eclipsedTime_ = 0.0;
        hue_ = 0;
    }

    void Update() {

        // 大きさ更新
        auto iterator = circles_.begin();
        for (auto it = circles_.begin(); it != circles_.end(); ++it) {
            get<0>(*it) += 200.0 * duration_ * Scene::DeltaTime();
            if (get<0>(*it) >= 200.0) {
                get<0>(*it) = 200.0;
                iterator = it;
            }
        }

        if (iterator != circles_.begin()) {
            circles_.erase(circles_.begin(), std::prev(iterator));
        }

        Print << circles_.size();

        eclipsedTime_ += Scene::DeltaTime();

        if (eclipsedTime_ >= interval_) {
            eclipsedTime_ -= interval_;
            circles_.emplace_back(0.0, HSV(hue_), Cursor::Pos());
            hue_ += 40;
            hue_ %= 360;
        }
    }

    void draw() const{
        for (const auto [r, c, p] : circles_) {
            //Circle(Scene::Center(), r).draw(c);
            Circle(p, r).draw(c).drawFrame(1.0, Palette::Gray);
        }
    }

private:
    Array<std::tuple<double, ColorF, Vec2>> circles_;

    // 円を最大限までの拡大するまでの時間
    double duration_;
    // 次の円が表示されるまでの時間
    double interval_;

    double eclipsedTime_;
    int hue_;
};

void Main() {

    Scene::SetBackground(Palette::White);

    CircleManager circleManager(0.5, 0.15);

    while (System::Update()) {

        circleManager.Update();
        circleManager.draw();
    }
}