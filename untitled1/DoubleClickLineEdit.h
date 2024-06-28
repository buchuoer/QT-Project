#ifndef DOUBLECLICKLINEEDIT_H
#define DOUBLECLICKLINEEDIT_H

#include <QLineEdit>
#include <QMouseEvent>
#include <QFocusEvent>

class DoubleClickLineEdit : public QLineEdit {
    Q_OBJECT

public:
    DoubleClickLineEdit(QWidget *parent = nullptr) : QLineEdit(parent) {
        setReadOnly(true); // 默认为只读模式
    }

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override {
        QLineEdit::mouseDoubleClickEvent(event); // 调用基类的双击事件处理
        setReadOnly(false); // 双击后设置为可编辑
    }

    void focusInEvent(QFocusEvent *event) override {
        setReadOnly(true); // 当获得焦点时，设置为只读（防止键盘输入）
        if (event->reason() == Qt::MouseFocusReason) { // 如果是通过鼠标获得焦点（即双击）
            setReadOnly(false); // 则允许编辑
        }
        QLineEdit::focusInEvent(event); // 调用基类的焦点获得事件处理
    }

    void focusOutEvent(QFocusEvent *event) override {
        setReadOnly(true); // 当失去焦点时，设置为只读
        QLineEdit::focusOutEvent(event); // 调用基类的焦点失去事件处理
    }
};

#endif // DOUBLECLICKLINEEDIT_H
