#include "ShortStringDialog.h"

ShortStringDialog::ShortStringDialog(QString& t_description, QWidget* parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	ui.labelDescription->setText(t_description);
	ui.lineEditValue->setMaxLength(16);
}

ShortStringDialog::~ShortStringDialog()
{
}

void ShortStringDialog::onOKPressed()
{
	auto value = ui.lineEditValue->text();
	emit sendValue(value);
	this->reject();
}
