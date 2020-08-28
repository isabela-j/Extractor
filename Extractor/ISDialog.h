#pragma once

#include <QDialog>
#include "ui_ISDialog.h"

class ISDialog : public QDialog
{
	Q_OBJECT

public:
	ISDialog(QString& t_description, QWidget *parent = Q_NULLPTR);
	~ISDialog();
private slots:
	void onOKPressed();
signals:
	void sendValue(QString& t_value);

private:
	Ui::ISDialog ui;
	void presets(QString& t_description);
};
