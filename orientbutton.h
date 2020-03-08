#ifndef ORIENTBUTTON_H
#define ORIENTBUTTON_H

#include <QPushButton>

class OrientablePushButton : public QPushButton
{
Q_OBJECT
public:
    enum Orientation {
        Horizontal,
        VerticalTopToBottom,
        VerticalBottomToTop
    };

    OrientablePushButton(QWidget * parent = nullptr);
    OrientablePushButton(const QString & text, QWidget *parent = nullptr);
    OrientablePushButton(const QIcon & icon, const QString & text, QWidget *parent = nullptr);

    QSize sizeHint() const;

    OrientablePushButton::Orientation orientation() const;
    void setOrientation(const OrientablePushButton::Orientation &orientation);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Orientation mOrientation = Horizontal;
};

#endif // ORIENTBUTTON_H
