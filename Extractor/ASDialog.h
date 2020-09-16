#pragma once
#include "AbstractVRDialog.h"
class ASDialog final: public AbstractVRDialog
{
	Q_OBJECT
public:
	explicit ASDialog(QString& t_description, QWidget* parent = Q_NULLPTR);
	~ASDialog() = default;
signals:
	void sendValue(QString& t_value) override;
private slots:
	void onOKPressed() override;

private:
	void presets(const QString& t_description) override;
};

