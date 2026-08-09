import QtQuick
import "../../Core"

Text {
    id: root

    enum Type {
        Display,
        Title,
        Heading,
        Body,
        Caption
    }

    property int type: GameText.Type.Body

    font.family: Typography ? Typography.family : "Arial" // Bảo vệ nếu Typography chưa load xong
    color: Theme ? Theme.text : "#FFFFFF"                  // Bảo vệ nếu Theme chưa load xong
    renderType: Text.QtRendering
    font.hintingPreference: Font.PreferFullHinting

    // SỬA TẠI ĐÂY: Bảo vệ switch-case bằng cách kiểm tra biến `Typography` trước
    font.pixelSize: {
        // Nếu Singleton Typography chưa khởi tạo xong, trả về tạm một kích thước mặc định (ví dụ: 16)
        if (!Typography) return 16;

        switch(type) {
        case GameText.Type.Display:
            return Typography.display
        case GameText.Type.Title:
            return Typography.title
        case GameText.Type.Heading:
            return Typography.heading
        case GameText.Type.Body:
            return Typography.body
        case GameText.Type.Caption:
            return Typography.caption
        default:
            return Typography.body
        }
    }
}
