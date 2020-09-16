#include "DSDialog.h"

#include <qvalidator.h>

DSDialog::DSDialog(const QString& t_description, QWidget* parent)
	:AbstractVRDialog(t_description,parent)
{
	presets(t_description);
}

void DSDialog::onOKPressed()
{
	auto value = m_ui.lineEditValue->text();
	emit sendValue(value);
	close();
}

void DSDialog::presets(const QString& t_description)
{
	m_ui.labelDescription->setText(t_description);
	m_ui.lineEditValue->setMaxLength(16);
	m_ui.lineEditValue->setValidator(new QRegExpValidator(QRegExp("[0-9+-.]*(e|E)$"),this));
}
