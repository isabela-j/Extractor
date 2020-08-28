#include "TagExtractor.h"
#include <QDebug>
#include <QXmlStreamReader>
#include <sstream>
#include <stack>
#include <dcmtk/dcmdata/dcfilefo.h>
#include "dcmtk/dcmdata/dctk.h"


void TagExtractor::addToStack(const QString& tagId, const QString& VR, const QString& VM, const QString& length,
                              const QString& description, const QString& value, std::stack<int>& tmp_stack,
                              std::stack<QTreeWidgetItem*>& t_stack)
{
	if (tmp_stack.empty())
	{
		emit addNewItemInTree(new Items(tagId, VR, VM, length, description, value, 0), t_stack);
	}
	else
	{
		emit addNewItemInTree(
			new Items(tagId, VR, VM, length, description, value, static_cast<int>(tmp_stack.size())),
			t_stack);
		tmp_stack.top()--;
		if (tmp_stack.top() == 0)
		{
			emit addNewItemInTree(new Items("(FFFE,E00D)", "", "0",
			                                "0", "Item Delimitation Item", "", tmp_stack.size()), t_stack);
			
			tmp_stack.pop();
			
			emit addNewItemInTree(new Items("(FFFE,E0DD)", "", "0",
			                              "0", "Sequence Delimitation Item", "", tmp_stack.size()), t_stack);
			tmp_stack.pop();
			
			
		}
	}
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

void TagExtractor::parseXML(const std::ostringstream& t_ss, std::stack<QTreeWidgetItem*>& t_stack)
{
	const auto xmlReader =
		std::make_unique<QXmlStreamReader>(QString::fromLatin1(t_ss.str().c_str()));
	std::stack<int> stack = {};
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
				addToStack(tagId, VR, VM, length, description, value, stack, t_stack);
			}
			else if (xmlReader->name() == "sequence")
			{
				extractSequence(xmlReader.get(), tagId, VR,
				                VM, length, description, value);
				addToStack(tagId, VR, VM, length, description, value, stack, t_stack);
				stack.push(1);
				emit addNewItemInTree(new Items("(FFFE,E000)", "", "1",
				                                "Undefined", "Item", " ", stack.size()), t_stack);
			}
			else if (xmlReader->name() == "pixel-item")
			{
				auto attributes = xmlReader->attributes();
				tagId = "(FFFE,E000)";
				length = attributes.value("len").toString();
				value = "Binary hidden";
				addToStack(tagId, VR, VM, length, description, value, stack, t_stack);
			}
			else if (xmlReader->name() == "item")
			{
				auto attributes = xmlReader->attributes();
				auto nrOfChilds = attributes.value("card").toString();
				stack.push(nrOfChilds.toInt());
				
			}
		}
	}
}

////cv
void TagExtractor::extract(const std::string& t_filePath, std::stack<QTreeWidgetItem*>& t_stack)
{
	if (m_file.loadFile(t_filePath.c_str()).bad())
	{
		throw std::runtime_error("Could not load file.");
	}
	m_file.loadAllDataIntoMemory();
	std::ostringstream ss;
	m_file.writeXML(ss, DCMTypes::PF_shortenLongTagValues);
	std::cout << ss.str();
	parseXML(ss, t_stack);
}
