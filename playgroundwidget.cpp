#include "playgroundwidget.h"
#include "datautilsinl.h"


#include <QGridLayout>
#include <QPushButton>

#define CELL_STYLE_TEMPLATE    "background-color: rgb(%1,%2,%3); border: %4px solid rgb(%5,%6,%7); border-radius: 5px;"
//#define CELL_STYLE_EMPTY    (QString(CELL_STYLE_TEMPLATE).arg(143).arg(143).arg(143).arg(0)) //"background-color: rgb(162, 143, 143); border-width: 0px; border-radius: 0px;"
//#define BORDER_STYLE_EMPTY     "border-style: none;"
#define BORDER_STYLE_TEMPLATE  "border-style: none; background-color: rgb(%1, %2, %3);"

#define PROPERTY_COLOR_NAME        "prop_color"
#define PROPERTY_BORDER_COLOR_NAME "prop_border_color"
#define PROPERTY_BORDER_SIZE       "prop_border_size"

CPlaygroundWidget::CPlaygroundWidget(QWidget *parent) :
    QWidget(parent),
    m_defaultCellColor(QColor(143, 143, 143)),
    m_defaultBorderColor(QColor(255, 255, 255))
{
    memset(&m_buttonArray, 0, sizeof(m_buttonArray));

    setMaximumSize(100, 100);

    m_grid = new QGridLayout(this);
    m_grid->setSpacing(0);

    for (size_t i = 0; i < DefinesArraySize; i++)
    {
        for (size_t j = 0; j < DefinesArraySize; j++)
        {
            QPushButton *pButton = new QPushButton(this);
            m_buttonArray[i][j] = pButton;
            m_grid->addWidget(pButton, i, j, 1, 1);
        }
    }


    resetPlayground();


//    addVerticalBorder(7, 0);
//    addHorizontalBorder(7,7);
//    addHorizontalBorder(2,4);
//    addVerticalBorder(3,6);
//    setCellText("5",0,0);
//    setCellText("15",0,7);
//    setCellColor(Qt::red, 3,8);
//    setCellColor(Qt::green, 3,7);
//    addPlayer(4, 0, FinishPosotionBottom);
//    addPlayer(0, 4, FinishPosotionRight);
//    addPlayer(8, 4, FinishPosotionLeft);
//    addPlayer(4, 8, FinishPosotionTop);

}

CPlaygroundWidget::~CPlaygroundWidget()
{
    //delete ui;
}

QPushButton* CPlaygroundWidget::getArrayCell(unsigned char x, unsigned char y)
{

#ifdef ENABLE_PARAMS_CHECKING
    checkCellCoordinates(x, y);
#endif

    return m_buttonArray[y * 2][x * 2];
}


QPushButton* CPlaygroundWidget::getHorizontalBorder(unsigned char x, unsigned char y)
{

#ifdef ENABLE_PARAMS_CHECKING
    checkBorderCoordinates(x, y);
#endif

    return m_buttonArray[x * 2 + 1][y * 2];
}


QPushButton* CPlaygroundWidget::getVerticalBorder(unsigned char x, unsigned char y)
{

#ifdef ENABLE_PARAMS_CHECKING
    checkBorderCoordinates(x, y);
#endif

    return m_buttonArray[y * 2][x * 2 + 1];
}


QPushButton* CPlaygroundWidget::getHorizontalBorderCross(unsigned char x, unsigned char y)
{

#ifdef ENABLE_PARAMS_CHECKING
    checkBorderCrossCoordinates(x, y);
#endif

    return m_buttonArray[x * 2 + 1][y * 2 + 1];
}

QPushButton* CPlaygroundWidget::getVerticalBorderCross(unsigned char x, unsigned char y)
{

#ifdef ENABLE_PARAMS_CHECKING
    checkBorderCrossCoordinates(x, y);
#endif

    return m_buttonArray[y * 2 + 1][x * 2 + 1];
}

void CPlaygroundWidget::addHorizontalBorder(unsigned char x, unsigned char y)
{

#ifdef ENABLE_PARAMS_CHECKING
    checkAddBorderCoordinates(x, y);
#endif

    static const QColor color(143, 89, 2);

    setBorderStyle(getHorizontalBorder(x, y), color);
    setBorderStyle(getHorizontalBorderCross(x, y), color);
    setBorderStyle(getHorizontalBorder(x, y + 1), color);

}

void CPlaygroundWidget::addVerticalBorder(unsigned char x, unsigned char y)
{

#ifdef ENABLE_PARAMS_CHECKING
    checkAddBorderCoordinates(x, y);
#endif

    static const QColor color(143, 89, 2);


    setBorderStyle(getVerticalBorder(x, y), color);
    setBorderStyle(getVerticalBorderCross(x, y), color);
    setBorderStyle(getVerticalBorder(x, y + 1), color);

}

void CPlaygroundWidget::setCellText(const QString &str, unsigned char x, unsigned char y)
{
    getArrayCell(x,y)->setText(str);
}


void CPlaygroundWidget::setCellColor(const QColor &color, unsigned char x, unsigned char y)
{
    setCellStyle(x, y, color);
}

void CPlaygroundWidget::setCellStyle(QPushButton* button, QColor color, int border, QColor borderColor)
{

#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(button);
#endif

    if (!color.isValid())
    {
        color = QColor(143, 143, 143);
        QVariant variant = button->property(PROPERTY_COLOR_NAME);
        if (variant.isValid())
            color = variant.value<QColor>();
    }

    if (!borderColor.isValid())
    {
        borderColor = QColor(143, 143, 143);
        QVariant variant = button->property(PROPERTY_BORDER_COLOR_NAME);
        if (variant.isValid())
            borderColor = variant.value<QColor>();
    }

    if (border < 0)
    {
        border = 0;
        QVariant variant = button->property(PROPERTY_BORDER_SIZE);
        if (variant.isValid())
            border = variant.toUInt();
    }

    button->setProperty(PROPERTY_COLOR_NAME, QVariant(color));
    button->setProperty(PROPERTY_BORDER_COLOR_NAME, QVariant(borderColor));
    button->setProperty(PROPERTY_BORDER_SIZE, QVariant((unsigned int)border));

    button->setStyleSheet(QString(CELL_STYLE_TEMPLATE).arg(color.red()).arg(color.green()).arg(color.blue()).arg(border)
                          .arg(borderColor.red()).arg(borderColor.green()).arg(borderColor.blue()));
}

void CPlaygroundWidget::setCellStyle(unsigned char x, unsigned char y, QColor color, int border, QColor borderColor)
{
    setCellStyle(getArrayCell(x,y), color, border, borderColor);
}

void CPlaygroundWidget::addPlayer(unsigned char x, unsigned char y, FinishPosition position)
{

#ifdef ENABLE_PARAMS_CHECKING
    Q_ASSERT_X(position >= FinishPositionFirst && position <= FinishPositionLast, "SearchAlg::checkFinishRoute", QString("finishPosition is out of range: %1").arg(static_cast<size_t>(position)).toStdString().c_str());
#endif

    static const QColor playersColors[PlayerDataDefines::PlayerCount] = {Qt::red, Qt::green, Qt::blue, Qt::yellow};
    QColor color = playersColors[position];
    setCellColor(color, x, y);
    setCellText("P", x, y);

    char dx = -1;
    char dy = -1;

    if (position == FinishPosotionTop || position == FinishPosotionBottom)
    {
        dy = position == FinishPosotionTop ? 0 : PlaygroundLinesDataDefines::LinesCount;

        for (size_t i = 0; i < PlaygroundLinesDataDefines::LineLength; i++)
            setCellStyle(i, dy, QColor(), 5, color);
    }
    else
    {
        dx = position == FinishPosotionLeft ? 0 : PlaygroundLinesDataDefines::LinesCount;

        for (size_t i = 0; i < PlaygroundLinesDataDefines::LineLength; i++)
            setCellStyle(dx, i, QColor(), 5, color);
    }
}


void CPlaygroundWidget::setBorderStyle(QPushButton* button, QColor color)
{

#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(button);
#endif

    if (!color.isValid())
        color = QColor(255, 255, 255);

    button->setStyleSheet(QString(BORDER_STYLE_TEMPLATE).arg(color.red()).arg(color.green()).arg(color.blue()));
}



void CPlaygroundWidget::showRoute(unsigned char x, unsigned char y, FinishPosition position, PlaygroundData *playgroundData, PlaygroundCellsMap *stepsMap)
{

#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(playgroundData);
    Q_CHECK_PTR(stepsMap);
#endif

    resetPlayground();

    addPlayer(x, y, position);

    readBordersFromPlaygroundData(playgroundData);

    for (size_t i = 0; i < PlaygroundLinesDataDefines::PlaygroundSize; i++)
        for (size_t j = 0; j < PlaygroundLinesDataDefines::PlaygroundSize; j++)
        {
            if (stepsMap->map[i][j] != 255)
                setCellText(QString::number(stepsMap->map[i][j]), i, j);
        }
}

void CPlaygroundWidget::showAvaliableBorderPosition(PlaygroundData *playgroundData, const std::list<PlayerActionAdd*> &actions)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(playgroundData);
#endif

    resetPlayground();

    readBordersFromPlaygroundData(playgroundData);

    std::list<PlayerActionAdd*>::const_iterator it = actions.begin();

    static const QColor color = Qt::red;
    static const QColor colorHor = Qt::green;
    static const QColor colorVert = Qt::blue;

    while(it != actions.end())
    {
        const PlayerActionAdd* pItem = *it;

        const unsigned char x = pItem->point.x;
        const unsigned char y = pItem->point.y;

        if (pItem->action.type == IPlayerAction::addHorizontalLine)
        {
            addHorizontalBorder(x, y);
            setHorizontalBorderStyle(x, y, color);
            // to hightlight the begginning of the border
            setBorderStyle(getHorizontalBorder(x, y), colorHor);

        }
        else
        {
            addVerticalBorder(x, y);
            setVerticalBorderStyle(x, y, color);
            // to hightlight the begginning of the border
            setBorderStyle(getVerticalBorder(x, y), colorVert);
        }


        ++it;
    }
}



void CPlaygroundWidget::readBordersFromPlaygroundData(PlaygroundData *data)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(data);
#endif

    size_t i = 0;
    size_t j = 0;

    i = 0;
    while (i < PlaygroundLinesDataDefines::LinesCount)
    {
        j = 0;
        while (j < PlaygroundLinesDataDefines::LineLength)
        {
            if (PlaygroundLinesDataInl::value(&data->horizontalLines, i, j) != 0)
            {
                addHorizontalBorder(i,j);
                ++j;
            }
            ++j;
        }
        ++i;
    }

    i = 0;
    while (i < PlaygroundLinesDataDefines::LinesCount)
    {
        j = 0;
        while (j < PlaygroundLinesDataDefines::LineLength)
        {
            if (PlaygroundLinesDataInl::value(&data->verticalLines, i, j) != 0)
            {
                addVerticalBorder(i,j);
                ++j;
            }
            ++j;
        }
        ++i;
    }
}

void CPlaygroundWidget::resetPlayground()
{
    for (size_t i = 0; i < DefinesArraySize; i++)
        for (size_t j = 0; j < DefinesArraySize; j++)
        {
            QPushButton *pButton = m_buttonArray[i][j];

            pButton->setProperty(PROPERTY_COLOR_NAME, m_defaultCellColor);
            pButton->setProperty(PROPERTY_BORDER_COLOR_NAME, m_defaultBorderColor);
            pButton->setProperty(PROPERTY_BORDER_SIZE, 0);

            if (i % 2 == 0)
            {
                // line with cells and borders between cells
                if (j % 2 == 0)
                {
                    // cell
                    pButton->setMinimumSize(DefinesCellSize, DefinesCellSize);
                    pButton->setMaximumSize(DefinesCellSize, DefinesCellSize);
                    setCellStyle(pButton);
                    //pButton->setStyleSheet(CELL_STYLE_EMPTY);
                }
                else
                {
                    // border between horizontal cells
                    pButton->setMinimumSize(DefinesBorderHeight, DefinesBorderWidth);
                    pButton->setMaximumSize(DefinesBorderHeight, DefinesBorderWidth);
                    setBorderStyle(pButton);
                }
            }
            else
            {
                // line with only borders
                if (j % 2 == 0)
                {
                    // border between vertical cells
                    pButton->setMinimumSize(DefinesBorderWidth, DefinesBorderHeight);
                    pButton->setMaximumSize(DefinesBorderWidth, DefinesBorderHeight);
                    setBorderStyle(pButton);
                }
                else
                {
                    // border between vertical borders
                    pButton->setMinimumSize(DefinesBorderHeight, DefinesBorderHeight);
                    pButton->setMaximumSize(DefinesBorderHeight, DefinesBorderHeight);
                    setBorderStyle(pButton);
                }
            }
        }
}


void CPlaygroundWidget::setHorizontalBorderStyle(unsigned char x, unsigned char y, QColor color)
{
#ifdef ENABLE_PARAMS_CHECKING
    checkAddBorderCoordinates(x, y);
#endif

    setBorderStyle(getHorizontalBorder(x, y), color);
    setBorderStyle(getHorizontalBorderCross(x, y), color);
    setBorderStyle(getHorizontalBorder(x, y + 1), color);
}

void CPlaygroundWidget::setVerticalBorderStyle(unsigned char x, unsigned char y, QColor color)
{
#ifdef ENABLE_PARAMS_CHECKING
    checkAddBorderCoordinates(x, y);
#endif

    setBorderStyle(getVerticalBorder(x, y), color);
    setBorderStyle(getVerticalBorderCross(x, y), color);
    setBorderStyle(getVerticalBorder(x, y + 1), color);
}

bool CPlaygroundWidget::checkCellCoordinates(unsigned char x, unsigned char y)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_ASSERT_X(x < PlaygroundLinesDataDefines::PlaygroundSize, "CPlaygroundWidget::checkCellCoordinates", QString("x coord is out of range: %1").arg(x).toStdString().c_str());
    Q_ASSERT_X(y < PlaygroundLinesDataDefines::PlaygroundSize, "CPlaygroundWidget::checkCellCoordinates", QString("y coord is out of range: %1").arg(y).toStdString().c_str());
#endif

    return (x < PlaygroundLinesDataDefines::PlaygroundSize && y < PlaygroundLinesDataDefines::PlaygroundSize);
}

bool CPlaygroundWidget::checkBorderCoordinates(unsigned char x, unsigned char y)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_ASSERT_X(x < PlaygroundLinesDataDefines::LinesCount, "CPlaygroundWidget::checkBorderCoordinates", QString("x coord is out of range: %1").arg(x).toStdString().c_str());
    Q_ASSERT_X(y < PlaygroundLinesDataDefines::LineLength, "CPlaygroundWidget::checkBorderCoordinates", QString("y coord is out of range: %1").arg(y).toStdString().c_str());
#endif

    return (x < PlaygroundLinesDataDefines::LinesCount && y < PlaygroundLinesDataDefines::LineLength);
}

bool CPlaygroundWidget::checkBorderCrossCoordinates(unsigned char x, unsigned char y)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_ASSERT_X(x < PlaygroundLinesDataDefines::LinesCount, "CPlaygroundWidget::checkBorderCrossCoordinates", QString("x coord is out of range: %1").arg(x).toStdString().c_str());
    Q_ASSERT_X(y < PlaygroundLinesDataDefines::LineLength - 1, "CPlaygroundWidget::checkBorderCrossCoordinates", QString("y coord is out of range: %1").arg(y).toStdString().c_str());
#endif

    return (x < PlaygroundLinesDataDefines::LinesCount && y < PlaygroundLinesDataDefines::LineLength - 1);
}

bool CPlaygroundWidget::checkAddBorderCoordinates(unsigned char x, unsigned char y)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_ASSERT_X(x < PlaygroundLinesDataDefines::LinesCount, "CPlaygroundWidget::checkAddBorderCoordinates", QString("x coord is out of range: %1").arg(x).toStdString().c_str());
    Q_ASSERT_X(y < PlaygroundLinesDataDefines::LineLength - 1, "CPlaygroundWidget::checkAddBorderCoordinates", QString("y coord is out of range: %1").arg(y).toStdString().c_str());
#endif

    return (x < PlaygroundLinesDataDefines::LinesCount && y < PlaygroundLinesDataDefines::LineLength - 1);
}

