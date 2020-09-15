#include "USInsertEdit.h"

#include <qvalidator.h>

USInsertEdit::USInsertEdit(const QString& t_description, QWidget* parent)
	:AbstractVRDialog(t_description, parent)
{
	presets(t_description);
}

void USInsertEdit::onOKPressed()
{
	auto value = m_ui.lineEditValue->text();
	emit sendValue(value);
	close();
}

void USInsertEdit::presets(const QString& t_description)
{
	m_ui.labelDescription->setText("Interger between 0 and 65535.");
	m_ui.lineEditValue->setValidator(new QRegExpValidator(QRegExp("^(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$"), this));
}
