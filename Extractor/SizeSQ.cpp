#include "SizeSQ.h"

SizeSQ::SizeSQ(QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	m_ui.setupUi(this);
}

void SizeSQ::onOKPressed()
{
	QString size;
	m_ui.radioButtonExplicit->isChecked() ? size = "0" : size = "FFFFFFFF";
	sendSize(size);
	close();
}

