#pragma once

#include <QWidget>
#include <QLabel>
#include <QScrollBar>
#include <QHBoxLayout>

class QColorPicker : public QWidget
{
	Q_OBJECT

public:
    QColorPicker(QWidget * parent = nullptr);
    ~QColorPicker() = default;

    QColor color() const;

public slots:
    void setColor(const QColor& color);

signals:
    void colorChanged(QColor color);

private:
    QLabel* mRedTitle;
    QLabel* mRedValue;
    QLabel* mRedColor;
    QScrollBar* mRedSB;
    QLabel* mGreenTitle;
    QLabel* mGreenValue;
    QLabel* mGreenColor;
    QScrollBar* mGreenSB;
    QLabel* mBlueTitle;
    QLabel* mBlueValue;
    QLabel* mBlueColor;
    QScrollBar* mBlueSB;
    QLabel* mMixedColor;

    QHBoxLayout* createChannel(QString const& titleText, QLabel*& title, QScrollBar*& sb, QLabel*& value, QLabel*& color, int width);
    void updateColor(QLabel* label, int red, int green, int blue);

private slots:
    void updateColors();
};

