#include "FDdialog.h"

FDdialog::FDdialog(QString& t_description, QWidget *parent)
	:QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint),
	m_insertDialog(std::make_unique<FDInsertDialog>()), m_editDialog(std::make_unique<FDEditDialog>())
{
	m_ui.setupUi(this);
	presets(t_description);
}

FDdialog::~FDdialog()
{
}

void FDdialog::onInsertPressed() const
{
	m_insertDialog->exec();
}

void FDdialog::valueWasSend(QString& t_value) const
{
	auto* item = new QListWidgetItem(t_value, nullptr, 0);
	m_ui.listWidget->addItem(item);
}

void FDdialog::onEditPressed() const
{
	if (!m_ui.listWidget->selectedItems().isEmpty())
	{
		m_editDialog->setLineEditValue(m_ui.listWidget->selectedItems()[0]->text());
		m_editDialog->exec();
	}
}

void FDdialog::valueWasChanged(QString& t_value) const
{
	m_ui.listWidget->selectedItems()[0]->setText(t_value);
}

void FDdialog::onDeletePressed() const
{
	if (!m_ui.listWidget->selectedItems().isEmpty())
	{
		delete m_ui.listWidget->selectedItems()[0];
	}
}

void FDdialog::onOKPressed()
{
	QString value;
	const auto count = m_ui.listWidget->count();
	for (auto i = 0; i < count; i++)
	{
		value += m_ui.listWidget->item(i)->text();
		if (i + 1 != count)
		{
			value += "\\";
		}
	}
	emit sendValue(value);
	this->reject();
}

void FDdialog::presets(QString& t_description) const
{
	m_ui.labelDescription->setText(t_description);
	Q_UNUSED(connect(m_insertDialog.get(), &FDInsertDialog::sendValue, this, &FDdialog::valueWasSend));
	Q_UNUSED(connect(m_editDialog.get(), &FDEditDialog::changeValue, this, &FDdialog::valueWasChanged));
}
