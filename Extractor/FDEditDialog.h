#pragma once

#include <QDialog>
#include "ui_FDEditDialog.h"

class FDEditDialog : public QDialog
{
	Q_OBJECT

public:
	FDEditDialog(QWidget *parent = Q_NULLPTR);
	~FDEditDialog();
	void setLineEditValue(const QString& t_value) const { m_ui.lineEditValue->setText(t_value); }
private slots:
	void onOKPressed();
signals:
	void changeValue(QString& t_value);
private:
	Ui::FDEditDialog m_ui={};
	void presets() const;
};
