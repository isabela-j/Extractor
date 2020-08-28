#include "UniqueIdentifierDialog.h"

#include <qvalidator.h>

UniqueIdentifierDialog::UniqueIdentifierDialog(QString& t_description, QWidget* parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	ui.labelDescription->setText(t_description);
	ui.lineEditValue->setMaxLength(64);
	const auto regexValidator =
		std::make_unique<QRegExpValidator>(QRegExp("(\\d+\\.?)+"));
	ui.lineEditValue->setValidator(regexValidator.get());
}

UniqueIdentifierDialog::~UniqueIdentifierDialog()
{
}

void UniqueIdentifierDialog::onOKPressed()
{
	auto value = ui.lineEditValue->text();
	emit sendValue(value);
	this->reject();
}
