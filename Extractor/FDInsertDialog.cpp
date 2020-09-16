#include "FDInsertDialog.h"

#include <qvalidator.h>

FDInsertDialog::FDInsertDialog(QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	m_ui.setupUi(this);
	presets();
}

FDInsertDialog::~FDInsertDialog()
{
}

void FDInsertDialog::onOKPressed()
{
	auto value = m_ui.lineEditValue->text();
	if(!value.contains("."))
	{
		value.append(".");
	}
	while(value.size()-value.indexOf(".")!=7)
	{
		value.append("0");
	}
	emit sendValue(value);
	this->reject();
}

void FDInsertDialog::presets() const
{
	m_ui.lineEditValue->setValidator(new QRegExpValidator(QRegExp("[0-9]+(\\.[0-9][0-9][0-9][0-9][0-9][0-9]?)?")));
}
