#include "AbstractVRDialog.h"

AbstractVRDialog::AbstractVRDialog(const QString& t_description, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	m_ui.setupUi(this);
}

void AbstractVRDialog::onOKPressed()
{
	auto val = m_ui.lineEditValue->text();
	emit sendValue(val);
}
