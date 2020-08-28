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

	void extract(const std::string& t_filePath, std::stack<QTreeWidgetItem*>& t_stack);
	[[nodiscard]]  DcmFileFormat getFile() const { return m_file; }
	
signals:
	void addNewItemInTree(Items* t_item, std::stack<QTreeWidgetItem*>& t_st);

private:
	DcmFileFormat m_file;
	
	void addToStack(const QString& tagId, const QString& VR, const QString& VM, const QString& length,
		const QString& description, const QString& value, std::stack<int>& tmp_stack,
		std::stack<QTreeWidgetItem*>& t_stack);
	void parseXML(const std::ostringstream& t_ss, std::stack<QTreeWidgetItem*>& t_stack);
	void extractElement(QXmlStreamReader* xmlReader, QString& tagId, QString& VR,
		QString& VM, QString& length, QString& description, QString& value);
	void extractSequence(QXmlStreamReader* xmlReader, QString& tagId, QString& VR,
		QString& VM, QString& length, QString& description, QString& value);
};
