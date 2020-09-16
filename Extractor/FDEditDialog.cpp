#include "FDEditDialog.h"

#include <qvalidator.h>

FDEditDialog::FDEditDialog(QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	m_ui.setupUi(this);
	presets();
}

FDEditDialog::~FDEditDialog()
{
}

void FDEditDialog::onOKPressed()
{
	auto value = m_ui.lineEditValue->text();
	if (!value.contains("."))
	{
		value.append(".");
	}
	while (value.size() - value.indexOf(".") != 7)
	{
		value.append("0");
	}
	emit changeValue(value);
	this->reject();
}

void FDEditDialog::presets() const
{
	m_ui.lineEditValue->setValidator(new QRegExpValidator(QRegExp("[0-9]+(\\.[0-9][0-9][0-9][0-9][0-9][0-9]?)?")));
}
