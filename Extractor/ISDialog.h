#pragma once

#include "AbstractVRDialog.h"

class ISDialog final : public AbstractVRDialog
{
	Q_OBJECT
public:
	explicit ISDialog(const QString& t_description, QWidget* parent = Q_NULLPTR);
	~ISDialog() = default;
private slots:
	 void onOKPressed() override;
signals:
	void sendValue(QString& t_value) override;
private:
	void presets(const QString& t_description) override;
};

