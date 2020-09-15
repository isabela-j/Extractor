#include "ISDialog.h"

#include <qvalidator.h>

ISDialog::ISDialog(const QString& t_description, QWidget* parent)
	:AbstractVRDialog(t_description, parent)
{
	presets(t_description);
}

void ISDialog::onOKPressed()
{
	auto value =m_ui.lineEditValue->text();
	emit sendValue(value);
	close();
}

void ISDialog::presets(const QString& t_description)
{
	m_ui.labelDescription->setText(t_description);
	m_ui.lineEditValue->setMaxLength(12);
	m_ui.lineEditValue->setValidator(new QRegExpValidator(QRegExp("(\\d+\\+-?)+"),this));
}
