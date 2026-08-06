import QtQuick

Text {

    enum Type {

        Display,
        Title,
        Heading,
        Body,
        Caption

    }

    property int type: GameText.Body
    font.family: Typography.family
    color: Theme.text
    renderType: Text.QtRendering
    font.hintingPreference: Font.PreferFullHinting


    font.pixelSize: {

        switch(type){

        case GameText.Display:

            return Typography.display

        case GameText.Title:

            return Typography.title

        case GameText.Heading:

            return Typography.heading

        case GameText.Body:

            return Typography.body

        case GameText.Caption:

            return Typography.caption

        }
    }


}