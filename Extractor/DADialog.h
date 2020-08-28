#pragma once

#include <QDialog>
#include "ui_DADialog.h"

class DADialog : public QDialog
{
	Q_OBJECT

public:
	DADialog(QString& t_description, QWidget *parent = Q_NULLPTR);
	~DADialog();
private slots:
	void onOKPressed();
signals:
	void sendValue(QString& t_value);

private:
	Ui::DADialog ui;
	void presets(QString& t_description);
};
