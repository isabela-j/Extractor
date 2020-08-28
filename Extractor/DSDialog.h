#pragma once

#include <QDialog>
#include "ui_DSDialog.h"

class DSDialog : public QDialog
{
	Q_OBJECT

public:
	DSDialog(QString& t_description, QWidget *parent = Q_NULLPTR);
	~DSDialog();
signals:
	void sendValue(QString& t_value);
private slots:
	void onOKPressed();

private:
	Ui::DSDialog ui;
	void presets(QString& t_description);
};
