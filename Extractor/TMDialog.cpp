#include "TMDialog.h"

#include <qvalidator.h>

TMDialog::TMDialog(const QString& t_description, QWidget* parent)
	:AbstractVRDialog(t_description,parent)
{
	presets(t_description);
}

void TMDialog::onOKPressed()
{
	auto value = m_ui.lineEditValue->text();
	emit sendValue(value);
	close();
}

void TMDialog::presets(const QString& t_description)
{
	m_ui.labelDescription->setText("Time Format: HHMMSS \n" + t_description);
	m_ui.lineEditValue->setMaxLength(6);
	m_ui.lineEditValue->setValidator(new QRegExpValidator(QRegExp("(2[0-3]|[01][0-9])[0-5][0-9][0-5][0-9]"), this));
}
