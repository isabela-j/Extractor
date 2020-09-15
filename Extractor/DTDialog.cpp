#include "DTDialog.h"

#include <qvalidator.h>

DTDialog::DTDialog(const QString& t_description, QWidget* parent)
	:AbstractVRDialog(t_description, parent)
{
	presets(t_description);
}

void DTDialog::onOKPressed()
{
	auto value = m_ui.lineEditValue->text();
	emit sendValue(value);
	close();
}

void DTDialog::presets(const QString& t_description)
{
	m_ui.labelDescription->setText("Date format: YYYYMMDDHHMMSS\n" + t_description);
	m_ui.lineEditValue->setMaxLength(16);
	m_ui.lineEditValue->setValidator(new QRegExpValidator(QRegExp(
		"([0-9]{4})(0[1-9]|1[0-2])(0[1-9]|[1-2][0-9]|3[0-1])(2[0-3]|[01][0-9])([0-5][0-9])([0-5][0-9])"), this));
}