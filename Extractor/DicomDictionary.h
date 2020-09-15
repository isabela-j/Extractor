#pragma once

#include <QDialog>
#include "ui_DicomDictionary.h"
#include "Items.h"

class DicomDictionary : public QDialog
{
	Q_OBJECT

public:
	DicomDictionary(QWidget *parent = Q_NULLPTR);
	~DicomDictionary();
	void populate() const;
	void presets();
	
signals:
	void insertData(QString& t_group, QString& t_element, QString& t_description, QString& t_VR);

private slots:
	void onSearchPressed() const;
	void onInsertPressed();

private:
	Ui::DicomDictionary ui;
};
