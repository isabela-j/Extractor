#pragma once

#include <QDialog>
#include "ui_PNDialog.h"

class PNDialog : public QDialog
{
	Q_OBJECT

public:
	PNDialog(QString& t_description, QWidget *parent = Q_NULLPTR);
	~PNDialog();

private slots:
	void onOKPressed();

signals:
	void sendName(QString& t_Name);
private:
	Ui::PNDialog ui;
};
