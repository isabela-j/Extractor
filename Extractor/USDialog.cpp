#include "USDialog.h"

USDialog::USDialog(QString& t_description, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint),
	m_insertDialogUS(std::make_unique<UnsignedShort>()), m_editDialogUS(std::make_unique<UnsignedShortEdit>())
{
	ui.setupUi(this);
	presets(t_description);
}

USDialog::~USDialog()
{
}

void USDialog::onOKPressed()
{
	QString value;
	int count = ui.listWidget->count();
	for(int i=0;i<count;i++)
	{
		value += ui.listWidget->item(i)->text();
		if(i+1!=count)
		{
			value += "\\";
		}
	}
	emit sendValue(value);
	this->reject();
}

void USDialog::valueWasSend(QString& t_value)
{
	auto* item = new QListWidgetItem(t_value, nullptr, 0);
	ui.listWidget->addItem(item);
}

void USDialog::valueWasChanged(QString& t_value)
{
	ui.listWidget->selectedItems()[0]->setText(t_value);
}

void USDialog::onDeletePressed()
{
	if (!ui.listWidget->selectedItems().isEmpty())
	{
		delete ui.listWidget->selectedItems()[0];
	}
}

void USDialog::onInsertPressed()
{
	m_insertDialogUS->exec();	
}

void USDialog::onEditPressed()
{
	if(!ui.listWidget->selectedItems().isEmpty())
	{
		m_editDialogUS->setLineEditValue(ui.listWidget->selectedItems()[0]->text());
		m_editDialogUS->exec();
	}
}

void USDialog::presets(QString& t_description)
{
	ui.labelDescription->setText(t_description);
	Q_UNUSED(connect(m_insertDialogUS.get(), &UnsignedShort::sendValue, this, &USDialog::valueWasSend));
	Q_UNUSED(connect(m_editDialogUS.get(), &UnsignedShortEdit::changeValue, this, &USDialog::valueWasChanged));
}

