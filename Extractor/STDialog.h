#pragma once

#include <QDialog>
#include "ui_STDialog.h"

class STDialog : public QDialog
{
	Q_OBJECT

public:
	STDialog(const QString& t_description, QWidget *parent = Q_NULLPTR);
	~STDialog() = default;
signals:
	void sendValue(QString& t_value);
private slots:
	void onOKPressed();
private:
	Ui::STDialog m_ui;
	void presets(const QString& t_description);
};
