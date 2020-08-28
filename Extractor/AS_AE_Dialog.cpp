#include "AS_AE_Dialog.h"

#include <qvalidator.h>

ASDialog::ASDialog(QString &VR, QString& t_description,QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	if (VR == "AS")
	{
		presetsAS(t_description);
	}
	else
	{
		presetsAE(t_description);
	}
}

ASDialog::~ASDialog()
{
}

void ASDialog::presetsAS(QString& t_description)
{
	ui.labelDescription->setText(t_description);
	ui.lineEditValue->setMaxLength(4);
	const auto regexValidator =
		std::make_unique<QRegExpValidator>(QRegExp("^([0-9]{3}[DMY])*$"));
	ui.lineEditValue->setValidator(regexValidator.get());
}

void ASDialog::presetsAE(QString& t_description)
{
	ui.labelDescription->setText(t_description);
	ui.lineEditValue->setMaxLength(16);
}

void ASDialog::onOKPressed()
{
	auto value = ui.lineEditValue->text();
	emit sendValue(value);
	this->reject();
}
