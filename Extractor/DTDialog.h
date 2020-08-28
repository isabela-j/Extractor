#pragma once

#include <QDialog>
#include "ui_DTDialog.h"

class DTDialog : public QDialog
{
	Q_OBJECT

public:
	DTDialog(QString& t_description, QWidget *parent = Q_NULLPTR);
	~DTDialog();
signals:
	void sendValue(QString& t_value);
private slots:
	void onOKPressed();

private:
	Ui::DTDialog ui;
	void presets(QString& t_description);
};
