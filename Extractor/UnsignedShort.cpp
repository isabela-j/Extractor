#include "UnsignedShort.h"

#include <qvalidator.h>

UnsignedShort::UnsignedShort(QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	presets();
}

UnsignedShort::~UnsignedShort()
{
}

void UnsignedShort::onOKPressed()
{
	auto value = ui.lineEditValue->text();
	emit sendValue(value);
	this->reject();
}

void UnsignedShort::presets()
{
	const auto regexValidator =
		std::make_unique<QRegExpValidator>(QRegExp("^(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$"));
	ui.lineEditValue->setValidator(regexValidator.get());
}
