#pragma once

#include <QDialog>
#include "ui_LongStringDialog.h"

class LongStringDialog : public QDialog
{
	Q_OBJECT

public:
	LongStringDialog(QString &t_description, QWidget *parent = Q_NULLPTR);
	~LongStringDialog();

private slots:
	void onOKPressed();

signals:
	void sendValue(QString& t_value);
	
private:
	Ui::LongStringDialog ui;
};
