#pragma once

#include <QDialog>
#include "ui_UnsignedShortEdit.h"

class UnsignedShortEdit : public QDialog
{
	Q_OBJECT

public:
	UnsignedShortEdit(QWidget *parent = Q_NULLPTR);
	~UnsignedShortEdit();
	void setLineEditValue(const QString& t_value) { ui.lineEditValue->setText(t_value); }
signals:
	void changeValue(QString& t_value);
private slots:
	void onOKPressed();
private:
	Ui::UnsignedShortEdit ui;
	void presets();
};
