#ifndef PLAYGROUNDWIDGET_H
#define PLAYGROUNDWIDGET_H

#include <structures.h>

#include <QWidget>
#include <QColor>

//namespace Ui {
//class CPlaygroundWidget;
//}

class QGridLayout;
class QPushButton;

class CPlaygroundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CPlaygroundWidget(QWidget *parent = 0);
    ~CPlaygroundWidget();

    void showRoute(unsigned char x, unsigned char y, FinishPosition position, const PlaygroundData *playgroundData, PlaygroundCellsMap *stepsMap);
    void showAvaliableBorderPosition(const PlaygroundData *playgroundData, const std::list<PlayerActionAddBorder*> &actions);
    void showAvaliablePlayerActions(const GameData *gameData, uint playerIndex, const std::list<IPlayerAction*> &actions);
    void showGame(const GameData *gameData);


    static void showGameStatic(const GameData *gameData);
    static void showGameChangesStatic(const GameData *gameData);

private:
    enum Defines
    {
        DefinesArraySize       = (PlaygroundLinesDataDefines::PlaygroundSize * 2 - 1),
        DefinesPartSize        = 8,
        DefinesCellPart        = 5,
        DefinesBorderPart      = 1,
        DefinesCellSize        = DefinesPartSize * DefinesCellPart,
        DefinesBorderHeight    = DefinesPartSize * DefinesBorderPart,
        DefinesBorderWidth     = DefinesCellSize,
    };

    QGridLayout *m_grid;
    QPushButton* m_buttonArray[DefinesArraySize][DefinesArraySize];
    QColor m_defaultCellColor;
    QColor m_defaultBorderColor;

    QPushButton* getArrayCell(unsigned char x, unsigned char y);
    QPushButton* getVerticalBorder(unsigned char x, unsigned char y);
    QPushButton* getHorizontalBorder(unsigned char x, unsigned char y);
    QPushButton* getHorizontalBorderCross(unsigned char x, unsigned char y);
    QPushButton* getVerticalBorderCross(unsigned char x, unsigned char y);

    void addHorizontalBorder(unsigned char x, unsigned char y);
    void addVerticalBorder(unsigned char x, unsigned char y);

    void setHorizontalBorderStyle(unsigned char x, unsigned char y, QColor color = QColor());
    void setVerticalBorderStyle(unsigned char x, unsigned char y, QColor color = QColor());

    void setCellText(const QString &str, unsigned char x, unsigned char y);
    void setCellColor(const QColor &color, unsigned char x, unsigned char y);
    void setCellStyle(unsigned char x, unsigned char y, QColor color = QColor(), int border = -1, QColor borderColor = QColor());

    static void setCellStyle(QPushButton* button, QColor color = QColor(), int border = -1, QColor borderColor = QColor());
    static void setBorderStyle(QPushButton* button, QColor color = QColor());

    void addPlayer(unsigned char x, unsigned char y, FinishPosition position);

    void resetPlayground();

    void readBordersFromPlaygroundData(const PlaygroundData *data);

    static bool checkCellCoordinates(unsigned char x, unsigned char y);
    static bool checkBorderCoordinates(unsigned char x, unsigned char y);
    static bool checkBorderCrossCoordinates(unsigned char x, unsigned char y);
    static bool checkAddBorderCoordinates(unsigned char x, unsigned char y);
};

#endif // PLAYGROUNDWIDGET_H
