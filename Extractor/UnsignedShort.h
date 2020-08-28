#pragma once

#include <QDialog>
#include "ui_UnsignedShort.h"

class UnsignedShort : public QDialog
{
	Q_OBJECT

public:
	UnsignedShort(QWidget *parent = Q_NULLPTR);
	~UnsignedShort();
	
signals:
	void sendValue(QString& t_value);
private slots:
	void onOKPressed();
	
private:
	Ui::UnsignedShort ui;
	void presets();
};
