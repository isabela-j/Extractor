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
	void onAddNewItemInTree(Items* t_item, std::stack<QTreeWidgetItem*>& t_stack);
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

	void AddRoot(Items* t_item, std::stack<QTreeWidgetItem*>& t_stack) const;
	void AddChild(Items* t_item, QTreeWidgetItem* t_root, std::stack<QTreeWidgetItem*>& t_stack);
	void AddRoot(Items* t_item);
	void AddChild(Items* t_item, QTreeWidgetItem* t_root);

	void presets() const;
	bool shouldDelete(QTreeWidgetItem *t_item);
	bool shouldEdit(QTreeWidgetItem* t_item);
	void substractValueFromGroupLength(QTreeWidgetItem* t_item);
	void addValueToGroupLength(QTreeWidgetItem* t_item);

	DcmFileFormat createNewFile();
	bool canBeSaved(const QString& t_tagId);
};


