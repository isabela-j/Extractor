#pragma once

#include <QDialog>
#include "ui_PNDialog.h"

class PNDialog final: public QDialog
{
	Q_OBJECT

public:
	explicit PNDialog(QString& t_description, QWidget *parent = Q_NULLPTR);
	~PNDialog() =default;

private slots:
	void onOKPressed();

signals:
	void sendName(QString& t_Name);
private:
	Ui::PNDialog ui;
};
