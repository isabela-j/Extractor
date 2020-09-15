#include "ExtractorGUI.h"

#include <iostream>
#include <QDebug>

#include <QFileDialog>
#include <dcmtk/dcmdata/dcfilefo.h>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dcistrmb.h>

#include "ATDialog.h"
#include "CSDialog.h"
#include "DADialog.h"
#include "DSDialog.h"
#include "DTDialog.h"
#include "FDdialog.h"
#include "ISDialog.h"
#include "PNDialog.h"
#include "STDialog.h"
#include "AEDialog.h"
#include "ASDialog.h"
#include "LODialog.h"
#include "SHDialog.h"
#include "TMDialog.h"
#include "UIDialog.h"
#include "ULDialog.h"

#include "USDialog.h"
#include "WarningDialog.h"

Extractor::Extractor(QWidget* parent)
	: QMainWindow(parent), m_extractor(std::make_unique<TagExtractor>()), m_insertDialog(std::make_unique<InsertDialog>())
{
	ui.setupUi(this);
	createConnections();
	presets();
}

void Extractor::presets() const
{
	ui.treeWidget->setColumnCount(6);
	QStringList ColumnNames;
	ColumnNames << "Tag ID" << "VR" << "VM" << "Length" << "Description" << "Value";
	ui.treeWidget->setHeaderLabels(ColumnNames);
	ui.treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.pushButtonEdit->setEnabled(false);
	ui.pushButtonDelete->setEnabled(false);
	ui.pushButtonInsert->setEnabled(false);
	ui.pushButton->setEnabled(false);
}

void Extractor::createConnections()
{
	Q_UNUSED(connect(m_extractor.get(), &TagExtractor::addNewChildInTree, this, &Extractor::AddChildExtractor));
	Q_UNUSED(connect(m_extractor.get(), &TagExtractor::addNewRootInTree, this, &Extractor::AddRootExtractor));
	Q_UNUSED(connect(m_insertDialog.get(), &InsertDialog::sendItem, this, &Extractor::receiveItem));
}

void Extractor::AddRootExtractor(QTreeWidgetItem* t_item) const
{
	ui.treeWidget->addTopLevelItem(t_item);
	t_item->setExpanded(true);
}

void Extractor::AddChildExtractor(QTreeWidgetItem* t_item, QTreeWidgetItem* t_root)
{
	t_root->addChild(t_item);
	t_item->setExpanded(true);
}

void Extractor::AddRoot(Items* t_item) const
{
	auto items = ui.treeWidget->findItems(t_item->text(0), Qt::MatchExactly, 0);
	if (items.count())
	{
		delete items[0];
	}
	ui.treeWidget->addTopLevelItem(t_item);
	t_item->setExpanded(true);
	ui.treeWidget->scrollToItem(t_item);
	ui.treeWidget->setCurrentItem(t_item);
}

void Extractor::AddChild(Items* t_item, QTreeWidgetItem* t_root) const
{
	auto i = 0;
	while (i < t_root->childCount())
	{
		if (t_root->child(i)->text(0) == t_item->text(0))
		{
			t_root->takeChild(i);
		}
		i++;
	}
	t_root->addChild(t_item);
	t_item->setExpanded(true);
	ui.treeWidget->scrollToItem(t_item);
	ui.treeWidget->setCurrentItem(t_item);
}

void Extractor::on_actionOpen_triggered()
{
	m_path =
		QFileDialog::getOpenFileName(this, "Select file",
			"", "");
	ui.treeWidget->clear();
	if (!m_path.isEmpty())
	{
		m_extractor->extract(m_path.toStdString());
	}
	ui.treeWidget->sortItems(0, Qt::SortOrder::AscendingOrder);
	ui.pushButtonEdit->setEnabled(true);
	ui.pushButtonDelete->setEnabled(true);
	ui.pushButtonInsert->setEnabled(true);
	ui.pushButton->setEnabled(true);
}

bool Extractor::shouldDelete(QTreeWidgetItem* t_item)
{
	auto contains = false;
	if (t_item->text(4) == "PhotometricInterpretation" || t_item->text(4) == "Rows"
		|| t_item->text(4) == "Columns" || t_item->text(4).contains("Pixel")
		|| t_item->text(4).contains("Frame") || t_item->text(4).contains("Item")
		|| t_item->text(4).contains("Bit") || t_item->text(4).contains("Implementation")
		|| t_item->text(4).contains("TransferSyntax") || t_item->text(5).contains("hidden"))
	{
		contains = true;
	}

	if (t_item->text(0).contains("0000") || t_item->text(0).contains("0001") || contains)
	{
		return false;
	}
	return true;
}

bool Extractor::shouldEdit(QTreeWidgetItem* t_item)
{
	if (t_item->text(4) == "PhotometricInterpretation" || t_item->text(4) == "Rows"
		|| t_item->text(4) == "Columns" || t_item->text(4).contains("Pixel")
		|| t_item->text(4).contains("Item") || t_item->text(4).contains("Bit")
		|| t_item->text(4).contains("TransferSyntax") || t_item->text(0).contains("0000") || t_item->text(5).contains("hidden"))
	{
		return false;
	}

	return true;
}

bool Extractor::shouldInsert(QTreeWidgetItem* t_item)
{
	auto ok = false;
	if (!t_item->text(0).contains("FFFE,E00D") &&
		!t_item->text(0).contains("FFFE,E0DD") &&
		!t_item->text(0).contains("Pixel"))
	{
		ok = true;
	}
	if (t_item->childCount())
	{
		auto* const child = t_item->child(0);
		return(child->text(0) != "(FFFE,E0DD)" && ok);
	}
	return ok;
}


void Extractor::subtractValueFromGroupLength(QTreeWidgetItem* t_item) const
{
	auto const val = t_item->text(3).toInt();
	auto const group = t_item->text(0).mid(1, 4);
	auto const tagId = "(" + group + ",0000)";
	auto const items = ui.treeWidget->findItems(tagId, Qt::MatchExactly, 0);
	if (items.count())
	{
		auto const totalValue = items.at(0)->text(5).toInt();
		auto const remainedValue = std::to_string((totalValue - 8 - val));
		items.at(0)->setText(5, remainedValue.c_str());
		if (!items.at(0)->text(5).toInt())
		{
			delete items.at(0);
		}
	}
}



void Extractor::addValueToGroupLength(QTreeWidgetItem* t_item) const
{
	auto const tagId = "(" + t_item->text(0).mid(1, 4) + ",0000)";
	auto const val = t_item->text(3).toInt() + 8;
	const auto items = ui.treeWidget->findItems(tagId, Qt::MatchExactly, 0);
	if (!items.count())
	{
		AddRoot(new Items(tagId, "UL", "1", "4", "Group Length", std::to_string(val).c_str(), 0));
	}
	else
	{
		auto const initialValue = items.at(0)->text(5).toInt();
		auto const newValue = std::to_string((initialValue + val));
		items.at(0)->setText(5, newValue.c_str());
	}

}


void Extractor::onDeleteTag()
{
	if (!ui.treeWidget->selectedItems().isEmpty())
	{
		if (shouldDelete(ui.treeWidget->selectedItems()[0]))
		{
			subtractValueFromGroupLength(ui.treeWidget->selectedItems()[0]);
			delete ui.treeWidget->selectedItems()[0];
			return;
		}
	}
	int warning = QMessageBox::warning(this, tr("Warning found"),
		tr("You are not allowed to do this operation."), QMessageBox::Cancel);
}

void Extractor::onInsertTag()
{
	if (!ui.treeWidget->selectedItems().isEmpty())
	{

		if (shouldInsert(ui.treeWidget->selectedItems()[0]))
		{
			m_insertDialog->exec();
			return;
		}
	}
	int warning = QMessageBox::warning(this, tr("Warning found"), 
		tr("You are not allowed to do this operation."), QMessageBox::Cancel);
}


void Extractor::onEditTag() //todo
{
	if (!ui.treeWidget->selectedItems().isEmpty())
	{
		if (shouldEdit(ui.treeWidget->selectedItems()[0]))
		{
			subtractValueFromGroupLength(ui.treeWidget->selectedItems()[0]);

			auto description = ui.treeWidget->selectedItems()[0]->text(4);
			if (ui.treeWidget->selectedItems()[0]->text(1) == "PN")
			{
				auto* pnDialog = new PNDialog(description, this);
				Q_UNUSED(connect(pnDialog, &PNDialog::sendName, this, &Extractor::valueWasSend));
				pnDialog->exec();
				
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "LO")
			{
				auto* loDialog = new LODialog(description, this);
				Q_UNUSED(connect(loDialog, &LODialog::sendValue, this, &Extractor::valueWasSend));
				loDialog->exec();
				
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "SH")
			{
				auto* shDialog = new SHDialog(description, this);
				Q_UNUSED(connect(shDialog, &SHDialog::sendValue, this, &Extractor::valueWasSend));
				shDialog->exec();
				
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "UI")
			{
				auto* uiDialog = new UIDialog(description, this);
				Q_UNUSED(connect(uiDialog, &UIDialog::sendValue, this, &Extractor::valueWasSend));
				uiDialog->exec();
			
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "DA")
			{
				auto* daDialog = new DADialog(description, this);
				Q_UNUSED(connect(daDialog, &DADialog::sendValue, this, &Extractor::valueWasSend));
				daDialog->exec();
			
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "TM")
			{
				auto* tmDialog = new TMDialog(description, this);
				Q_UNUSED(connect(tmDialog, &TMDialog::sendValue, this, &Extractor::valueWasSend));
				tmDialog->exec();
		
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "IS")
			{
				auto* isDialog = new ISDialog(description, this);
				Q_UNUSED(connect(isDialog, &ISDialog::sendValue, this, &Extractor::valueWasSend));
				isDialog->exec();
			
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "CS")
			{
				auto* csDialog = new CSDialog(description, this);
				Q_UNUSED(connect(csDialog, &CSDialog::sendValue, this, &Extractor::valueWasSend));
				csDialog->exec();
				
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "AS")
			{
				auto* asDialog = new ASDialog( description, this);
				Q_UNUSED(connect(asDialog, &ASDialog::sendValue, this, &Extractor::valueWasSend));
				asDialog->exec();
				
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "AE")
			{
				auto* aeDialog = new AEDialog(description, this);
				Q_UNUSED(connect(aeDialog, &AEDialog::sendValue, this, &Extractor::valueWasSend));
				aeDialog->exec();
				
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "DS")
			{
				auto* dsDialog = new DSDialog(description, this);
				Q_UNUSED(connect(dsDialog, &DSDialog::sendValue, this, &Extractor::valueWasSend));
				dsDialog->exec();
			
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "US" ||
				ui.treeWidget->selectedItems()[0]->text(1) == "SS")
			{
				auto* usDialog = new USDialog(description, this);
				Q_UNUSED(connect(usDialog, &USDialog::sendValue, this, &Extractor::valueWasSend));
				usDialog->exec();
				
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "FD"
				|| ui.treeWidget->selectedItems()[0]->text(1) == "FL")
			{
				auto* fdDialog = new FDdialog(description, this);
				Q_UNUSED(connect(fdDialog, &FDdialog::sendValue, this, &Extractor::valueWasSend));
				fdDialog->exec();
				
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "AT")
			{
				auto* atDialog = new ATDialog(description, this);
				Q_UNUSED(connect(atDialog, &ATDialog::sendValue, this, &Extractor::valueWasSend));
				atDialog->exec();
			
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "DT")
			{
				auto* dtDialog = new DTDialog(description, this);
				Q_UNUSED(connect(dtDialog, &DTDialog::sendValue, this, &Extractor::valueWasSend));
				dtDialog->exec();
			
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "ST"
				|| ui.treeWidget->selectedItems()[0]->text(1) == "UT"
				|| ui.treeWidget->selectedItems()[0]->text(1) == "LT")
			{
				auto* stDialog = new STDialog(description, this);
				Q_UNUSED(connect(stDialog, &STDialog::sendValue, this, &Extractor::valueWasSend));
				stDialog->exec();
				delete stDialog;
			}
			else if (ui.treeWidget->selectedItems()[0]->text(1) == "UL")
			{
				auto* ulDialog = new ULDialog(description,this);
				Q_UNUSED(connect(ulDialog, &ULDialog::sendValue, this, &Extractor::valueWasSend));
				ulDialog->exec();
			
			}
			addValueToGroupLength(ui.treeWidget->selectedItems()[0]);
		}
		else
		{
			int warning = QMessageBox::warning(this, tr("Warning found"),
				tr("You are not allowed to do this operation."), QMessageBox::Cancel);
		}
	}
	else
	{
		int warning = QMessageBox::warning(this, tr("Warning found"),
			tr("You are not allowed to do this operation."), QMessageBox::Cancel);
	}


}

void Extractor::valueWasSend(QString& t_name) const
{
	ui.treeWidget->selectedItems()[0]->setText(5, t_name);
	auto nr = 0;
	if (t_name.contains("\\"))
	{
		nr = t_name.count("\\");
	}
	if (t_name.contains(","))
	{
		nr = t_name.count(",");
	}

	auto size = 0;
	if (!t_name.isEmpty())
		size = t_name.size() - nr;
	if (size % 2)
		size++;
	ui.treeWidget->selectedItems()[0]->setText(2, std::to_string(nr + 1).c_str());
	ui.treeWidget->selectedItems()[0]->setText(3, std::to_string(size).c_str());
}


void Extractor::onSaveFile()
{
	const auto fileName = QFileDialog::getSaveFileName(this,
		tr("Save File"), tr(""), tr("DICOM File (*.dcm)"));
	if (!fileName.isEmpty())
	{
		const auto file = std::make_unique<DcmFileFormat>(createNewFile());
		if (!file->saveFile(fileName.toStdString().c_str(),
			m_extractor->getFile().getDataset()->getCurrentXfer()).good())
		{
			std::cout << "Failed to save. \n";
		}
	}
}

DcmFileFormat Extractor::createNewFile()
{
	DcmFileFormat fileFormat;
	auto file = m_extractor->getFile();
	auto* dataset = fileFormat.getDataset();
	auto* metainfo = fileFormat.getMetaInfo();

	auto* metaInfoOriginal = file.getMetaInfo();
	auto* originalDataset = file.getDataset();

	OFString value;
	metaInfoOriginal->findAndGetOFStringArray(DCM_FileMetaInformationVersion, value);
	metainfo->putAndInsertString(DCM_FileMetaInformationVersion, value.c_str(), OFTrue);

	QTreeWidgetItemIterator it(ui.treeWidget);
	while (*it && dynamic_cast<Items*> (*it)->getTagId().mid(1, 4) <= "0002")
	{
		auto* itm = dynamic_cast<Items*>(*it);
		auto tagKey = getTagKey(itm);
		metainfo->putAndInsertOFStringArray(tagKey, itm->getValue().toStdString().c_str(), OFTrue);
		++it;
	}

	std::stack<std::pair<DcmSequenceOfItems*, int>> sequenceStack;
	auto stop = false;

	while (*it && !stop)
	{
		auto* itm = dynamic_cast<Items*>(*it);
		if (canBeSaved(itm->getTagId()))
		{
			auto tagKey = getTagKey(itm);

			auto ok = true;
			while (!sequenceStack.empty() && ok)
			{
				itm->getLevel() <= sequenceStack.top().second ? sequenceStack.pop() : ok = false;
			}

			if (sequenceStack.empty())
			{
				if (itm->getVR() == "OB" && itm->childCount()) /// for multi-frame
				{
					DcmElement* elem = nullptr;
					originalDataset->findAndGetElement(tagKey, elem, false, true);
					if (elem)
					{
						dataset->insert(elem);
					}
					stop = true;
				}
				else if (tagKey == DCM_VOILUTSequence)
				{
					DcmElement* elem = nullptr;
					originalDataset->findAndGetElement(tagKey, elem, false, true);
					if (elem)
					{
						dataset->insert(elem);
					}
				}
				else if (itm->getVR() != "SQ")
				{
					saveNonSequenceRoot(itm, dataset, tagKey);
				}
				else
				{
					auto* dcmSQ = new DcmSequenceOfItems(tagKey);
					dataset->insert(dcmSQ);
					sequenceStack.push({ dcmSQ,itm->getLevel() });
				}
			}
			else
			{

				if (itm->getTagId() == "(FFFE,E000)")
				{
					auto* item = new DcmItem(tagKey, itm->getLength().toInt());
					sequenceStack.top().first->append(item);
				}
				else if (itm->getVR() != "SQ")
				{
					auto* itemSeq = sequenceStack.top().first->getItem(sequenceStack.top().first->card() - 1);
					saveNonSequenceChild(itm, itemSeq, dataset, tagKey);
				}
				else
				{
					auto* itemSeq = sequenceStack.top().first->getItem(sequenceStack.top().first->card() - 1);
					auto* dcmSQ = new DcmSequenceOfItems(tagKey);
					itemSeq->insert(dcmSQ);
					sequenceStack.push({ dcmSQ,itm->getLevel() });
				}
			}
		}
		++it;
	}
	return fileFormat;
}

void Extractor::hidden_values(DcmElement* t_newElem, DcmDataset* t_dataset, DcmTagKey& t_tagKey)
{
	DcmElement* elem = nullptr;
	t_dataset->findAndGetElement(t_tagKey, elem, OFTrue, true);
	if (elem)
	{
		OFString st;
		elem->getOFStringArray(st);
		t_newElem->putString(st.c_str());
	}
}

void Extractor::valueForEVR_ox(DcmElement* t_newElem, DcmDataset* t_originalDataset,
	DcmDataset* t_newDataset, DcmTagKey& t_tagKey)
{
	DcmStack originalStack;
	t_originalDataset->findAndGetElements(t_tagKey, originalStack);

	DcmStack currentStack;
	t_newDataset->findAndGetElements(t_tagKey, currentStack);

	auto howMuchToPop = originalStack.card() - currentStack.card() - 1; //todo change name

	while (howMuchToPop)
	{
		originalStack.pop();
		howMuchToPop--;
	}
	auto* elem = dynamic_cast<DcmElement*>(originalStack.top());

	Uint8* pixelValue;
	elem->getUint8Array(pixelValue);
	const auto size = elem->getLength();
	t_newElem->putUint8Array(pixelValue, size);

}


void Extractor::valueForEVR_FD_OD(DcmElement* t_newElem, Items* t_item)
{
	const auto str = t_item->getValue();
	auto list = str.split("\\");
	auto pos = 0;
	for (const auto& elem : list)
	{
		const auto el = elem.toDouble();
		t_newElem->putFloat64(el, pos++);
	}
}

void Extractor::valueForEVR_FL_OF(DcmElement* t_newElem, Items* t_item)
{
	const auto str = t_item->getValue();
	auto list = str.split("\\");
	auto pos = 0;
	for (const auto& elem : list)
	{
		const auto el = elem.toFloat();
		t_newElem->putFloat32(el, pos);
		pos++;
	}
}

void Extractor::saveNonSequenceRoot(Items* t_item, DcmDataset* t_dataset, DcmTagKey& t_tagKey) //todo
{
	DcmElement* newElement = nullptr;
	const auto value = t_item->getValue().toLatin1();

	DcmTag tag(t_tagKey);
	const auto newTagVR = tag.getEVR();
	if (newTagVR == EVR_UNKNOWN)
	{
		const DcmVR dcmvr(t_item->getVR().toStdString().c_str());
		tag.setVR(dcmvr);
	}

	DcmItem::newDicomElementWithVR(newElement, tag);

	if (!newElement)
	{
		std::cout << "Invalid VR. root" << tag.getVRName() << " " << t_item->getTagId().toStdString() << " " << t_item->getValue().toStdString() << "\n";
	}
	else
	{
		if (t_tagKey == DCM_PixelData && (newTagVR == EVR_OB || newTagVR == EVR_OW))
			OFstatic_cast(DcmPixelData*, newElement)->setNonEncapsulationFlag(OFTrue);


		if (tag.getEVR() == EVR_ox || tag.getEVR() == EVR_OB || tag.getEVR() == EVR_OW)
		{
			valueForEVR_ox(newElement, m_extractor->getFile().getDataset(), t_dataset, tag);
			t_dataset->insert(newElement);
		}
		else if (tag.getEVR() == EVR_UN)
		{
			hidden_values(newElement, m_extractor->getFile().getDataset(), tag);
			t_dataset->insert(newElement);
		}
		else if (tag.getEVR() == EVR_FD || tag.getEVR() == EVR_OD)
		{
			valueForEVR_FD_OD(newElement, t_item);
			t_dataset->insert(newElement);
		}
		else if (tag.getEVR() == EVR_FL || tag.getEVR() == EVR_OF)
		{
			valueForEVR_FL_OF(newElement, t_item);
			t_dataset->insert(newElement);
		}
		else if (tag.getEVR() == EVR_AT)
		{
			const auto group = t_item->text(5).mid(0, 4);
			const auto element = t_item->text(5).mid(5, 4);
			t_dataset->putAndInsertTagKey(tag, getTagKey(group, element));
		}
		else
		{
			newElement->putString(value);
			t_dataset->insert(newElement);
		}

	}

}

void Extractor::saveNonSequenceChild(Items* t_item, DcmItem* t_parent, DcmDataset* t_dataset, DcmTagKey& t_tagKey)
{
	DcmElement* newElement = nullptr;
	const auto value = t_item->getValue().toLatin1();
	DcmTag tag(t_tagKey);
	const auto newTagVR = tag.getEVR();
	if (newTagVR == EVR_UNKNOWN)
	{
		const DcmVR dcmvr(t_item->getVR().toStdString().c_str());
		tag.setVR(dcmvr);
	}

	DcmItem::newDicomElementWithVR(newElement, tag);

	if (!newElement)
	{
		std::cout << "Invalid VR." << tag.getVRName() << " " << t_item->getTagId().toStdString() << "\n";
	}
	else
	{
		if (t_tagKey == DCM_PixelData && (newTagVR == EVR_OB || newTagVR == EVR_OW))
			OFstatic_cast(DcmPixelData*, newElement)->setNonEncapsulationFlag(OFTrue);

		if (tag.getEVR() == EVR_ox || tag.getEVR() == EVR_OB || tag.getEVR() == EVR_OW)
		{
			valueForEVR_ox(newElement, m_extractor->getFile().getDataset(), t_dataset, tag);
			t_parent->insert(newElement);
		}
		else if (tag.getEVR() == EVR_lt)
		{
			///already covered
		}
		else if (tag.getEVR() == EVR_FD || tag.getEVR() == EVR_OD)
		{
			valueForEVR_FD_OD(newElement, t_item);
			t_parent->insert(newElement);
		}
		else if (tag.getEVR() == EVR_FL || tag.getEVR() == EVR_OF)
		{
			valueForEVR_FL_OF(newElement, t_item);
			t_parent->insert(newElement);
		}
		else if (tag.getEVR() == EVR_UN)
		{
			hidden_values(newElement, m_extractor->getFile().getDataset(), tag);
			t_parent->insert(newElement);
		}
		else if (tag.getEVR() == EVR_AT)
		{
			const auto group = t_item->text(5).mid(0, 4);
			const auto element = t_item->text(5).mid(5, 4);
			t_parent->putAndInsertTagKey(tag, getTagKey(group, element));
		}
		else
		{
			newElement->putString(value);
			t_parent->insert(newElement);
		}
	}
}

DcmTagKey Extractor::getTagKey(Items* t_item)
{
	const auto group = t_item->getTagId().mid(1, 4);
	const auto element = t_item->getTagId().mid(6, 4);
	bool ok;
	DcmTagKey tagkey(group.toInt(&ok, 16), element.toInt(&ok, 16));
	return tagkey;
}

DcmTagKey Extractor::getTagKey(const QString& t_group, const QString& t_element)
{
	bool ok;
	DcmTagKey tagkey(t_group.toInt(&ok, 16), t_element.toInt(&ok, 16));
	return tagkey;
}


bool Extractor::canBeSaved(const QString& t_tagId)
{
	return (t_tagId != "(FFFE,E00D)" && t_tagId != "(FFFE,E0DD)");
}

void Extractor::receiveItem(QString& t_tagId, QString& t_vr, QString& t_vm, QString& t_length, QString& t_description, QString& t_value) const
{
	if (!ui.treeWidget->selectedItems()[0]->childCount())
	{
		auto* itm = new Items(t_tagId, t_vr, t_vm, t_length, t_description, t_value, 0);
		AddRoot(itm);
		addValueToGroupLength(itm);
		if (t_vr == "SQ")
		{
			insertSequenceDelimitators(itm);
		}
	}
	else
	{
		const auto level = ui.treeWidget->selectedItems()[0]->data(0, 1).toInt() + 2;
		auto* itm = new Items(t_tagId, t_vr, t_vm, t_length, t_description, t_value, level);
		AddChild(itm, ui.treeWidget->selectedItems()[0]->child(0));
		addValueToGroupLength(itm);


		if(t_vr=="SQ")
		{
			insertSequenceDelimitators(itm);
		}
	}

}

void Extractor::insertSequenceDelimitators(QTreeWidgetItem* t_root) const
{
	const auto level = t_root->data(0, 1).toInt();
	auto* seqItem = new Items("(FFFE,E000)", "", "0",
		"Undefined", "Item", "", level + 1);
	AddChild(seqItem, t_root);
	auto* itemDelimitation = new Items("(FFFE,E00D)", "", "0",
		"0", "Item Delimitation Item", "", level + 2);
	AddChild(itemDelimitation, seqItem);
	auto* sequenceDelimitation = new Items("(FFFE,E0DD)", "", "0",
		"0", "Sequence Delimitation Item", "", level + 1);
	AddChild(sequenceDelimitation, t_root);
}
