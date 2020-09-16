#include "STDialog.h"

STDialog::STDialog(const QString& t_description, QWidget* parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	m_ui.setupUi(this);
	presets(t_description);
}

void STDialog::onOKPressed()
{
	auto value = m_ui.textEditValue->toPlainText();
	value.replace("\n", " ");
	emit sendValue(value);
	close();
}

void STDialog::presets(const QString& t_description) const
{
	m_ui.labelDescription->setText(t_description);
}
