#pragma once

#include <QDialog>
#include "ui_UniqueIdentifierDialog.h"

class UniqueIdentifierDialog : public QDialog
{
	Q_OBJECT

public:
	UniqueIdentifierDialog(QString& t_description, QWidget *parent = Q_NULLPTR);
	~UniqueIdentifierDialog();
private slots:
	void onOKPressed();
signals:
	void sendValue(QString& t_value);
private:
	Ui::UniqueIdentifierDialog ui;
};
