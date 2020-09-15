#pragma once

#include <QDialog>
#include "ui_WarningDialog.h"

class WarningDialog : public QDialog
{
	Q_OBJECT

public:
	WarningDialog(QWidget *parent = Q_NULLPTR);
	~WarningDialog();

private:
	Ui::WarningDialog ui;
};
