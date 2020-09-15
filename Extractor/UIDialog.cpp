#include "UIDialog.h"

#include <qvalidator.h>

UIDialog::UIDialog(const QString& t_description, QWidget* parent)
	:AbstractVRDialog(t_description, parent)
{
	presets(t_description);
}

void UIDialog::onOKPressed()
{
	auto value = m_ui.lineEditValue->text();
	emit sendValue(value);
	close();
}

void UIDialog::presets(const QString& t_description)
{
	m_ui.labelDescription->setText("Unique Identifier(UID) \n" + t_description);
	m_ui.lineEditValue->setMaxLength(64);
	m_ui.lineEditValue->setValidator(new QRegExpValidator(QRegExp("(\\d+\\.?)+"), this));
}
