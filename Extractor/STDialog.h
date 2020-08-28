#pragma once

#include <QDialog>
#include "ui_STDialog.h"

class STDialog : public QDialog
{
	Q_OBJECT

public:
	STDialog(QString& t_description, QWidget* parent = Q_NULLPTR);
	~STDialog();
signals:
	void sendValue(QString& t_value);
private slots:
	void onOKPressed();
private:
	Ui::STDialog ui;
	void presets(QString& t_description);
};
