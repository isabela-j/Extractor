#pragma once

#include <iostream>

#include "TagExtractor.h"
#include "ui_Extractor.h"
#include "InsertDialog.h"
#include <QTreeWidget>
#include <QMessageBox>

class Extractor final : public QMainWindow
{
Q_OBJECT

public:
	explicit Extractor(QWidget* parent = Q_NULLPTR);
	~Extractor() = default;

private slots:
	void on_actionOpen_triggered();
	void onDeleteTag();
	void onInsertTag();
	void onEditTag();
	void onSaveFile();
	void receiveItem(QString& t_tagId, QString& t_vr, QString& t_vm, QString& t_length, QString& t_description, QString& t_value) const;
	void valueWasSend(QString& t_name) const;
	

private:
	Ui::ExtractorClass ui = {};
	std::unique_ptr<TagExtractor> m_extractor = {};
	std::unique_ptr<InsertDialog> m_insertDialog = {};
	QString m_path={};
	
	
	void createConnections() const;
	
	void AddRootExtractor(QTreeWidgetItem* t_item) const;
	void AddChildExtractor(QTreeWidgetItem* t_item, QTreeWidgetItem* t_root);
	void AddRoot(Items* t_item) const;
	void AddChild(Items* t_item,bool acceptDuplicates, QTreeWidgetItem* t_root) const;

	void presets() const;
	bool shouldDelete(QTreeWidgetItem *t_item);
	bool shouldEdit(QTreeWidgetItem* t_item);
	bool shouldInsert(QTreeWidgetItem* t_item);
	void subtractValueFromGroupLength(QTreeWidgetItem* t_item) const;
	void addValueToGroupLength(QTreeWidgetItem* t_item) const;
	Items* insertItemDelimitators(QTreeWidgetItem* t_root) const;
	Items* insertSequenceDelimitators(QTreeWidgetItem* t_root) const;
	void addInSequence(Items* t_item, QTreeWidgetItem* t_widgetItem) const;

	DcmFileFormat createNewFile();
	bool canBeSaved(const QString& t_tagId);
	void hidden_values(DcmElement* t_newElem, DcmDataset* t_dataset, DcmTagKey& t_tagKey);
	void valueForEVR_ox(DcmElement* t_newElem, DcmDataset* t_originalDataset,DcmDataset* t_newDataset, DcmTagKey& t_tagKey);
	void valueForEVR_FD_OD(DcmElement* t_newElem, Items* t_item);
	void valueForEVR_FL_OF(DcmElement* t_newElem, Items* t_item);
	void valueMultiframeAndVOILUT(DcmDataset* t_dataset, DcmDataset* t_originalDataset,DcmTagKey& t_tagKey);
	void saveNonSequenceRoot(Items* t_item, DcmDataset* t_dataset, DcmTagKey& t_tagKey);
	void saveNonSequenceChild(Items* t_item, DcmItem* t_parentItem, DcmDataset* t_dataset, DcmTagKey& t_tagKey);
	void saveDcmSequenceOfItems(Items* t_item, DcmDataset* t_dataset, std::stack<std::pair<DcmSequenceOfItems*, int>>& t_sequenceStack, DcmTagKey& t_tagKey);
	DcmTagKey getTagKey(Items* t_item);
	DcmTagKey getTagKey(const QString& t_group, const QString &t_element);
};









