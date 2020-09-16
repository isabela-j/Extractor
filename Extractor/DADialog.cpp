#include "DADialog.h"

#include <qvalidator.h>

DADialog::DADialog(QString& t_description, QWidget* parent)
	:AbstractVRDialog(t_description,parent)
{
	DADialog::presets(t_description);
}


void DADialog::onOKPressed()
{
	auto value = m_ui.lineEditValue->text();
	emit sendValue(value);
	close();
}

void DADialog::presets(const QString& t_description)
{
	m_ui.labelDescription->setText("Date Format:: YYYYMMDD \n" + t_description);
	m_ui.lineEditValue->setMaxLength(8);
	m_ui.lineEditValue->setValidator(new QRegExpValidator(QRegExp("\\d{4}(0[1-9]|1[012])(0[1-9]|[12][0-9]|3[01])"), this));
}
