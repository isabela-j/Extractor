#pragma once
#include "AbstractVRDialog.h"
class DTDialog final: public AbstractVRDialog
{
	Q_OBJECT

public:
	explicit DTDialog(const QString& t_description, QWidget* parent = Q_NULLPTR);
	~DTDialog()= default;
signals:
	void sendValue(QString& t_value) override;
private slots:
	void onOKPressed() override;

private:
	void presets(const QString& t_description) override;
};

