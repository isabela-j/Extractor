#include "TagExtractor.h"
#include <QDebug>
#include <QXmlStreamReader>
#include <sstream>
#include <stack>
#include <dcmtk/dcmdata/dcfilefo.h>
#include "dcmtk/dcmdata/dctk.h"


void TagExtractor::addItem(Items* t_item, std::stack<QTreeWidgetItem*>& t_stack)
{	
	t_stack.empty() ? emit addNewRootInTree(t_item) : emit addNewChildInTree(t_item, t_stack.top());
}

void TagExtractor::extractElement(QXmlStreamReader* xmlReader, QString& tagId, QString& VR, QString& VM,
	QString& length, QString& description, QString& value)
{
	const auto attributes = xmlReader->attributes();
	tagId = "(";
	tagId = tagId + attributes.value("tag").toString() + ")";
	tagId = tagId.toUpper();
	VR = attributes.value("vr").toString();
	VM = attributes.value("vm").toString();
	length = attributes.value("len").toString();
	description = attributes.value("name").toString();

	if (description.contains("Unknown Tag & Data"))
	{
		description = "";
	}

	if (attributes.hasAttribute("binary"))
	{
		value = attributes.value("binary").toString();
	}
	else
	{
		value = xmlReader->readElementText();
		value.replace("\n", "");
		value = value.mid(0, 150);
	}
}

void TagExtractor::extractSequence(QXmlStreamReader* xmlReader, QString& tagId, QString& VR, QString& VM,
	QString& length, QString& description, QString& value)
{
	const auto attributes = xmlReader->attributes();

	tagId = "(";
	tagId = tagId + attributes.value("tag").toString() + ")";
	tagId = tagId.toUpper();
	VR = attributes.value("vr").toString();
	VM = attributes.value("card").toString();
	length = attributes.value("len").toString();
	description = attributes.value("name").toString();
	value = ' ';
}

void TagExtractor::parseXML(const std::ostringstream& t_ss)
{
	const auto xmlReader =
		std::make_unique<QXmlStreamReader>(QString::fromLatin1(t_ss.str().c_str()));

	std::stack<QTreeWidgetItem*> stack;
	int level = 0;
	while (!xmlReader->atEnd() && !xmlReader->hasError())
	{
		const auto token = xmlReader->readNext();
		if (token == QXmlStreamReader::StartDocument)
		{
			continue;
		}
		if (token == QXmlStreamReader::StartElement)
		{
			QString tagId, value, VR, VM, length, description;
			if (xmlReader->name() == "element")
			{
				extractElement(xmlReader.get(), tagId, VR,
					VM, length, description, value);
				
				addItem(new Items(tagId, VR, VM, length, description, value, level), stack);
			}
			else if (xmlReader->name() == "sequence")
			{
				extractSequence(xmlReader.get(), tagId, VR,
					VM, length, description, value);

				Items* item = new Items(tagId, VR, VM, length, description, value, level);
				addItem(item, stack);
				stack.push(item);
				level++;
			}
			else if (xmlReader->name() == "item")
			{
				Items* seqItem = new Items("(FFFE,E000)", "", "1", xmlReader->attributes().value("len").toString(), "Item", " ", level);
				addItem(seqItem, stack);
				stack.push(seqItem);
				level++;
			}
			else if (xmlReader->name() == "pixel-item")
			{
				auto attributes = xmlReader->attributes();
				tagId = "(FFFE,E000)";
				length = attributes.value("len").toString();
				value = "Binary hidden";
				addItem(new Items(tagId, VR, VM, length, description, value, level), stack);
			}
		}
		if(token== QXmlStreamReader::EndElement)
		{
			if (xmlReader->name() == "item")
			{
				addItem(new Items("(FFFE,E00D)", "", "0",
					"0", "Item Delimitation Item", "", level), stack);
				stack.pop();
				level--;
			}
			else if (xmlReader->name() == "sequence")
			{
				addItem(new Items("(FFFE,E0DD)", "", "0",
					"0", "Sequence Delimitation Item", "", level), stack);
				stack.pop();
				level--;
			}
		}
	}
}

void TagExtractor::extract(const std::string& t_filePath)
{
	if (m_file.loadFile(t_filePath.c_str()).bad())
	{
		throw std::runtime_error("Could not load file.");
	}
	m_file.loadAllDataIntoMemory();
	std::ostringstream ss;
	m_file.writeXML(ss, DCMTypes::PF_shortenLongTagValues);
	//std::cout << ss.str();
	parseXML(ss);
}
