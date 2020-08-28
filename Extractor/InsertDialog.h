#pragma once
#include <QListWidget>
#include "DicomDictionary.h"
#include "ui_InsertDialog.h"
#include "PNDialog.h"
#include "LongStringDialog.h"
#include "ShortStringDialog.h"
#include "UniqueIdentifierDialog.h"

class InsertDialog : public QDialog
{
	Q_OBJECT

public:
	explicit InsertDialog(QWidget *parent = Q_NULLPTR);
	~InsertDialog();
signals:
	void sendItem(Items* t_item);
private slots:
	void onListItems() const;
	void cancelPressed() { this->reject(); }
	void onInsertData(QString& t_group, QString& t_element, QString& t_description, QString& t_VR);
	void onInsertPressed();
	void valueWasSend(QString& t_name);
private:
	Ui::InsertDialog ui={};
	DicomDictionary* m_dictionary={};
	void presets();
};
