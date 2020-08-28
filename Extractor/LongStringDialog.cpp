#include "LongStringDialog.h"

#include <iostream>

LongStringDialog::LongStringDialog(QString& t_description, QWidget* parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	ui.labelDescription->setText(t_description);
	ui.lineEditValue->setMaxLength(64);
}

LongStringDialog::~LongStringDialog()
{
}
void LongStringDialog::onOKPressed()
{
	auto value = ui.lineEditValue->text();
	emit sendValue(value);
	this->reject();
}

