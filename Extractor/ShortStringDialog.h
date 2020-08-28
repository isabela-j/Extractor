#pragma once

#include <QDialog>
#include "ui_ShortStringDialog.h"

class ShortStringDialog : public QDialog
{
	Q_OBJECT

public:
	ShortStringDialog(QString& t_description,QWidget *parent = Q_NULLPTR);
	~ShortStringDialog();

private slots:
	void onOKPressed();
signals:
	void sendValue(QString& t_value);

private:
	Ui::ShortStringDialog ui;
};
