#ifndef REMARKINPUT_H
#define REMARKINPUT_H

#include <QDialog>

namespace Ui {
    class RemarkInput;
}

class RemarkInput : public QDialog {
    Q_OBJECT

    Ui::RemarkInput *ui;
    QString remark;

public:
    explicit RemarkInput(QWidget *parent = nullptr, QString label = "");
    ~RemarkInput();
    QString getRemark();

private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // REMARKINPUT_H
