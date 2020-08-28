#pragma once

#include <QDialog>
#include "ui_FDInsertDialog.h"

class FDInsertDialog : public QDialog
{
	Q_OBJECT

public:
	FDInsertDialog(QWidget *parent = Q_NULLPTR);
	~FDInsertDialog();
signals:
	void sendValue(QString& t_value);
private slots:
	void onOKPressed();
private:
	Ui::FDInsertDialog ui;
	void presets();
};
