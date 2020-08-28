#include "DicomDictionary.h"
#include <dcmtk/dcmdata/dcdict.h>
#include <dcmtk/dcmdata/dcdicent.h>
#include <regex>

DicomDictionary::DicomDictionary(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	presets();
	populate();
}

DicomDictionary::~DicomDictionary()
{
}

void DicomDictionary::presets()
{
	ui.tableWidget->setColumnCount(4);
	QStringList ColumnNames;
	ColumnNames << "Group" << "Element" << "Tag Description" << "VR";
	ui.tableWidget->setHorizontalHeaderLabels(ColumnNames);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void DicomDictionary::onSearchPressed()
{
	auto const description = ui.lineEdit->text();
	if(description.isEmpty())
	{
		populate();
	}
	else
	{
		if (ui.tableWidget->rowCount() != 3889)
		{
			populate();
		}
		auto rows = ui.tableWidget->rowCount();
		for(int i=rows-1; i>=0;i--)
		{
			if (!ui.tableWidget->item(i, 2)->text().contains(description,Qt::CaseSensitive))
				ui.tableWidget->removeRow(i);
		}
		
	}
}

void DicomDictionary::onInsertPressed()
{
	if(!ui.tableWidget->selectedItems().isEmpty())
	{
		auto row = ui.tableWidget->selectedItems()[0]->row();
		auto group = ui.tableWidget->item(row, 0)->text();
		auto element = ui.tableWidget->item(row, 1)->text();
		auto description= ui.tableWidget->item(row, 2)->text();
		auto VR= ui.tableWidget->item(row, 3)->text();
		emit insertData(group, element, description, VR);
	}
}



void DicomDictionary::populate()
{
	auto* dictionary = new DcmDataDictionary(true, false);
	DcmHashDictIterator iterStart = dictionary->normalBegin();
	const DcmHashDictIterator iterEnd = dictionary->normalEnd();
	auto count = 0;
	ui.tableWidget->setRowCount(0);
	while (iterStart != iterEnd)
	{
		const DcmDictEntry* item = *iterStart;
		QString key = item->getBaseTag().toString().c_str();
		key=key.toUpper();
		QString description = item->getTagName();
		QString vr = item->getVR().getVRName();

		if (key != "(FFFE,E00D)" && key != "(FFFE,E000)" && key !="(FFFE,E0DD)"
			&& !description.contains("Retired", Qt::CaseInsensitive))
		{
			ui.tableWidget->insertRow(count);
			ui.tableWidget->setItem(count, 0, new QTableWidgetItem(key.mid(1,4)));
			ui.tableWidget->setItem(count, 1, new QTableWidgetItem(key.mid(6, 4)));
			ui.tableWidget->setItem(count, 2, new QTableWidgetItem(description,0));
			ui.tableWidget->setItem(count, 3, new QTableWidgetItem(vr,0));
			count++;
		}
	
		++iterStart;
		
	}
	ui.tableWidget->sortItems(0, Qt::AscendingOrder);
	ui.tableWidget->resizeColumnsToContents();
	delete dictionary;
}

