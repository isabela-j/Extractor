#include "STDialog.h"

STDialog::STDialog(QString& t_description, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
}

STDialog::~STDialog()
{
}

void STDialog::onOKPressed()
{
	auto value = ui.textEditValue->toPlainText();
	value.replace("\n", " ");
	emit sendValue(value);
	this->reject();
}

void STDialog::presets(QString& t_description)
{
	ui.labelDescription->setText(t_description);
	
}
