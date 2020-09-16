#pragma once

#include "ui_STDialog.h"

class STDialog final : public QDialog
{
	Q_OBJECT

public:
	explicit STDialog(const QString& t_description, QWidget *parent = Q_NULLPTR);
	~STDialog() = default;
signals:
	void sendValue(QString& t_value);
private slots:
	void onOKPressed();
private:
	Ui::STDialog m_ui;
	void presets(const QString& t_description) const;
};
