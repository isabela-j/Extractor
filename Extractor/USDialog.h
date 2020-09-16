#pragma once

#include "ui_USDialog.h"
#include "USInsertEdit.h"

class USDialog final : public QDialog
{
	Q_OBJECT

public:
	explicit USDialog(QString& t_description, QWidget* parent = Q_NULLPTR);
	~USDialog()=default;
signals:
	void sendValue(QString& t_value);
	
private slots:
	void onInsertPressed() const;
	void onEditPressed() const;
	void onOKPressed();
	void valueWasSend(QString& t_value) const;
	void valueWasChanged(QString& t_value) const;
	void onDeletePressed() const;

private:
	Ui::USDialog ui;
	std::unique_ptr<USInsertEdit> m_insertDialogUS;
	std::unique_ptr<USInsertEdit> m_editDialogUS;
	void presets(QString& t_description) const;
};
