#pragma once

#include <qobject.h>
#include <qobjectdefs.h>
#include <stack>
#include <dcmtk/dcmdata/dcfilefo.h>

#include "Items.h"

class QXmlStreamReader;
class QTreeWidgetItem;

class TagExtractor final : public QObject
{
Q_OBJECT
public:
	explicit TagExtractor(QObject* parent = Q_NULLPTR) : QObject(parent){}
	~TagExtractor() = default;

	void extract(const std::string& t_filePath);
	[[nodiscard]]  DcmFileFormat getFile() const { return m_file; }
	
signals:
	void addNewRootInTree(QTreeWidgetItem* t_root);
	void addNewChildInTree(QTreeWidgetItem* t_child, QTreeWidgetItem* t_parent);

private:
	DcmFileFormat m_file;
	
	void addItem(Items* t_item, std::stack<QTreeWidgetItem*>& t_stack);
	void parseXML(const std::ostringstream& t_ss);
	void extractElement(QXmlStreamReader* xmlReader, QString& tagId, QString& VR,
		QString& VM, QString& length, QString& description, QString& value);
	void extractSequence(QXmlStreamReader* xmlReader, QString& tagId, QString& VR,
		QString& VM, QString& length, QString& description, QString& value);
};
