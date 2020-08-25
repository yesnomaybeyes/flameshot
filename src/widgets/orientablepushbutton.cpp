// Copyright(c) 2017-2019 Alejandro Sirgo Rica & Contributors
//
// This file is part of Flameshot.
//
//     Flameshot is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     Flameshot is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with Flameshot.  If not, see <http://www.gnu.org/licenses/>.

// Based on https://stackoverflow.com/a/53135675/964478

#include "orientablepushbutton.h"
#include <QPainter>
#include <QStyleOptionButton>
#include <QDebug>
#include <QStylePainter>

namespace {
// no QRect::transposed in old Qt
QRect transposed(const QRect& rect) {
    QSize size = rect.size();
    size.transpose();
    return QRect(rect.topLeft(), size);
}
}

OrientablePushButton::OrientablePushButton(QWidget *parent)
    : QPushButton(parent)
{ }

OrientablePushButton::OrientablePushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{ }

OrientablePushButton::OrientablePushButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text, parent)
{ }

QSize OrientablePushButton::sizeHint() const {
    QSize sh = QPushButton::sizeHint();

    if (m_orientation != OrientablePushButton::Horizontal) {
        sh.transpose();
    }

    return sh;
}

void OrientablePushButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

    QStylePainter painter(this);
    QStyleOptionButton option;
    initStyleOption(&option);

    if (m_orientation == OrientablePushButton::VerticalTopToBottom) {
        painter.rotate(90);
        painter.translate(0, -1 * width());
        option.rect = transposed(option.rect);
    }
    else if (m_orientation == OrientablePushButton::VerticalBottomToTop) {
        painter.rotate(-90);
        painter.translate(-1 * height(), 0);
        option.rect = transposed(option.rect);
    }

    painter.drawControl(QStyle::CE_PushButton, option);
}

OrientablePushButton::Orientation OrientablePushButton::orientation() const {
    return m_orientation;
}

void OrientablePushButton::setOrientation(const OrientablePushButton::Orientation &orientation) {
    m_orientation = orientation;
}
