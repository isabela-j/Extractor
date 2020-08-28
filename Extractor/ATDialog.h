#pragma once

#include <QDialog>
#include "ui_ATDialog.h"

class ATDialog : public QDialog
{
	Q_OBJECT

public:
	ATDialog(QString& t_description, QWidget *parent = Q_NULLPTR);
	~ATDialog();
signals:
	void sendValue(QString& t_value);
private slots:
	void onOKPressed();
private:
	Ui::ATDialog ui;
	void presets(QString& t_description);
};
