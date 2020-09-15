#include "ULDialog.h"

#include <QMessageBox>
#include <qvalidator.h>

ULDialog::ULDialog(const QString& t_description, QWidget* parent)
	:AbstractVRDialog(t_description,parent)
{
	presets(t_description);
}

void ULDialog::onOKPressed()
{
	auto value = m_ui.lineEditValue->text();
	const auto val = value.toLongLong();
	if(val> 4294967295)
	{
		int warning = QMessageBox::warning(this, tr("Warning found"),
			tr("Introduce an integer between 0 and 4294967295."), QMessageBox::Cancel);
	}
	else
	{
		emit sendValue(value);
		close();
	}
}

void ULDialog::presets(const QString& t_description)
{
	m_ui.labelDescription->setText("Integer between 0 and 4294967295.\n"+ t_description);
	m_ui.lineEditValue->setMaxLength(10);
	m_ui.lineEditValue->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$"), this));
}


