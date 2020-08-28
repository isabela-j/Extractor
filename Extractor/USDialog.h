#pragma once

#include <QDialog>

#include "InsertDialog.h"
#include "ui_USDialog.h"
#include "UnsignedShort.h"
#include "UnsignedShortEdit.h"
class USDialog : public QDialog
{
	Q_OBJECT

public:
	USDialog(QString& t_description, QWidget* parent = Q_NULLPTR);
	~USDialog();
signals:
	void sendValue(QString& t_value);
	
private slots:
	void onInsertPressed();
	void onEditPressed();
	void onOKPressed();
	void valueWasSend(QString& t_value);
	void valueWasChanged(QString& t_value);
	void onDeletePressed();

private:
	Ui::USDialog ui;
	std::unique_ptr<UnsignedShort> m_insertDialogUS;
	std::unique_ptr<UnsignedShortEdit> m_editDialogUS;
	void presets(QString& t_description);
};
