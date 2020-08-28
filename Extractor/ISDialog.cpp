#include "ISDialog.h"

#include <qvalidator.h>

ISDialog::ISDialog(QString& t_description, QWidget* parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	presets(t_description);
}

ISDialog::~ISDialog()
{
}
void ISDialog::onOKPressed()
{
	auto value = ui.lineEditValue->text();
	emit sendValue(value);
	this->reject();
}
void ISDialog::presets(QString& t_description)
{
	ui.labelDescription->setText(t_description);
	ui.lineEditValue->setMaxLength(12);
	const auto regexValidator =
		std::make_unique<QRegExpValidator>(QRegExp("(\\d+\\+-?)+"));
	ui.lineEditValue->setValidator(regexValidator.get());
}