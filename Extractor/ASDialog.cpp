#include "ASDialog.h"

#include <qvalidator.h>

ASDialog::ASDialog(QString& t_description, QWidget* parent)
	:AbstractVRDialog(t_description, parent)
{
	presets(t_description);
}

void ASDialog::onOKPressed()
{
	auto value =
		m_ui.lineEditValue->text();
	emit sendValue(value);
	close();
}

void ASDialog::presets(const QString& t_description)
{
	m_ui.labelDescription->setText(t_description);
	m_ui.lineEditValue->setMaxLength(4);
	m_ui.lineEditValue->setValidator(new QRegExpValidator(
		QRegExp("^([0-9]{3}[DMYW])*$"), this));
}
