# include <Siv3D.hpp>

void Main()
{
    // 使用する画像
    const Image image(U"example/siv3d-kun.png");

    // アルファ値 1 以上の領域を Polygon 化
    const Polygon polygon = image.alphaToPolygon(1, false);

    // テクスチャ
    const Texture texture(image);

    // 移動のオフセット
    constexpr Vec2 pos(40, 40);

    // Polygon 単純化時の基準距離（ピクセル）
    double maxDistance = 4.0;

    // 単純化した Polygon
    Polygon simplifiedPolygon = polygon.simplified(maxDistance);

    while (System::Update())
    {
        // 単純化した Polygon の頂点数を表示
        ClearPrint();
        Print << simplifiedPolygon.vertices().size() << U" vertices";

        texture.draw(pos);

        // 単純化した Polygon を表示
        simplifiedPolygon.movedBy(pos)
            .draw(ColorF(1.0, 1.0, 0.0, 0.2))
            .drawWireframe(2, Palette::Yellow);

        // 単純化した Polygon をマウスカーソルに追従させて表示
        simplifiedPolygon.movedBy(Cursor::Pos() - image.size() / 2)
            .draw(ColorF(0.5));

        // Polygon 単純化時の基準距離を制御
        if (SimpleGUI::Slider(U"{:.1f}"_fmt(maxDistance), maxDistance, 0.0, 30.0, Vec2(400, 40), 60, 200))
        {
            // スライダーに変更があれば、単純化した Polygon を新しい基準値で再作成
            simplifiedPolygon = polygon.simplified(maxDistance);
        }
    }
}