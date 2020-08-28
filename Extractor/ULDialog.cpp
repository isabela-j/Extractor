#include "ULDialog.h"

#include <qvalidator.h>

ULDialog::ULDialog(QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
}

ULDialog::~ULDialog()
{
}
void ULDialog::onOKPressed()
{
	auto value = ui.lineEditValue->text();
	if (value.toInt() < 0)
	{
		value = "0";
	}
	if(value.at(0)>=4 && value.at(1)>=2 && value.at(2) >= 9 && value.at(3) >= 4 && 
	value.at(4) >= 9 && value.at(5) >= 6 && value.at(6) >= 7 && value.at(7) >= 2 && 
	value.at(8) >= 9 && value.at(9) >= 6)
	{
		value = "4294967295";
	}
	emit sendValue(value);
	this->reject();
}


