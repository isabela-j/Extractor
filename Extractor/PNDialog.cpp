#include "PNDialog.h"

#include <iostream>

PNDialog::PNDialog(QString& t_description, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	ui.labelDescription->setText(t_description);
}



void PNDialog::onOKPressed()
{
	QString patientName;
	if(!ui.lineEditFamilyName->text().isEmpty())
	{
		patientName += ui.lineEditFamilyName->text() + "^";
	}
	if (!ui.lineEditGivenName->text().isEmpty())
	{
		patientName += ui.lineEditGivenName->text() + "^";
	}
	if (!ui.lineEditMiddleName->text().isEmpty())
	{
		patientName += ui.lineEditMiddleName->text() + "^";
	}
	if (!ui.lineEditNamePrefix->text().isEmpty())
	{
		patientName += ui.lineEditNamePrefix->text() + "^";
	}
	if (!ui.lineEditNameSuffix->text().isEmpty())
	{
		patientName += ui.lineEditNameSuffix->text() + "^";
	}
	emit sendName(patientName);
	close();
}
