#pragma once

#include <QDialog>
#include "ui_SizeSQ.h"

class SizeSQ : public QDialog
{
	Q_OBJECT

public:
	SizeSQ(QWidget *parent = Q_NULLPTR);
	~SizeSQ() = default;
signals:
	void sendSize(QString& t_size);
private slots:
	void onOKPressed();
private:
	Ui::SizeSQ m_ui;
};
