#pragma once

#include <iostream>
#include <QtWidgets/QMainWindow>

#include "TagExtractor.h"
#include "ui_Extractor.h"
#include "InsertDialog.h"
#include <QTreeWidget>
#include <stack>

class Extractor final : public QMainWindow
{
Q_OBJECT

public:
	explicit Extractor(QWidget* parent = Q_NULLPTR);
	~Extractor() = default;

private slots:
	void on_actionOpen_triggered();
	//void onAddNewItemInTree(Items* t_item, std::stack<QTreeWidgetItem*>& t_stack);
	void onDeleteTag();
	void onInsertTag();
	void onEditTag();
	void onSaveFile();
	void receiveItem(Items* t_item);
	void valueWasSend(QString& t_name);
	

private:
	Ui::ExtractorClass ui = {};
	std::unique_ptr<TagExtractor> m_extractor = {};
	std::unique_ptr<InsertDialog> m_insertDialog = {};
	QString m_path={};

	void AddRootExtractor(QTreeWidgetItem* t_item) const;
	void AddChildExtractor(QTreeWidgetItem* t_item, QTreeWidgetItem* t_root);
	void AddRoot(Items* t_item);
	void AddChild(Items* t_item, QTreeWidgetItem* t_root);

	void presets() const;
	bool shouldDelete(QTreeWidgetItem *t_item);
	bool shouldEdit(QTreeWidgetItem* t_item);
	void substractValueFromGroupLength(QTreeWidgetItem* t_item);
	void addValueToGroupLength(QTreeWidgetItem* t_item);

	DcmFileFormat createNewFile();
	bool canBeSaved(const QString& t_tagId);
	void valueForOB(DcmElement* t_elem, DcmDataset* t_dataset, DcmTagKey& t_tagKey);
	void insertNonSequence(Items* t_item, DcmDataset* t_dataset, DcmTagKey& t_tagKey);
	DcmTagKey getTagKey(Items* t_item);
};




