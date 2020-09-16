#pragma once


#include "ui_SizeSQ.h"

class SizeSQ final: public QDialog
{
	Q_OBJECT

public:
	explicit SizeSQ(QWidget *parent = Q_NULLPTR);
	~SizeSQ() = default;
signals:
	void sendSize(QString& t_size);
private slots:
	void onOKPressed();
private:
	Ui::SizeSQ m_ui;
};
