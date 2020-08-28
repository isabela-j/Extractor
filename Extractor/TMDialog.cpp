#include "TMDialog.h"

#include <qvalidator.h>

TMDialog::TMDialog(QString& t_description, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	presets(t_description);
}

TMDialog::~TMDialog()
{
}

void TMDialog::onOKPressed()
{
	auto value = ui.lineEditValue->text();
	emit sendValue(value);
	this->reject();
}
void TMDialog::presets(QString& t_description)
{
	ui.labelDescription->setText(t_description);
	ui.labelTimeFormat->setText("Time Format: HHMMSS");
	ui.lineEditValue->setMaxLength(8);
	const auto regexValidator =
		std::make_unique<QRegExpValidator>(QRegExp("(2[0-3]|[01]?[0-9])([0-5]?[0-9])([0-5]?[0-9])$"));
	ui.lineEditValue->setValidator(regexValidator.get());
}