#include "ATDialog.h"

#include <qvalidator.h>

ATDialog::ATDialog(QString& t_description, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	presets(t_description);
}

ATDialog::~ATDialog()
{
}

void ATDialog::onOKPressed()
{
	QString value;
	if(!ui.lineEditGroup->text().isEmpty())
	{
		value += ui.lineEditGroup->text();
	}
	if(!ui.lineEditElement->text().isEmpty())
	{
		if(!value.isEmpty())
		{
			value += ",";
		}
		value+=ui.lineEditElement->text();
	}
	emit sendValue(value);
	this->reject();
}

void ATDialog::presets(QString& t_description)
{
	ui.labelDescription->setText(t_description);
	ui.lineEditGroup->setMaxLength(4);
	const auto regexValidator =
		std::make_unique<QRegExpValidator>(QRegExp("[A-Z0-9]{4}"));
	ui.lineEditGroup->setValidator(regexValidator.get());

	ui.lineEditElement->setMaxLength(4);
	const auto regexValidator2 =
		std::make_unique<QRegExpValidator>(QRegExp("^[A-Z0-9]{4}"));
	ui.lineEditElement->setValidator(regexValidator2.get());
	
}
