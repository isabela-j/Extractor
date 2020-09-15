#include "ATDialog.h"

#include <qvalidator.h>

ATDialog::ATDialog(QString& t_description, QWidget* parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	m_ui.setupUi(this);
	presets(t_description);
}

ATDialog::~ATDialog()
{
}

void ATDialog::onOKPressed()
{
	QString value;
	if (!m_ui.lineEditGroup->text().isEmpty())
	{
		value += m_ui.lineEditGroup->text();
	}
	if (!m_ui.lineEditElement->text().isEmpty())
	{
		if (!value.isEmpty())
		{
			value += ",";
		}
		value += m_ui.lineEditElement->text();
	}
	emit sendValue(value);
	close();
}

void ATDialog::presets(QString& t_description)
{
	m_ui.labelDescription->setText(t_description);

	m_ui.lineEditGroup->setMaxLength(4);
	m_ui.lineEditGroup->setValidator(new QRegExpValidator(
		QRegExp("[A-Z0-9]{4}"), this));

	m_ui.lineEditElement->setMaxLength(4);
	m_ui.lineEditElement->setValidator(new QRegExpValidator(QRegExp("[A-Z0-9]{4}"), this));

}
