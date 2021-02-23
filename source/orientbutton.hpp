#ifndef ORIENTBUTTON_HPP
#define ORIENTBUTTON_HPP

#include <QPushButton>

class OrientablePushButton : public QPushButton {
public:
    enum Orientation {
        Horizontal,
        VerticalTopToBottom,
        VerticalBottomToTop
    };

    OrientablePushButton(QWidget *parent = nullptr);
    OrientablePushButton(const QString &text, QWidget *parent);
    OrientablePushButton(const QIcon &icon, const QString &text, QWidget *parent);

    QSize sizeHint() const;

    OrientablePushButton::Orientation orientation() const;
    void setOrientation(const OrientablePushButton::Orientation &orientation);

    virtual ~OrientablePushButton() {}

protected:
    void paintEvent(QPaintEvent *event);

private:
    Orientation mOrientation = Horizontal;
};

#endif // ORIENTBUTTON_HPP
