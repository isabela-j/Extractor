#pragma once

#include <QDialog>
#include "ui_ULDialog.h"

class ULDialog : public QDialog
{
	Q_OBJECT

public:
	ULDialog(QWidget *parent = Q_NULLPTR);
	~ULDialog();
signals:
	void sendValue(QString& t_value);
private slots:
	void onOKPressed();
private:
	Ui::ULDialog ui;
};
