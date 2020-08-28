#include "FDdialog.h"

FDdialog::FDdialog(QString& t_description, QWidget *parent)
	:QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint),
	m_insertDialog(std::make_unique<FDInsertDialog>()), m_editDialog(std::make_unique<FDEditDialog>())
{
	ui.setupUi(this);
	presets(t_description);
}

FDdialog::~FDdialog()
{
}

void FDdialog::onInsertPressed()
{
	m_insertDialog->exec();
}

void FDdialog::valueWasSend(QString& t_value)
{
	auto* item = new QListWidgetItem(t_value, nullptr, 0);
	ui.listWidget->addItem(item);
}

void FDdialog::onEditPressed()
{
	if (!ui.listWidget->selectedItems().isEmpty())
	{
		m_editDialog->setLineEditValue(ui.listWidget->selectedItems()[0]->text());
		m_editDialog->exec();
	}
}

void FDdialog::valueWasChanged(QString& t_value)
{
	ui.listWidget->selectedItems()[0]->setText(t_value);
}

void FDdialog::onDeletePressed()
{
	if (!ui.listWidget->selectedItems().isEmpty())
	{
		delete ui.listWidget->selectedItems()[0];
	}
}

void FDdialog::onOKPressed()
{
	QString value;
	int count = ui.listWidget->count();
	for (int i = 0; i < count; i++)
	{
		value += ui.listWidget->item(i)->text();
		if (i + 1 != count)
		{
			value += "\\";
		}
	}
	emit sendValue(value);
	this->reject();
}

void FDdialog::presets(QString& t_description)
{
	ui.labelDescription->setText(t_description);
	Q_UNUSED(connect(m_insertDialog.get(), &FDInsertDialog::sendValue, this, &FDdialog::valueWasSend));
	Q_UNUSED(connect(m_editDialog.get(), &FDEditDialog::changeValue, this, &FDdialog::valueWasChanged));
}
