#include "CSDialog.h"
#include <QComboBox>

CSDialog::CSDialog(QString& t_description,QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	presets(t_description);
}

CSDialog::~CSDialog()
{
}

void CSDialog::presets(QString& t_description)
{
	if(t_description=="Modality")
	{
		auto* comboBox = new QComboBox();
		QStringList list = { "CR", "CT", "MR", "US", "OT", "BI", "CD", "DD", "DG","ES","LS","PT","RG",
						   "ST", "TG", "RF","RTIMAGE","RTDOSE","RTSTRUCT", "RTPLAN", "RTRECORD", "HC"
						   "DX","NM","MG", "IO","PX", "GM", "SM", "XC","PR","AU","EPS","HD","SR","IVUS","OP","SMR" };
		for (int i = 0; i < list.size(); i++)
			comboBox->addItem(list[i]);
		ui.verticalLayoutValue->addWidget(comboBox);
		ui.labelDescription->setText(list[0]);
		connect(comboBox, QOverload<int>::of(&QComboBox::highlighted), this, [=](int index) { ui.labelDescription->setText(list[index]), m_value = list[index]; });
		
		
	}
	else if(t_description=="PatientSex")
	{
		auto* comboBox = new QComboBox();
		QStringList list = { "Not specified","Male","Female","Other" };
		for (int i = 0; i < 4; i++)
			comboBox->addItem(QString::number(i));
		ui.verticalLayoutValue->addWidget(comboBox);
		ui.labelDescription->setText(list[0]);
		connect(comboBox, QOverload<int>::of(&QComboBox::highlighted), this, [=](int index) { ui.labelDescription->setText(list[index]), m_value = list[index].at(0); });
		
	}
	else
	{
		m_lineEdit = new QLineEdit;
		ui.verticalLayoutValue->addWidget(m_lineEdit);
		connect(m_lineEdit, &QLineEdit::textChanged, this, &CSDialog::lineEditChanged);
		
	}

}

void CSDialog::onOKPressed()
{
	emit sendValue(m_value);
	this->reject();
}

void CSDialog::lineEditChanged()
{
	m_value = m_lineEdit->text();
}

