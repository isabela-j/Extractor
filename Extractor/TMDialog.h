#pragma once

#include <QDialog>
#include "ui_TMDialog.h"

class TMDialog : public QDialog
{
	Q_OBJECT

public:
	TMDialog(QString& t_description,QWidget *parent = Q_NULLPTR);
	~TMDialog();
private slots:
	void onOKPressed();
signals:
	void sendValue(QString& t_value);

private:
	Ui::TMDialog ui;
	void presets(QString& t_description);
};
