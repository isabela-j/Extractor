#pragma once

#include<QLineEdit>
#include "ui_CSDialog.h"

class CSDialog final: public QDialog
{
	Q_OBJECT

public:
	explicit CSDialog(QString& t_description,QWidget *parent = Q_NULLPTR);
	~CSDialog()=default;

private slots:
	void onOKPressed();
	void lineEditChanged();
signals:
	void sendValue(QString& t_value);
private:
	Ui::CSDialog ui;
	void presets(QString& t_description);
	QString m_value;
	QLineEdit* m_lineEdit;
};
