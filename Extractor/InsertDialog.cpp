#include "InsertDialog.h"
#include <iostream>
#include <QMessageBox>
#include <dcmtk/dcmdata/dcdict.h>

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
#include "SizeSQ.h"
#include "TMDialog.h"
#include "UIDialog.h"
#include "ULDialog.h"
#include "USDialog.h"

InsertDialog::InsertDialog(QWidget* parent)
	: QDialog(parent,  Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint),
	m_dictionary(new DicomDictionary(this))
{
	m_ui.setupUi(this);
	Q_UNUSED(connect(m_dictionary,
		&DicomDictionary::insertData,
		this, &InsertDialog::onInsertData));
	presets();
}

InsertDialog::~InsertDialog()
{
	delete m_dictionary;
}


void InsertDialog::onListItems() const
{
	m_dictionary->exec();
}

void InsertDialog::onInsertData(QString& t_group, QString& t_element, QString& t_description, QString& t_VR) const
{
	m_ui.lineEditGroup->setText(t_group);
	m_ui.lineEditElement->setText(t_element);
	m_ui.lineEditVR->setText(t_VR);
	m_ui.descriptionLabel->setText(t_description);
	m_dictionary->close();
}


void InsertDialog::onInsertPressed() 
{
	auto description = m_ui.descriptionLabel->text();
	if(m_ui.lineEditVR->text().toUpper()=="PN")
	{
		auto* pnDialog = new PNDialog(description,this);
		Q_UNUSED(connect(pnDialog, &PNDialog::sendName, this, &InsertDialog::valueWasSent));
		pnDialog->exec();
	}
	else if(m_ui.lineEditVR->text().toUpper()=="LO")
	{
		auto* loDialog = new LODialog(description, this);
		Q_UNUSED(connect(loDialog, &LODialog::sendValue, this, &InsertDialog::valueWasSent));
		loDialog->exec();
	}
	else if(m_ui.lineEditVR->text().toUpper()=="SH")
	{
		auto* shDialog = new SHDialog(description, this);
		Q_UNUSED(connect(shDialog, &SHDialog::sendValue, this, &InsertDialog::valueWasSent));
		shDialog->exec();
	}
	else if(m_ui.lineEditVR->text().toUpper() == "UI")
	{
		auto* uiDialog = new UIDialog(description, this);
		Q_UNUSED(connect(uiDialog, &UIDialog::sendValue, this, &InsertDialog::valueWasSent));
		uiDialog->exec();
	}
	else if(m_ui.lineEditVR->text().toUpper() == "DA")
	{
		auto* daDialog = new DADialog(description, this);
		Q_UNUSED(connect(daDialog, &DADialog::sendValue, this, &InsertDialog::valueWasSent));
		daDialog->exec();
	}
	else if (m_ui.lineEditVR->text().toUpper() == "TM")
	{
		auto* tmDialog = new TMDialog(description, this);
		Q_UNUSED(connect(tmDialog, &TMDialog::sendValue, this, &InsertDialog::valueWasSent));
		tmDialog->exec();
	}
	else if (m_ui.lineEditVR->text().toUpper() == "IS" )
	{
		auto* isDialog = new ISDialog(description, this);
		Q_UNUSED(connect(isDialog, &ISDialog::sendValue, this, &InsertDialog::valueWasSent));
		isDialog->exec();
	}
	else if (m_ui.lineEditVR->text().toUpper() == "CS" )
	{
		auto* csDialog = new CSDialog(description, this);
		Q_UNUSED(connect(csDialog, &CSDialog::sendValue, this, &InsertDialog::valueWasSent));
		csDialog->exec();
	}
	else if(m_ui.lineEditVR->text().toUpper()=="AS")
	{
		auto* asDialog = new ASDialog(description, this);
		Q_UNUSED(connect(asDialog, &ASDialog::sendValue, this, &InsertDialog::valueWasSent));
		asDialog->exec();
	}
	else if (m_ui.lineEditVR->text().toUpper() == "AE")
	{
		auto* aeDialog = new AEDialog( description, this);
		Q_UNUSED(connect(aeDialog, &AEDialog::sendValue, this, &InsertDialog::valueWasSent));
		aeDialog->exec();
	}
	else if (m_ui.lineEditVR->text().toUpper() == "DS")
	{
		auto* dsDialog = new DSDialog(description, this);
		Q_UNUSED(connect(dsDialog, &DSDialog::sendValue, this, &InsertDialog::valueWasSent));
		dsDialog->exec();
	}
	else if(m_ui.lineEditVR->text().toUpper()=="US"|| m_ui.lineEditVR->text().toUpper() == "SS")
	{
		auto* usDialog = new USDialog(description, this);
		Q_UNUSED(connect(usDialog, &USDialog::sendValue, this, &InsertDialog::valueWasSent));
		usDialog->exec();
	}
	else if (m_ui.lineEditVR->text().toUpper() == "FD" || m_ui.lineEditVR->text().toUpper() == "FL")
	{
		auto* fdDialog = new FDdialog(description, this);
		Q_UNUSED(connect(fdDialog, &FDdialog::sendValue, this, &InsertDialog::valueWasSent));
		fdDialog->exec();
	}
	else if (m_ui.lineEditVR->text().toUpper() == "AT")
	{
		auto* atDialog = new ATDialog(description, this);
		Q_UNUSED(connect(atDialog, &ATDialog::sendValue, this, &InsertDialog::valueWasSent));
		atDialog->exec();
	}
	else if (m_ui.lineEditVR->text().toUpper() == "DT")
	{
		auto* dtDialog = new DTDialog(description, this);
		Q_UNUSED(connect(dtDialog, &DTDialog::sendValue, this, &InsertDialog::valueWasSent));
		dtDialog->exec();
	}
	else if (m_ui.lineEditVR->text().toUpper() == "ST" || m_ui.lineEditVR->text().toUpper() == "UT" || m_ui.lineEditVR->text().toUpper() == "LT")
	{
		auto* stDialog = new STDialog(description, this);
		Q_UNUSED(connect(stDialog, &STDialog::sendValue, this, &InsertDialog::valueWasSent));
		stDialog->exec();
	}
	else if (m_ui.lineEditVR->text().toUpper() == "UL")
	{
		auto* ulDialog = new ULDialog( description, this);
		Q_UNUSED(connect(ulDialog, &ULDialog::sendValue, this, &InsertDialog::valueWasSent));
		ulDialog->exec();
	}
	else if (m_ui.lineEditVR->text().toUpper() == "SQ")
	{
		auto* sqSizeDialog = new SizeSQ(this);
		Q_UNUSED(connect(sqSizeDialog, &SizeSQ::sendSize, this, &InsertDialog::sizeWasSent));
		sqSizeDialog->exec();
	}
	else
	{
		QMessageBox::warning(this, tr("Warning found"),
			tr("You are not allowed to do this operation."), QMessageBox::Cancel);
	}
}

void InsertDialog::valueWasSent(QString& t_name)
{
	setGroupElementFormat();

	auto tagID = "(" + m_ui.lineEditGroup->text() + "," + 
		m_ui.lineEditElement->text() + ")";

	//in case of VR: UL, our t_name will look like: 66\24\2345\55 and its size will be 13.
	//We must not count the character "\", so we will subtract each occurence of it
	auto nr = 0; 
	if(t_name.contains("\\")) 
	{
		 nr = t_name.count("\\");
	}
	if(t_name.contains(","))
	{
		nr = t_name.count(",");
	}
	auto size=0;
	if (!t_name.isEmpty())
	{
		size = t_name.size() - nr;
	}
	if (size % 2)
	{
		size++;
	}

	QString vm = std::to_string(nr+1).c_str();
	QString len = std::to_string(size).c_str();

	auto vr = m_ui.lineEditVR->text().toUpper();
	auto description = m_ui.descriptionLabel->text();
	emit sendItem(tagID, vr , vm, len , description , t_name);
	close();
}

void InsertDialog::sizeWasSent(QString& t_size)
{
	setGroupElementFormat();
	auto tagID = "(" + m_ui.lineEditGroup->text() + "," +
		m_ui.lineEditElement->text() + ")";
	QString vr = "SQ";
	QString vm = "0";
	QString description = m_ui.descriptionLabel->text();
	QString value = "";
	emit sendItem(tagID, vr, vm, t_size, description, value);
	close();
}

void InsertDialog::presets() const
{
	m_ui.lineEditGroup->setMaxLength(4);
	m_ui.lineEditElement->setMaxLength(4);
}

void InsertDialog::setGroupElementFormat() const
{
	if (m_ui.lineEditElement->text().isEmpty())
	{
		m_ui.lineEditElement->setText("FFFF");
	}
	else if (m_ui.lineEditElement->text().size() < 4)
	{
		auto txt = m_ui.lineEditElement->text();
		while (txt.size() < 4)
		{
			txt.insert(0, "0");
		}
		m_ui.lineEditElement->setText(txt);
	}

	if (m_ui.lineEditGroup->text().isEmpty())
	{
		m_ui.lineEditGroup->setText("FFFF");
	}
	else if (!m_ui.lineEditGroup->text().isEmpty() && m_ui.lineEditGroup->text().size() < 4)
	{
		auto txt = m_ui.lineEditGroup->text();
		while (txt.size() < 4)
		{
			txt.insert(0, "0");
		}
		m_ui.lineEditGroup->setText(txt);
	}
}

