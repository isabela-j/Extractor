#include "ExtractorGUI.h"

#include <iostream>
#include <QDebug>

#include <QFileDialog>
#include <dcmtk/dcmdata/dcfilefo.h>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dcistrmb.h>

#include "AS_AE_Dialog.h"
#include "ATDialog.h"
#include "CSDialog.h"
#include "DADialog.h"
#include "DSDialog.h"
#include "DTDialog.h"
#include "FDdialog.h"
#include "ISDialog.h"
#include "STDialog.h"
#include "TMDialog.h"
#include "ULDialog.h"
#include "USDialog.h"

Extractor::Extractor(QWidget* parent)
	: QMainWindow(parent), m_extractor(std::make_unique<TagExtractor>()), m_insertDialog(std::make_unique<InsertDialog>())
{
	ui.setupUi(this);
	Q_UNUSED(connect(m_extractor.get(), &TagExtractor::addNewChildInTree, this, &Extractor::AddChildExtractor));
	Q_UNUSED(connect(m_extractor.get(), &TagExtractor::addNewRootInTree, this, &Extractor::AddRootExtractor));
	Q_UNUSED(connect(m_insertDialog.get(), &InsertDialog::sendItem, this, &Extractor::receiveItem));
	presets();
}

void Extractor::presets() const
{
	ui.treeWidget->setColumnCount(6);
	QStringList ColumnNames;
	ColumnNames << "Tag ID" << "VR" << "VM" << "Length" << "Description" << "Value";
	ui.treeWidget->setHeaderLabels(ColumnNames);
	ui.treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
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

void Extractor::AddRoot(Items* t_item)
{	
	ui.treeWidget->addTopLevelItem(t_item);
	t_item->setExpanded(true);
	ui.treeWidget->scrollToItem(t_item);
	ui.treeWidget->setCurrentItem(t_item);
}

void Extractor::AddChild(Items* t_item, QTreeWidgetItem* t_root)
{
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
}

bool Extractor::shouldDelete(QTreeWidgetItem* t_item)
{
	bool contains=false;
	if(t_item->text(4)=="PhotometricInterpretation" || t_item->text(4) == "Rows"
		|| t_item->text(4) == "Columns" || t_item->text(4).contains("Pixel")
		|| t_item->text(4).contains("Frame") || t_item->text(4).contains("Item") 
		|| t_item->text(4).contains("Bit") || t_item->text(4).contains("Implementation") 
		|| t_item->text(4).contains("TransferSyntax"))
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
		|| t_item->text(4).contains("TransferSyntax") || t_item->text(0).contains("0000"))
	{
		return false;
	}
	
	return true;
}


void Extractor::substractValueFromGroupLength(QTreeWidgetItem* t_item)
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
			delete items.at(0);
	}
}

void Extractor::addValueToGroupLength(QTreeWidgetItem* t_item)
{
	auto const tagId = "("+t_item->text(0).mid(1,4)+",0000)";
	auto const val = t_item->text(3).toInt()+8;
	auto items = ui.treeWidget->findItems(tagId, Qt::MatchExactly, 0);
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
			substractValueFromGroupLength(ui.treeWidget->selectedItems()[0]);
			delete ui.treeWidget->selectedItems()[0];
		}
	}
	
}

void Extractor::onInsertTag()
{
	if (!ui.treeWidget->selectedItems().isEmpty())
	{
		m_insertDialog->exec();
	}
	
}


void Extractor::onEditTag()
{
	if(!ui.treeWidget->selectedItems().isEmpty())
	{
		if (shouldEdit(ui.treeWidget->selectedItems()[0]))
		{
			substractValueFromGroupLength(ui.treeWidget->selectedItems()[0]);
				if (ui.treeWidget->selectedItems()[0]->text(1) == "PN")
				{
					auto* pnDialog = new PNDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(pnDialog, &PNDialog::sendName, this, &Extractor::valueWasSend));
					pnDialog->exec();
					delete pnDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "LO")
				{
					auto* loDialog = new LongStringDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(loDialog, &LongStringDialog::sendValue, this, &Extractor::valueWasSend));
					loDialog->exec();
					delete loDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "SH")
				{
					auto* shDialog = new ShortStringDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(shDialog, &ShortStringDialog::sendValue, this, &Extractor::valueWasSend));
					shDialog->exec();
					delete shDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "UI")
				{
					auto* uiDialog = new UniqueIdentifierDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(uiDialog, &UniqueIdentifierDialog::sendValue, this, &Extractor::valueWasSend));
					uiDialog->exec();
					delete uiDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "DA")
				{
					auto* daDialog = new DADialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(daDialog, &DADialog::sendValue, this, &Extractor::valueWasSend));
					daDialog->exec();
					delete daDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "TM")
				{
					auto* tmDialog = new TMDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(tmDialog, &TMDialog::sendValue, this, &Extractor::valueWasSend));
					tmDialog->exec();
					delete tmDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "IS")
				{
					auto* isDialog = new ISDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(isDialog, &ISDialog::sendValue, this, &Extractor::valueWasSend));
					isDialog->exec();
					delete isDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "CS")
				{
					auto* csDialog = new CSDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(csDialog, &CSDialog::sendValue, this, &Extractor::valueWasSend));
					csDialog->exec();
					delete csDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "AS")
				{
					auto* asDialog = new ASDialog(ui.treeWidget->selectedItems()[0]->text(1), ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(asDialog, &ASDialog::sendValue, this, &Extractor::valueWasSend));
					asDialog->exec();
					delete asDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "AE")
				{
					auto* aeDialog = new ASDialog(ui.treeWidget->selectedItems()[0]->text(1), ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(aeDialog, &ASDialog::sendValue, this, &Extractor::valueWasSend));
					aeDialog->exec();
					delete aeDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "DS")
				{
					auto* dsDialog = new DSDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(dsDialog, &DSDialog::sendValue, this, &Extractor::valueWasSend));
					dsDialog->exec();
					delete dsDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "US")
				{
					auto* usDialog = new USDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(usDialog, &USDialog::sendValue, this, &Extractor::valueWasSend));
					usDialog->exec();
					delete usDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "FD" 
						|| ui.treeWidget->selectedItems()[0]->text(1) == "FL")
				{
					auto* fdDialog = new FDdialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(fdDialog, &FDdialog::sendValue, this, &Extractor::valueWasSend));
					fdDialog->exec();
					delete fdDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "AT")
				{
					auto* atDialog = new ATDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(atDialog, &ATDialog::sendValue, this, &Extractor::valueWasSend));
					atDialog->exec();
					delete atDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "DT")
				{
					auto* dtDialog = new DTDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(dtDialog, &DTDialog::sendValue, this, &Extractor::valueWasSend));
					dtDialog->exec();
					delete dtDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "ST"
						|| ui.treeWidget->selectedItems()[0]->text(1) == "UT" 
						|| ui.treeWidget->selectedItems()[0]->text(1) == "LT")
				{
					auto* stDialog = new STDialog(ui.treeWidget->selectedItems()[0]->text(4), this);
					Q_UNUSED(connect(stDialog, &STDialog::sendValue, this, &Extractor::valueWasSend));
					stDialog->exec();
					delete stDialog;
				}
				else if (ui.treeWidget->selectedItems()[0]->text(1) == "UL")
				{
					auto* ulDialog = new ULDialog(this);
					Q_UNUSED(connect(ulDialog, &ULDialog::sendValue, this, &Extractor::valueWasSend));
					ulDialog->exec();
					delete ulDialog;
				}
				addValueToGroupLength(ui.treeWidget->selectedItems()[0]);

				
		}
	}
	
	
}

void Extractor::valueWasSend(QString& t_name)
{
	ui.treeWidget->selectedItems()[0]->setText(5, t_name);
	if (t_name.size() % 2)
	{
		t_name.append(" ");
	}
	ui.treeWidget->selectedItems()[0]->setText(3, std::to_string(t_name.size()).c_str());
}


void Extractor::onSaveFile()
{
	const QString fileName = QFileDialog::getSaveFileName(this, 
		tr("Save File"), tr(""), tr("DICOM File (*.dcm)"));
	if (!fileName.isEmpty())
	{
		DcmFileFormat* file=new DcmFileFormat(createNewFile());
		file->loadAllDataIntoMemory();
		std::ostringstream ss;
		file->writeXML(ss, DCMTypes::PF_shortenLongTagValues);
		//std::cout << ss.str();

		if (!file->saveFile(fileName.toStdString().c_str(),m_extractor->getFile().getDataset()->getCurrentXfer()).good())
		{
			std::cout << "Failed to save. \n";
		}
	}
}

DcmFileFormat Extractor::createNewFile()
{
	DcmFileFormat fileFormat;
	auto file = m_extractor->getFile();
	DcmDataset* dataset = fileFormat.getDataset();
	DcmMetaInfo* metainfo = fileFormat.getMetaInfo();

	DcmMetaInfo* metaInfoOriginal = file.getMetaInfo();
	DcmDataset* originalDataset = file.getDataset();

	OFString value;
	metaInfoOriginal->findAndGetOFStringArray(DCM_FileMetaInformationVersion, value);
	metainfo->putAndInsertString(DCM_FileMetaInformationVersion, value.c_str(), OFTrue);
	
	QTreeWidgetItemIterator it(ui.treeWidget);
	while (*it && dynamic_cast<Items*> (*it)->getTagId().mid(1, 4) <= "0002")
	{
		auto itm = dynamic_cast<Items*>(*it);
		DcmTagKey tagKey = getTagKey(itm);
		metainfo->putAndInsertOFStringArray(tagKey, itm->getValue().toStdString().c_str(), OFTrue);
		++it;
	}
	
	std::stack<std::pair<DcmSequenceOfItems*, int>> sequenceStack;
	while (*it)
	{
		auto itm= dynamic_cast<Items*>(*it);
		if (canBeSaved(itm->getTagId()))
		{
			DcmTagKey tagKey = getTagKey(itm);
			bool ok = true;
			
			while (!sequenceStack.empty() && ok)
			{
				itm->getLevel() <= sequenceStack.top().second ? sequenceStack.pop() : ok = false;
			}
			//QTreeWidgetItemIterator nextIt(++it);
			//--it;
			//std::cout << dynamic_cast<Items*>(*nextIt)->getTagId().toStdString() << "\n";
			if(sequenceStack.empty())
			{
				if(itm->getVR()!="SQ")
				{
					insertNonSequence(itm, dataset, tagKey);
				}
				/*else if (itm->getVR() != "SQ" && (*nextIt)->text(0) == "(FFFE,E000)")
				{
					std::cout << "here";
					//auto* itemSeq = sequenceStack.top().first->getItem(sequenceStack.top().first->card() - 1);
					//itemSeq->putAndInsertString(tagKey, itm->getValue().toLatin1());
				}**/
				else
				{
					auto *dcmSQ = new DcmSequenceOfItems(tagKey);
					dataset->insert(dcmSQ);
					sequenceStack.push({ dcmSQ,itm->getLevel() });
				}						 
			}
			else
			{	
				if(itm->getTagId()=="(FFFE,E000)")
				{
					auto* item = new DcmItem(tagKey, itm->getLength().toInt());
					sequenceStack.top().first->append(item);	
				}
				else if (itm->getVR() != "SQ")
				{
					auto* itemSeq = sequenceStack.top().first->getItem(sequenceStack.top().first->card()-1);
					itemSeq->putAndInsertString(tagKey, itm->getValue().toLatin1());
				}
				else
				{
					auto* itemSeq = sequenceStack.top().first->getItem(0);
					auto* dcmSQ = new DcmSequenceOfItems(tagKey);
					itemSeq->insert(dcmSQ);
					sequenceStack.push({ dcmSQ,itm->getLevel() });
				}
			}	
		}
		++it;
	}
	// we check if we have Pixel Data in our original dataset
	Uint8* pixelValue;
	DcmElement* tempElem = nullptr;
	originalDataset->findAndGetElement(DCM_PixelData, tempElem, true);
	if (tempElem)
	{
		tempElem->getUint8Array(pixelValue);
		dataset->putAndInsertUint8Array(DCM_PixelData, pixelValue, tempElem->getLength());

	}
	return fileFormat;
}

void Extractor::valueForOB(DcmElement* t_elem, DcmDataset* t_dataset, DcmTagKey& t_tagKey)
{
	OFString value;
	t_dataset->findAndGetOFStringArray(t_tagKey, value);
	t_elem->putString(value.c_str());
}

void Extractor::insertNonSequence(Items* t_item, DcmDataset* t_dataset, DcmTagKey& t_tagKey)
{
	DcmElement* newElement = NULL;
	std::string value = t_item->getValue().toLatin1();

	DcmTag tag(t_tagKey);
	const DcmEVR newTagVR = tag.getEVR();
	if (newTagVR == EVR_UNKNOWN)
	{
		DcmVR dcmvr(t_item->getVR().toStdString().c_str());
		tag.setVR(dcmvr);
	}

	OFCondition newElementError = DcmItem::newDicomElementWithVR(newElement, tag);

	if (!newElement)
	{
		std::cout << "Invalid VR.   " << tag.getVRName() << "    " << t_item->getTagId().toStdString() << "\n";
	}
	else
	{
		if (t_tagKey == DCM_PixelData && (newTagVR == EVR_OB || newTagVR == EVR_OW))
			OFstatic_cast(DcmPixelData*, newElement)->setNonEncapsulationFlag(OFTrue);

		if (!value.empty())
		{
			if (value == "hidden" &&( tag.getEVR() == EVR_OB || tag.getEVR() == EVR_OW ))
			{
				valueForOB(newElement, m_extractor->getFile().getDataset(), t_tagKey);
			}
			else
			{
				OFCondition l_error = newElement->putString(value.c_str());
			}

		}
		OFCondition cond = t_dataset->insert(newElement);
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

bool Extractor::canBeSaved(const QString& t_tagId)
{
	return (t_tagId != "(FFFE,E00D)" && t_tagId != "(FFFE,E0DD)");
}

void Extractor::receiveItem(Items* t_item)
{
	if (!ui.treeWidget->selectedItems()[0]->childCount())
	{
		AddRoot(t_item);
	}
	else
	{
		AddChild(t_item, ui.treeWidget->selectedItems()[0]->child(0));
	}
	addValueToGroupLength(t_item);
}
