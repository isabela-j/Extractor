#pragma once

#include <QDialog>
#include "ui_AbstractVRDialog.h"

class AbstractVRDialog : public QDialog
{
	Q_OBJECT

public:
	AbstractVRDialog(const QString& t_description, QWidget *parent = Q_NULLPTR);
	~AbstractVRDialog()=default;
signals:
	virtual void sendValue(QString& t_value);
private slots:
	virtual void onOKPressed();	
protected:
	Ui::AbstractVRDialog m_ui={};
private:
	virtual void presets(const QString& t_description) = 0;
};
