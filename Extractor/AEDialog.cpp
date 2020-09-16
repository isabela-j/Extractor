#include "AEDialog.h"


AEDialog::AEDialog(QString& t_description, QWidget* parent)
	:AbstractVRDialog(t_description,parent)
{
	presets(t_description);
}

void AEDialog::onOKPressed()
{
	auto value =
		m_ui.lineEditValue->text();
	emit sendValue(value);
	close();
}

void AEDialog::presets(const QString& t_description)
{
	m_ui.labelDescription->setText(t_description);
	m_ui.lineEditValue->setMaxLength(16);
}
