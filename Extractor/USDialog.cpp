#include "USDialog.h"

USDialog::USDialog(QString& t_description, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint),
	m_insertDialogUS(std::make_unique<USInsertEdit>("",nullptr)), m_editDialogUS(std::make_unique<USInsertEdit >("",nullptr))
{
	ui.setupUi(this);
	presets(t_description);
}


void USDialog::onOKPressed()
{
	QString value;
	auto count = ui.listWidget->count();
	for(auto i=0;i<count;i++)
	{
		value += ui.listWidget->item(i)->text();
		if(i+1!=count)
		{
			value += "\\";
		}
	}
	emit sendValue(value);
	close();
}

void USDialog::valueWasSend(QString& t_value) const
{
	auto* item = new QListWidgetItem(t_value, nullptr, 0);
	ui.listWidget->addItem(item);
}

void USDialog::valueWasChanged(QString& t_value) const
{
	ui.listWidget->selectedItems()[0]->setText(t_value);
}

void USDialog::onDeletePressed() const
{
	if (!ui.listWidget->selectedItems().isEmpty())
	{
		delete ui.listWidget->selectedItems()[0];
	}
}

void USDialog::onInsertPressed() const
{
	m_insertDialogUS->exec();	
}

void USDialog::onEditPressed() const
{
	if(!ui.listWidget->selectedItems().isEmpty())
	{
		m_editDialogUS->setLineEditValue(ui.listWidget->selectedItems()[0]->text());
		m_editDialogUS->exec();
	}
}

void USDialog::presets(QString& t_description) const
{
	ui.labelDescription->setText(t_description);
	Q_UNUSED(connect(m_insertDialogUS.get(), &USInsertEdit::sendValue, this, &USDialog::valueWasSend));
	Q_UNUSED(connect(m_editDialogUS.get(), &USInsertEdit::sendValue, this, &USDialog::valueWasChanged));
}

