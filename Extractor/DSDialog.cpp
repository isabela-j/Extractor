#include "DSDialog.h"

#include <qvalidator.h>

DSDialog::DSDialog(QString& t_description, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	presets(t_description);
}

DSDialog::~DSDialog()
{
}

void DSDialog::onOKPressed()
{
	auto value = ui.lineEditValue->text();
	emit sendValue(value);
	this->reject();
}

void DSDialog::presets(QString& t_description)
{
	ui.labelDescription->setText(t_description);
	ui.lineEditValue->setMaxLength(16);
	const auto regexValidator =
		std::make_unique<QRegExpValidator>(QRegExp("[0-9+-.]*(e|E)$"));
	ui.lineEditValue->setValidator(regexValidator.get());
}
