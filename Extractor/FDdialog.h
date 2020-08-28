#pragma once

#include <QDialog>
#include "ui_FDdialog.h"
#include "FDInsertDialog.h"
#include "FDEditDialog.h"

class FDdialog : public QDialog
{
	Q_OBJECT

public:
	FDdialog(QString& t_description, QWidget *parent = Q_NULLPTR);
	~FDdialog();
signals:
	void sendValue(QString& t_value);
private slots:
	void onInsertPressed();
	void valueWasSend(QString& t_value);

	void onEditPressed();
	void valueWasChanged(QString& t_value);

	void onDeletePressed();

	void onOKPressed();
	
private:
	Ui::FDdialog ui;
	std::unique_ptr<FDInsertDialog> m_insertDialog={};
	std::unique_ptr<FDEditDialog> m_editDialog = {};
	void presets(QString& t_description);
};
