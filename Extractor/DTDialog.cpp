#include "DTDialog.h"

#include <qvalidator.h>

DTDialog::DTDialog(QString& t_description, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	presets(t_description);
}

DTDialog::~DTDialog()
{
}

void DTDialog::onOKPressed()
{
	auto value = ui.lineEditValue->text();
	emit sendValue(value);
	this->reject();
}

void DTDialog::presets(QString& t_description)
{
	ui.labelDescription->setText(t_description);
	ui.lineEditValue->setMaxLength(16);
	const auto regexValidator =
		std::make_unique<QRegExpValidator>(QRegExp("([0-9]{4})(0[1-9]|1[0-2])(0[1-9]|[1-2][0-9]|3[0-1])(2[0-3]|[01][0-9])([0-5][0-9])([0-5][0-9])"));
	ui.lineEditValue->setValidator(regexValidator.get());
}
