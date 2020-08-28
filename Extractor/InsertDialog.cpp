#include "InsertDialog.h"
#include <iostream>
#include <dcmtk/dcmdata/dcdict.h>


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

InsertDialog::InsertDialog(QWidget* parent)
	: QDialog(parent,  Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint),
	m_dictionary(new DicomDictionary(this))
{
	ui.setupUi(this);
	Q_UNUSED(connect(m_dictionary,
		&DicomDictionary::insertData,
		this, &InsertDialog::onInsertData));
}

InsertDialog::~InsertDialog()
{
	delete m_dictionary;
}


void InsertDialog::onListItems() const
{
	m_dictionary->exec();
}

void InsertDialog::onInsertData(QString& t_group, QString& t_element, QString& t_description, QString& t_VR)
{
	ui.lineEditGroup->setText(t_group);
	ui.lineEditElement->setText(t_element);
	ui.lineEditVR->setText(t_VR);
	ui.descriptionLabel->setText(t_description);
	m_dictionary->reject();
}


void InsertDialog::onInsertPressed()
{
	if(ui.lineEditVR->text()=="PN")
	{
		auto* pnDialog = new PNDialog(ui.descriptionLabel->text(),this);
		Q_UNUSED(connect(pnDialog, &PNDialog::sendName, this, &InsertDialog::valueWasSend));
		pnDialog->exec();
		delete pnDialog;
	}
	else if(ui.lineEditVR->text()=="LO")
	{
		auto* loDialog = new LongStringDialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(loDialog, &LongStringDialog::sendValue, this, &InsertDialog::valueWasSend));
		loDialog->exec();
		delete loDialog;
	}
	else if(ui.lineEditVR->text()=="SH")
	{
		auto* shDialog = new ShortStringDialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(shDialog, &ShortStringDialog::sendValue, this, &InsertDialog::valueWasSend));
		shDialog->exec();
		delete shDialog;
	}
	else if(ui.lineEditVR->text() == "UI")
	{
		auto* uiDialog = new UniqueIdentifierDialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(uiDialog, &UniqueIdentifierDialog::sendValue, this, &InsertDialog::valueWasSend));
		uiDialog->exec();
		delete uiDialog;
	}
	else if(ui.lineEditVR->text() == "DA")
	{
		auto* daDialog = new DADialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(daDialog, &DADialog::sendValue, this, &InsertDialog::valueWasSend));
		daDialog->exec();
		delete daDialog;
	}
	else if (ui.lineEditVR->text() == "TM")
	{
		auto* tmDialog = new TMDialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(tmDialog, &TMDialog::sendValue, this, &InsertDialog::valueWasSend));
		tmDialog->exec();
		delete tmDialog;
	}
	else if (ui.lineEditVR->text() == "IS")
	{
		auto* isDialog = new ISDialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(isDialog, &ISDialog::sendValue, this, &InsertDialog::valueWasSend));
		isDialog->exec();
		delete isDialog;
	}
	else if (ui.lineEditVR->text() == "CS")
	{
		auto* csDialog = new CSDialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(csDialog, &CSDialog::sendValue, this, &InsertDialog::valueWasSend));
		csDialog->exec();
		delete csDialog;
	}
	else if(ui.lineEditVR->text()=="AS")
	{
		auto* asDialog = new ASDialog(ui.lineEditVR->text(),ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(asDialog, &ASDialog::sendValue, this, &InsertDialog::valueWasSend));
		asDialog->exec();
		delete asDialog;
	}
	else if (ui.lineEditVR->text() == "AE")
	{
		auto* aeDialog = new ASDialog(ui.lineEditVR->text(), ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(aeDialog, &ASDialog::sendValue, this, &InsertDialog::valueWasSend));
		aeDialog->exec();
		delete aeDialog;
	}
	else if (ui.lineEditVR->text() == "DS")
	{
		auto* dsDialog = new DSDialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(dsDialog, &DSDialog::sendValue, this, &InsertDialog::valueWasSend));
		dsDialog->exec();
		delete dsDialog;
	}
	else if(ui.lineEditVR->text()=="US")
	{
		auto* usDialog = new USDialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(usDialog, &USDialog::sendValue, this, &InsertDialog::valueWasSend));
		usDialog->exec();
		delete usDialog;
	}
	else if (ui.lineEditVR->text() == "FD" || ui.lineEditVR->text() == "FL")
	{
		auto* fdDialog = new FDdialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(fdDialog, &FDdialog::sendValue, this, &InsertDialog::valueWasSend));
		fdDialog->exec();
		delete fdDialog;
	}
	else if (ui.lineEditVR->text() == "AT")
	{
		auto* atDialog = new ATDialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(atDialog, &ATDialog::sendValue, this, &InsertDialog::valueWasSend));
		atDialog->exec();
		delete atDialog;
	}
	else if (ui.lineEditVR->text() == "DT")
	{
		auto* dtDialog = new DTDialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(dtDialog, &DTDialog::sendValue, this, &InsertDialog::valueWasSend));
		dtDialog->exec();
		delete dtDialog;
	}
	else if (ui.lineEditVR->text() == "ST" || ui.lineEditVR->text() == "UT" || ui.lineEditVR->text() == "LT") 
	{
		auto* stDialog = new STDialog(ui.descriptionLabel->text(), this);
		Q_UNUSED(connect(stDialog, &STDialog::sendValue, this, &InsertDialog::valueWasSend));
		stDialog->exec();
		delete stDialog;
	}
	else if (ui.lineEditVR->text() == "UL")
	{
		auto* ulDialog = new ULDialog( this);
		Q_UNUSED(connect(ulDialog, &ULDialog::sendValue, this, &InsertDialog::valueWasSend));
		ulDialog->exec();
		delete ulDialog;
	}
	else if (ui.lineEditVR->text() == "OB")
	{
		QString noName = "hidden";
		valueWasSend(noName);
	}
	else
	{
		QString noName;
		valueWasSend(noName);
	}
	
	
}

void InsertDialog::valueWasSend(QString& t_name)
{
	if(ui.lineEditElement->text().isEmpty())
	{
		ui.lineEditElement->setText("FFFF");
	}
	else if (ui.lineEditElement->text().size() < 4)
	{
		auto txt = ui.lineEditElement->text();
		while (txt.size() < 4)
		{
			txt.insert(0, "0");
		}
		ui.lineEditElement->setText(txt);
	}
	
	if (ui.lineEditGroup->text().isEmpty())
	{
		ui.lineEditGroup->setText("FFFF");
	}
	else if (!ui.lineEditGroup->text().isEmpty() && ui.lineEditGroup->text().size() < 4)
	{
		auto txt = ui.lineEditGroup->text();
		while (txt.size() < 4)
		{
			txt.insert(0, "0");
		}
		ui.lineEditGroup->setText(txt);
	}
	
	QString tagID = "(" + ui.lineEditGroup->text() + "," + 
		ui.lineEditElement->text() + ")";
	auto size=0;
	if (!t_name.isEmpty())
		size = t_name.size();
	if (size % 2)
		size++;
	emit sendItem( new Items(tagID, ui.lineEditVR->text(), "0",
		std::to_string(size).c_str(), ui.descriptionLabel->text(), t_name, 0));
	this->reject();
}

void InsertDialog::presets()
{
	ui.lineEditGroup->setMaxLength(4);
	ui.lineEditElement->setMaxLength(4);
}

