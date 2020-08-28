#include "DADialog.h"

#include <qvalidator.h>

DADialog::DADialog(QString& t_description, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	presets(t_description);
	
}
void DADialog::presets(QString& t_description)
{
	ui.labelDescription->setText(t_description);
	ui.labelDateFormat->setText("Date Format:: YYYYMMDD");
	ui.lineEditValue->setMaxLength(8);
	const auto regexValidator =
		std::make_unique<QRegExpValidator>(QRegExp("\\d{4}(0[1-9]|1[012])(0[1-9]|[12][0-9]|3[01])"));
	ui.lineEditValue->setValidator(regexValidator.get());
}


DADialog::~DADialog()
{
}
void DADialog::onOKPressed()
{
	auto value = ui.lineEditValue->text();
	emit sendValue(value);
	this->reject();
}