#include "QColorPicker.h"

#include <QSignalBlocker>

QColorPicker::QColorPicker(QWidget * parent)
    : QWidget(parent)
    , mMixedColor{ new QLabel }
{
    const int fixedWidgetSize{ 75 };

    mMixedColor->setFixedWidth(fixedWidgetSize);

    QVBoxLayout* channelsLayout{ new QVBoxLayout };
    channelsLayout->addLayout(createChannel("Rouge", mRedTitle, mRedSB, mRedValue, mRedColor, fixedWidgetSize));
    channelsLayout->addLayout(createChannel("Vert", mGreenTitle, mGreenSB, mGreenValue, mGreenColor, fixedWidgetSize));
    channelsLayout->addLayout(createChannel("Bleu", mBlueTitle, mBlueSB, mBlueValue, mBlueColor, fixedWidgetSize));

    QHBoxLayout* mixedColorLayout{ new QHBoxLayout };
    mixedColorLayout->addLayout(channelsLayout);
    mixedColorLayout->addWidget(mMixedColor);

    QVBoxLayout* centralLayout{ new QVBoxLayout };
    centralLayout->addLayout(mixedColorLayout);
    centralLayout->addStretch();

    setLayout(centralLayout);
}


QColor QColorPicker::color() const
{
    return QColor(mRedSB->value(), mGreenSB->value(), mBlueSB->value());
}

void QColorPicker::setColor(QColor const & color)
{
    QSignalBlocker redBlocker(mRedSB);
    QSignalBlocker greenBlocker(mGreenSB);
    QSignalBlocker blueBlocker(mBlueSB);
    mRedSB->setValue(color.red());
    mGreenSB->setValue(color.green());
    mBlueSB->setValue(color.blue());
    updateColors();
}

QHBoxLayout* QColorPicker::createChannel(QString const& titleText, QLabel*& title, QScrollBar*& sb, QLabel*& value, QLabel*& color, int width)
{
    title = new QLabel;
    value = new QLabel;
    color = new QLabel;
    sb = new QScrollBar;

    title->setText(titleText);
    title->setFixedWidth(width);
    value->setText("0");
    value->setFixedWidth(width);
    value->setAlignment(Qt::AlignCenter);
    color->setText("");
    color->setFixedWidth(width);
    sb->setRange(0, 255);
    sb->setValue(0);
    sb->setMinimumWidth(width);
    sb->setOrientation(Qt::Horizontal);

    QHBoxLayout* layout{ new QHBoxLayout };
    layout->addWidget(title);
    layout->addWidget(sb);
    layout->addWidget(value);
    layout->addWidget(color);

    connect(sb, &QScrollBar::valueChanged,
        value, static_cast<void(QLabel::*)(int)>(&QLabel::setNum));
    connect(sb, &QScrollBar::valueChanged,
        this, &QColorPicker::updateColors);

    return layout;
}

void QColorPicker::updateColor(QLabel* label, int red, int green, int blue)
{
    QPixmap pixmap(label->size());
    pixmap.fill(QColor(red, green, blue));
    label->setPixmap(pixmap);
}

void QColorPicker::updateColors()
{
    updateColor(mRedColor, mRedSB->value(), 0, 0);
    updateColor(mGreenColor, 0, mGreenSB->value(), 0);
    updateColor(mBlueColor, 0, 0, mBlueSB->value());
    updateColor(mMixedColor, mRedSB->value(), mGreenSB->value(), mBlueSB->value());

    emit colorChanged(color());
}
