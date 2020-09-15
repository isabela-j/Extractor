#pragma once
#include <QListWidget>
#include "DicomDictionary.h"
#include "ui_InsertDialog.h"


class InsertDialog : public QDialog
{
	Q_OBJECT

public:
	explicit InsertDialog(QWidget *parent = Q_NULLPTR);
	~InsertDialog();
signals:
	void sendItem(QString& t_tagId, QString& t_vr, QString& t_vm, QString& t_length, QString& t_description, QString &t_value);
private slots:
	void onListItems() const;
	void cancelPressed() { this->reject(); }
	void onInsertData(QString& t_group, QString& t_element, QString& t_description, QString& t_VR) const;
	void onInsertPressed();
	void valueWasSent(QString& t_name);
	void sizeWasSent(QString& t_size);
private:
	Ui::InsertDialog m_ui={};
	DicomDictionary* m_dictionary={};
	void presets() const;
	void setGroupElementFormat() const;
};
