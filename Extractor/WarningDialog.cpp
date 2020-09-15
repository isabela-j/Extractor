#include "WarningDialog.h"

WarningDialog::WarningDialog(QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
}

WarningDialog::~WarningDialog()
{
}
