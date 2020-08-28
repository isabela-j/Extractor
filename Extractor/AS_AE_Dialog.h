#pragma once

#include <QDialog>
#include "ui_ASDialog.h"

class ASDialog : public QDialog
{
	Q_OBJECT

public:
	ASDialog(QString& VR, QString& t_description, QWidget *parent = Q_NULLPTR);
	~ASDialog();
signals:
	void sendValue(QString& t_value);
private slots:
	void onOKPressed();
	
private:
	Ui::ASDialog ui;
	void presetsAS(QString& t_description);
	void presetsAE(QString& t_description);
};
